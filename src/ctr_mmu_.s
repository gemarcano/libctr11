.arm
.cpu mpcore
.fpu vfpv2
.align 4
.global ctr_mmu_initialize_, ctr_mmu_shutdown
.type ctr_mmu_initialize_, %function
.type ctr_mmu_shutdown, %function

ctr_mmu_initialize_:
	@ Set FCSE to zero. r0 should be zero
	mov r0, #0
	mcr p15, 0, r0, c13, c0, 0

	@ Invalidate instruction cache caches before continuing
	push {lr}
	ldr r0, =ctr_cache_flush_instruction_all
	blx r0

	@ Initialize MMU table (table itself should have been initialized)
	mrc p15, 0, r0, c2, c0, 0
	ldr r0, =ctr_mmu_level1_table
	lsr r0, #14
	lsl r0, #14
	orr r0, #1 << 3
	orr r0, #1 << 1
	mcr p15, 0, r0, c2, c0, 0

	@ Invalidate all TLB entries
	mcr p15, 0, r0, c8, c7, 0

	@ Set all domains to client access level
	ldr r0, =0x55555555
	mcr p15, 0, r0, c3, c0, 0

	@ TTBCR, set N to zero so TTBR0 is used always
	mov r0, #0
	mcr p15, 0, r0, c2, c0, 2

	@ FIXME Should we flush the caches now?

	@ Disable instruction
	mov r1, #0
	mrc p15, 0, r1, c1, c0, 0
	mov r0, r1 @copy mrc result to r0
	and r1, #1 << 12 @only keep track of the value of the instruction cache
	bic r0, #1 << 12
	mcr p15, 0, r0, c1, c0, 0

	@ Configure control register
	mrc p15, 0, r0, c1, c0, 0
	orr r0, r1 @Enable level 1 instruction cache only if it was already
	orr r0, #1 @Enable MMU -- default mapping is ALWAYS flat
	mcr p15, 0, r0, c1, c0, 0

	pop {lr}
	bx lr

ctr_mmu_shutdown:
	@ Set FCSE to zero. r0 should be zero
	mcr p15, 0, r0, c13, c0, 0

	@ Configure control register
	mrc p15, 0, r0, c1, c0, 0
	bic r0, #1 << 2 @Disable data cache
	bic r0, #1 @Disable MMU
	mcr p15, 0, r0, c1, c0, 0

	bx lr

