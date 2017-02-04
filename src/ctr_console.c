#include <ctr11/ctr_console.h>

#include <sys/iosupport.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

//FIXME Freetype interactions are wonky. I'm not handling the cases where metrics can be negative due to changes in text orientation

#include <ctr11/ctr_freetype.h>

int ctr_console_initialize(void *surface)
{
	return ctr_core_console_initialize(surface);
}

short ctr_console_get_char_width(char c)
{
	return ctr_core_console_get_char_width(c);
}

unsigned int ctr_console_get_char_height(void)
{
	return ctr_core_console_get_char_height();
}

void ctr_console_draw(char c)
{
	ctr_core_console_draw(c);
}

void ctr_console_clear(void)
{
	ctr_core_console_clear();
}

