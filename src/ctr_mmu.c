#include <ctr11/ctr_mmu.h>
#include <ctr11/ctr_cache.h>
#include <stdint.h>
#include <stdalign.h>
#include <string.h>

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

alignas(1 << 14) uint32_t ctr_mmu_level1_table[4096];

void ctr_mmu_fault_initialize(uint32_t *entry)
{
	*entry = 0;
}

void ctr_mmu_coarse_initialize(uint32_t *entry, uint32_t base, unsigned char domain)
{
	*entry = (base & 0xFFFFFC00) | (uint32_t)domain << 5 | 0x1;
}

void ctr_mmu_section_initialize(uint32_t *entry, uint32_t base, ctr_mmu_permissions perms, ctr_mmu_memory_attributes attr, unsigned char domain)
{
	uint32_t tex = ((uint32_t)attr >> 2) << 12;
	uint32_t cb =  ((uint32_t)attr & 0x3) << 2;
	uint32_t ap = ((uint32_t)perms & 0x3) << 10;
	uint32_t apx = ((uint32_t)perms >> 2) << 15;
	*entry = (base & 0xFFF00000) | 1 << 16 | apx | tex | ap | (uint32_t)domain << 5 | cb | 0x2;
}

void ctr_mmu_supersection_initialize(uint32_t *entry, uint32_t base, ctr_mmu_permissions perms, ctr_mmu_memory_attributes attr)
{
	uint32_t tex = ((uint32_t)attr >> 2) << 12;
	uint32_t cb =  ((uint32_t)attr & 0x3) << 2;
	uint32_t ap = ((uint32_t)perms & 0x3) << 10;
	uint32_t apx = ((uint32_t)perms >> 2) << 15;
	*entry = (base & 0xFF000000) | 1u << 18 | 1 << 16 | apx | tex | ap | cb | 0x2;
}

void ctr_mmu_initialize_(void);
void ctr_mmu_initialize(void)
{
	for (size_t i = 0; i < 0x1000; ++i)
	{
		if ((i < 0x100) || (i >= 0x17E))
		{
			ctr_mmu_memory_attributes attr = CTR_MMU_NORMAL_INNER(CTR_MMU_WBC_WA_B) | CTR_MMU_NORMAL_OUTER(CTR_MMU_WBC_WA_B);
			ctr_mmu_section_initialize(ctr_mmu_level1_table + i, i << 20, CTR_MMU_RW_RW, attr, 0);
		}
		else
		{
			ctr_mmu_memory_attributes attr = CTR_MMU_SHARED_DEVICE;
			ctr_mmu_section_initialize(ctr_mmu_level1_table + i, i << 20, CTR_MMU_RW_RW, attr, 0);
		}
	}
	ctr_cache_clean_data_all();
	ctr_mmu_initialize_();
}

