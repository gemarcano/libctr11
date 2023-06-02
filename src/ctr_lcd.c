// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright: Gabriel Marcano, 2023

#include <ctr11/ctr_lcd.h>

#include <stdbool.h>
#include <stdint.h>

void ctr_lcd_set_fill_color(ctr_lcd_screen screen, ctr_lcd_color color, bool enable)
{
    uint32_t data = color.red | color.green << 8 | color.blue << 16 | (enable ? 1 : 0) << 24;
    switch (screen)
    {
        case CTR_LCD_TOP_SCREEN:
            CTR_LCD_CONF_FILL_COLOR(CTR_LCD_TOP_SCREEN_CONF) = data;
            break;
        case CTR_LCD_BOT_SCREEN:
            CTR_LCD_CONF_FILL_COLOR(CTR_LCD_BOT_SCREEN_CONF) = data;
            break;
    }
}

void ctr_lcd_backlight_duty_cycle(ctr_lcd_screen screen, double duty)
{
	uint16_t period = 0x3FFu & CTR_LCD_CONF_BACKLIGHT_CNT(CTR_LCD_TOP_SCREEN_CONF);
	if (duty < 0)
		duty = 0;
	else if (duty > 1)
		duty = 1;
	uint16_t duty_ = period * duty;

	switch (screen)
    {
        case CTR_LCD_TOP_SCREEN:
            CTR_LCD_CONF_BACKLIGHT_DUTY(CTR_LCD_TOP_SCREEN_CONF) = duty_;
            break;
        case CTR_LCD_BOT_SCREEN:
            CTR_LCD_CONF_BACKLIGHT_DUTY(CTR_LCD_BOT_SCREEN_CONF) = duty_;
            break;
    }
}

void ctr_lcd_backlight_period(ctr_lcd_screen screen, uint16_t period)
{
	// FIXME should we preserve the duty cycle as best as possible?
	if (period > 0x3FF)
		period = 0x3FF;
	if (period < 0x16)
		period = 0x16; // 3DS shuts down hard if period is set below this
	uint16_t current_period = 0x3FFu & CTR_LCD_CONF_BACKLIGHT_CNT(CTR_LCD_TOP_SCREEN_CONF);
	double duty = CTR_LCD_CONF_BACKLIGHT_DUTY(CTR_LCD_TOP_SCREEN_CONF) / (double)current_period;

	ctr_lcd_backlight_duty_cycle(screen, duty);
	switch (screen)
    {
        case CTR_LCD_TOP_SCREEN:
            CTR_LCD_CONF_BACKLIGHT_DUTY(CTR_LCD_TOP_SCREEN_CONF) = duty;
			CTR_LCD_CONF_BACKLIGHT_CNT(CTR_LCD_TOP_SCREEN_CONF) &= ~(uint32_t)0x3FFu;
			CTR_LCD_CONF_BACKLIGHT_CNT(CTR_LCD_TOP_SCREEN_CONF) |= period;
            break;
        case CTR_LCD_BOT_SCREEN:
            CTR_LCD_CONF_BACKLIGHT_DUTY(CTR_LCD_BOT_SCREEN_CONF) = duty;
			CTR_LCD_CONF_BACKLIGHT_CNT(CTR_LCD_BOT_SCREEN_CONF) &= ~(uint32_t)0x3FFu;
			CTR_LCD_CONF_BACKLIGHT_CNT(CTR_LCD_BOT_SCREEN_CONF) |= period;
            break;
    }
}
