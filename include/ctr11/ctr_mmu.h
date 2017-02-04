/*******************************************************************************
 * Copyright (C) 2016 Gabriel Marcano
 *
 * Refer to the COPYING.txt file at the top of the project directory. If that is
 * missing, this file is licensed under the GPL version 2.0 or later.
 *
 ******************************************************************************/

/** @file */

#ifndef CTR_MMU_H_
#define CTR_MMU_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

extern uint32_t ctr_mmu_level1_table[4096];
/*
bootrom: 64k - 1 large page
bootrom mirror: same
IO memory: 126 MB - 7 supersections, 14 sections
MPCore private: 8k, 2 pages
(N3DS) level2 cache controller 4k - 1 page
VRAM- 6MB, 6 sections
(N3DS) additional memory - 4MB 4 sections
DSP - 512k, 8 large pages
AXIWRAM - 512k, 8 large pages
FCRAM - 128MB, 8 super sections
(N3DS) FCRAM extension - 128MB, 8 super sections
bootrom mirror: 64k - 1 large page
*/

typedef enum
{
	CTR_MMU_NOACCESS = 0,
	CTR_MMU_RW_NONE = 1,
	CTR_MMU_RW_RO = 2,
	CTR_MMU_RW_RW = 3,
	CTR_MMU_RO_NONE = 5,
	CTR_MMU_RO_RO = 7,
} ctr_mmu_permissions;

//WBC - Write back cached
//WA - Write allocate
//B Buffered
//U Unbuffered
#define CTR_MMU_STRONGLY_ORDERED 0
#define CTR_MMU_SHARED_DEVICE 1
#define CTR_MMU_NON_SHARED_DEVICE (0x8)
#define CTR_MMU_NORMAL_N_U 0
#define CTR_MMU_WBC_WA_B 1
#define CTR_MMU_WTC_NA_B 2
#define CTR_MMY_WBC_NA_B 3
#define CTR_MMU_NORMAL_INNER(opt) (1 << 4 | ((opt) & 0x3))
#define CTR_MMU_NORMAL_OUTER(opt) (1 << 4 | (((opt) & 0x3) << 2))
typedef int ctr_mmu_memory_attributes;

void ctr_mmu_fault_initialize(uint32_t *entry);
void ctr_mmu_coarse_initialize(uint32_t *entry, uint32_t base, unsigned char domain);
void ctr_mmu_section_initialize(uint32_t *entry, uint32_t base, ctr_mmu_permissions perms, ctr_mmu_memory_attributes attr, unsigned char domain);
void ctr_mmu_supersection_initialize(uint32_t *entry, uint32_t base, ctr_mmu_permissions perms, ctr_mmu_memory_attributes attr);
void ctr_mmu_initialize(void);

#ifdef __cplusplus
extern "C" }
#endif

#endif//CTR_MMU_H_

