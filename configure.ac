AC_INIT([libctr11], [0.0.1], [], [])
AM_INIT_AUTOMAKE([foreign no-dist-gzip dist-xz subdir-objects])

#Find AR and RANLIB for lto support before initializing libtool
AC_CHECK_TOOL([AR],gcc-ar)
AC_CHECK_TOOL([RANLIB],gcc-ranlib)

AC_PROG_CC
AC_PROG_CXX
AM_PROG_AS
AC_CHECK_TOOL([OBJCOPY],objcopy)

AX_CFLAGS_WARN_ALL
AX_COMPILER_FLAGS(,,,[-Wpedantic -Wall -Wextra -Wcast-align -Wcast-qual\
 -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op\
 -Wmissing-declarations -Wmissing-include-dirs -Wredundant-decls\
 -Wshadow -Wsign-conversion -Wstrict-overflow=5 -Wswitch-default\
 -Wundef -Wno-unused -fstrict-aliasing])
AX_CHECK_COMPILE_FLAG(-Wno-declaration-after-statement,
	[WARN_CFLAGS="$WARN_CFLAGS -Wno-declaration-after-statement -Wno-error=declaration-after-statement"], [], [], [])

cflags_save="$CFLAGS"
cxxflags_save="$CXXFLAGS"

C11FLAGS="-mcpu=mpcore -mlittle-endian -march=armv6k -mtune=mpcore -mfloat-abi=hard -mtp=soft"
AC_SUBST(C11FLAGS)
CFLAGS="$C11FLAGS $CFLAGS"
CXXFLAGS="$C11FLAGS $CXXFLAGS"
LT_INIT

CFLAGS="$cflags_save"
CXXFLAGS="$cxxflags_save"

AC_CONFIG_FILES([Makefile src/Makefile libctr11.pc])

AC_OUTPUT

