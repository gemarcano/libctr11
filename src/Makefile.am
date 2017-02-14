include $(top_srcdir)/common.mk

lib_LTLIBRARIES = libctr11.la
libctr11_la_CFLAGS=$(AM_CFLAGS) $(C11FLAGS)
libctr11_la_CXXFLAGS=$(AM_CXXFLAGS) $(C11FLAGS)
libctr11_la_CCASFLAGS = -I$(top_srcdir)/data
#payload_stage1_elf_CCASFLAGS = -I$(top_srcdir)/data
libctr11_la_SOURCES = crt0.s ctr_pxi.c ctr_screen.cpp i2c.c ctr_system.c \
	$(top_srcdir)/data/ctr_font_data.s ctr_freetype.c ctr_console.c ctr_hid.c \
	ctr_circular_buffer.c ctr_headers.c ctr_firm.c ctr_init.c ctr_surface.cpp \
	ctr_window.cpp ctr_mmu.c ctr_cache.s ctr_mmu_.s
libctr11_la_LDFLAGS=$(AM_LDFLAGS) -static

libctr11dir=$(pkgdatadir)
libctr11_DATA=linker.ld

EXTRA_DIST=screen_init.ld

includedirectory = $(top_srcdir)/include

ctrincludedir = $(includedir)/ctr11

ctrinclude_HEADERS = $(includedirectory)/ctr11/ctr_pxi.h \
$(includedirectory)/ctr11/ctr_screen.h \
$(includedirectory)/ctr11/i2c.h \
$(includedirectory)/ctr11/ctr_system.h \
$(includedirectory)/ctr11/ctr_freetype.h \
$(includedirectory)/ctr11/ctr_console.h \
$(includedirectory)/ctr11/ctr_hid.h \
$(includedirectory)/ctr11/ctr_circular_buffer.h \
$(includedirectory)/ctr11/ctr_headers.h \
$(includedirectory)/ctr11/ctr_firm.h \
$(includedirectory)/ctr11/ctr_surface.h \
$(includedirectory)/ctr11/ctr_window.h \
$(includedirectory)/ctr11/ctr_mmu.h \
$(includedirectory)/ctr11/ctr_cache.h

