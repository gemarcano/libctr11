@ SPDX-License-Identifier: GPL-2.0-or-later
@ Copyright: Gabriel Marcano, 2023

.arm
.cpu mpcore
.fpu vfpv2
.align 4

.section .text.start, "x"

.global _start
.type _start, STT_FUNC
_start:
	@ Preserve argc and argv
	mov r2, r0
	mov r3, r1

	adr r0, argc_offset
	ldr r1, [r0]
	add r0, r1
	str r2, [r0]

	adr r0, argv_offset
	ldr r1, [r0]
	add r0, r1
	str r3, [r0]

	@ Disable interrupts
	CPSID aif

	@ Set stack
	ldr sp, =_stack

	@ Clear bss
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

end_hang_:
	wfi
	b end_hang_ @die if we return, just forcibly hang

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
	bx lr
