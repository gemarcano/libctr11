@*******************************************************************************
@* Copyright (C) 2016, 2017 Gabriel Marcano
@*
@* Refer to the COPYING.txt file at the top of the project directory. If that is
@* missing, this file is licensed under the GPL version 2.0 or later.
@*
@******************************************************************************/

.arm

.align 4

.global ctr_cache_clean_and_flush_all, ctr_cache_flush_data_all
.global ctr_cache_flush_data_entry, ctr_cache_data_clean_entry
.global ctr_cache_data_clean_and_flush_entry
.global ctr_cache_flush_instruction_all, ctr_cache_flush_instruction_entry
.global ctr_isb, ctr_dsb, ctr_dmb

.type ctr_cache_clean_and_flush_all, %function
.type ctr_cache_flush_data_all, %function
.type ctr_cache_flush_data_entry, %function
.type ctr_cache_data_clean_entry, %function
.type ctr_cache_data_clean_and_flush_entry, %function
.type ctr_cache_flush_instruction_all, %function
.type ctr_cache_flush_instruction_entry, %function
.type ctr_isb,  %function
.type ctr_dsb, %function
.type ctr_dmb, %function

.macro define_entry_function c, segment=1
	mcr p15, 0, r0, c7, \c, \segment
	bx lr
.endm

ctr_cache_clean_and_flush_all:
	mov r0, #0
	define_entry_function c10, 0

ctr_cache_flush_data_all:
	mov r0, #0
	define_entry_function c6, 0

ctr_cache_flush_data_entry:
	define_entry_function c6

ctr_cache_data_clean_entry:
	define_entry_function c10

ctr_cache_data_clean_and_flush_entry:
	define_entry_function c14

ctr_cache_flush_instruction_all:
	mov r0, #0
	define_entry_function c5, 0

ctr_cache_flush_instruction_entry:
	define_entry_function c5

ctr_isb:
	mov r0, #0
	define_entry_function c5, 4

ctr_dsb:
	mov r0, #0
	define_entry_function c10, 4

ctr_dmb:
	mov r0, #0
	define_entry_function c10, 5

