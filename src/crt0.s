.arm
.cpu mpcore
.fpu vfpv2
.align 4
.global _start

.section .text.start, "x"

_start:
	@ Preserve argc and argv
	mov r2, r0
	mov r3, r1

	@ Invalidate all caches before continuing
	mov r0, #0
	mcr p15, 0, r0, c7, c7, 0

	@ Set FCSE to zero. r0 should be zero
	mcr p15, 0, r0, c13, c0, 0

	adr r0, argc_offset
	ldr r1, [r0]
	add r0, r1
	str r2, [r0]

	adr r0, argv_offset
	ldr r1, [r0]
	add r0, r1
	str r3, [r0]

	@ Disable interrupts, switch to system mode
	CPSID aif, #0x1F

	@ Clear bss, needs to happen before MMU setup since table is in this section
	adr r0, clear_bss_offset
	ldr r1, [r0]
	add r0, r1, r0
	blx r0

	@ Initialize FPU access
	mov r0, #0
	mov r1, #0xF00000           @ Give full access to cp10/11 in user and privileged mode
	mcr p15, 0, r1, c1, c0, 2   @ Write Coprocessor Access Control Register, needs an IMB
	mcr p15, 0, r0, c7, c5, 4   @ Flush Prefetch Buffer, effectively an Instruction Memory Barrier (IMB)
	mov r1, #0x40000000         @ Clear exception bits and enable VFP11
	mov r2, #0x3C00000          @ Round towards zero (RZ) mode, flush-to-zero mode, default NaN mode
	fmxr fpexc, r1              @ Write Floating-point exception register
	fmxr fpscr, r2              @ Write Floating-Point Status and Control Register

	@ Set stack
	ldr sp, =_stack

	@initialize MMU table
	adr r0, ctr_mmu_initialize_offset
	ldr r1, [r0]
	add r0, r1
	blx r0

	mrc p15, 0, r0, c2, c0, 0
	ldr r0, =ctr_mmu_level1_table
	lsr r0, #14
	lsl r0, #14
	orr r0, #1 << 3
	orr r0, #1 << 1
	mcr p15, 0, r0, c2, c0, 0

	@Invalidate all TLB entries
	mcr p15, 0, r0, c8, c7, 0

	@(FIXME For now) set all domains to manager access level
	mvn r0, #0
	mcr p15, 0, r0, c3, c0, 0

	@TTBCR, set N to zero so TTBR0 is used always
	mov r0, #0
	mcr p15, 0, r0, c2, c0, 2

	@ Disable instruction and data cache
	mrc p15, 0, r0, c1, c0, 0
	bic r0, #1 << 12
	bic r0, #1 << 2 @data cache
	mcr p15, 0, r0, c1, c0, 0

	@ FIXME Should we flush the caches now?

	@Auxiliary Control register
	mrc p15, 0, r0, c1, c0, 1
	bic r0, #1 << 6 @Don't do L1 parity checking
	@orr r0, #1 << 5 @Set CPU mode to SMP
	@ Don't know enough to decide on bit 4 EXCL, about cache inclu/exclusivity
	orr r0, #1 << 3 @Enable instruction folding
	orr r0, #1 << 2 @Enable static branch prediction
	orr r0, #1 << 1 @Enable dynamic branch prediction
	orr r0, #1 @Enable return stack
	mcr p15, 0, r0, c1, c0, 1

	@ Configure control register
	mrc p15, 0, r0, c1, c0, 0
	bic r0, #1 << 29 @Disable forced Access Perm checking
	bic r0, #1 << 28 @Disable TEX remapping
	bic r0, #1 << 27 @Don't make FIQs NMFIs
	@I can't be bothered by bit 25 EE, CPSR E bit on exception
	orr r0, #1 << 23
	orr r0, #1 << 22 @Enable unaligned support
	bic r0, #1 << 15 @Loads to PC set T bit
	orr r0, #1 << 13 @Use high exception vectors
	orr r0, #1 << 12 @Enable level 1 instruction cache
	orr r0, #1 << 11 @Enable program flow prediction
	orr r0, #1 << 2 @Enable data cache
	bic r0, #1 << 1 @disable strict align fault checking
	orr r0, #1 @Enable MMU -- default mapping is ALWAYS flat
	mcr p15, 0, r0, c1, c0, 0

	@call libc initialization routines
	adr r0, __libc_init_array_offset
	ldr r1, [r0]
	add r0, r1, r0
	blx r0

	adr r0, _fini_offset
	ldr r1, [r0]
	add r0, r1, r0
	adr r1, atexit_offset
	ldr r2, [r1]
	add r1, r2, r1
	blx r1

	adr r0, _init_offset
	ldr r1, [r0]
	add r0, r1, r0
	blx r0

	@Initialize libctr11 (weak symbol)
	adr r0, ctr_libctr11_init_offset
	ldr r1, [r0]
	add r0, r1, r0
	blx r0

	@ Restore argc and argv
	adr r0, argc_offset
	ldr r1, [r0]
	add r0, r1
	ldr r0, [r0]

	adr r1, argv_offset
	ldr r2, [r1]
	add r1, r2
	ldr r1, [r1]

	adr r3, main_offset
	ldr r2, [r3]
	add r2, r3
	blx r2

	@if we do return, make sure to call exit functions.
	adr r1, exit_offset
	ldr r2, [r1]
	add r1, r2, r1
	blx r1

	b . @die if we return, just forcibly hang

main_offset:
.word main-.

_fini_offset:
.word _fini-.

atexit_offset:
.word atexit-.

_init_offset:
.word _init-.

__libc_init_array_offset:
.word __libc_init_array-.

ctr_libctr11_init_offset:
.word ctr_libctr11_init-.

__bss_start_offset:
.word __bss_start__-.

__bss_end_offset:
.word __bss_end__-.

clear_bss_offset:
.word clear_bss-.

exit_offset:
.word exit-.

argc_offset:
.word argc-.

argv_offset:
.word argv-.

argc:
.skip 4

argv:
.skip 4

ctr_mmu_initialize_offset:
.word ctr_mmu_initialize-.

clear_bss:
	@clear bss
	adr r0, __bss_start_offset
	ldr r1, [r0]
	add r0, r1, r0

	adr r1, __bss_end_offset
	ldr r2, [r1]
	add r1, r2, r1
	mov r2, #0
	.Lclear_bss_loop:
		cmp r0, r1
		beq .Lclear_bss_loop_done
		str r2, [r0], #4
		b .Lclear_bss_loop
	.Lclear_bss_loop_done:
	blx lr

