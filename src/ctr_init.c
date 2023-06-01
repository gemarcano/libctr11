#include <ctr11/ctr_console.h>
#include <ctr11/ctr_screen.h>
#include <ctr11/ctr_freetype.h>
#include <ctr11/ctr_pxi.h>
#include <ctr11/ctr_gpu.h>

#include <stdint.h>

//#define PDC0_FRAMEBUFFER_SETUP_FBA_ADDR_1 PDC0_FRAMEBUFFER_SETUP_REG(0x68)
//#define PDC1_FRAMEBUFFER_SETUP_FBA_ADDR_1 PDC1_FRAMEBUFFER_SETUP_REG(0x68)

void __attribute__((weak)) ctr_libctr11_init(void);

void __attribute__((weak)) ctr_libctr11_init(void)
{
	// FIXME we should do GPU/LCD/display init properly here
	ctr_pxi_initialize();
	ctr_screen_initialize(&ctr_screen_top, (uint8_t*)PDC0_FRAMEBUFFER_SETUP_FBA_ADDR_1, 400, 240, CTR_GFX_PIXEL_RGB8);
	ctr_screen_initialize(&ctr_screen_bottom, (uint8_t*)PDC1_FRAMEBUFFER_SETUP_FBA_ADDR_1, 320, 240, CTR_GFX_PIXEL_RGB8);
	ctr_console_initialize(&ctr_screen_top);

	ctr_freetype_initialize();
	ctr_pxi_push((unsigned int)PDC0_FRAMEBUFFER_SETUP_FBA_ADDR_1);
	ctr_pxi_push((unsigned int)PDC1_FRAMEBUFFER_SETUP_FBA_ADDR_1);
}

