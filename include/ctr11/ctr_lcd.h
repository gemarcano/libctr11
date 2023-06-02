// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright: Gabriel Marcano, 2023

#ifndef CTR_LCD_H_
#define CTR_LCD_H_

#include <stdbool.h>
#include <stdint.h>

#define CTR_LCD_BASE_ADDR (0x10202000u)
#define CTR_LCD_REG4(OFFSET) (*(volatile uint32_t*)(CTR_LCD_BASE_ADDR + OFFSET))
#define CTR_LCD_REGARR(OFFSET) ((volatile uint32_t*)(CTR_LCD_BASE_ADDR + OFFSET))
#define CTR_LCD_PARALLAX_ENABLE CTR_LCD_REG4(0x0)
#define CTR_LCD_UNKNOWN1 CTR_LCD_REG4(0x4)
#define CTR_LCD_TOP_SCREEN_CONF CTR_LCD_REGARR(0x200)
#define CTR_LCD_BOT_SCREEN_CONF CTR_LCD_REGARR(0xA00)
#define CTR_LCD_UNKNOWN2 CTR_LCD_REG64(0x1200)

#define CTR_LCD_CONF_REG(SCREEN, OFFSET) (SCREEN[OFFSET])
#define CTR_LCD_CONF_FILL_COLOR(SCREEN) CTR_LCD_CONF_REG(SCREEN, 1u)
#define CTR_LCD_CONF_BACKLIGHT_DUTY(SCREEN) CTR_LCD_CONF_REG(SCREEN, 0x10u)
#define CTR_LCD_CONF_BACKLIGHT_CNT(SCREEN) CTR_LCD_CONF_REG(SCREEN, 0x11u)
#define CTR_LCD_CONF_N3DS_CALIBRATION(SCREEN) ((SCREEN) + 0x40u)

typedef struct
{
    uint8_t red, green, blue;
} ctr_lcd_color;

typedef enum
{
    CTR_LCD_TOP_SCREEN,
    CTR_LCD_BOT_SCREEN,
} ctr_lcd_screen;

void ctr_lcd_set_fill_color(ctr_lcd_screen screen, ctr_lcd_color color, bool enable);
void ctr_lcd_backlight_duty_cycle(ctr_lcd_screen screen, double duty);
void ctr_lcd_backlight_period(ctr_lcd_screen screen, uint16_t period);

#endif//CTR_LCD_H_
