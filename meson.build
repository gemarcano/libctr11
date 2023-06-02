project('libctr11', 'c',
  default_options: [
    'b_lto=true',
    'b_staticpic=false',
    'c_std=c17',
    'warning_level=3',
  ],
  license: ['GPL-2.0-or-later'],
  version: '0.0.1')

link_args = [
  '-Wl,--gc-sections', '-fno-exceptions',
]

sources = files([
  'src/ctr11_gpu.c',
  'src/ctr_circular_buffer.c',
  'src/ctr_console.c',
  'src/ctr_firm.c',
  'src/ctr_freetype.c',
  'src/ctr_headers.c',
  'src/ctr_hid.c',
  'src/ctr_init.c',
  'src/ctr_pxi.c',
  'src/ctr_screen.c',
  'src/ctr_system.c',
  'src/i2c.c',
  'src/ctr_lcd.c',
  'src/crt0.s',
])

header_files = files([
'include/ctr11/ctr_circular_buffer.h',
'include/ctr11/ctr_console.h',
'include/ctr11/ctr_firm.h',
'include/ctr11/ctr_freetype.h',
'include/ctr11/ctr_headers.h',
'include/ctr11/ctr_hid.h',
'include/ctr11/ctr_pxi.h',
'include/ctr11/ctr_screen.h',
'include/ctr11/ctr_system.h',
'include/ctr11/i2c.h',
'include/ctr11/ctr_lcd.h',
])

# FIXME do not install fatfs headers
install_subdir('include', install_dir: 'include', strip_directory: true)

ctr_core = dependency('ctr_core')
ctrelf = dependency('ctrelf')

lib = library(
  'ctr11', sources,
  dependencies: [ctr_core, ctrelf],
  include_directories: 'include',
  install: true,
)

pkg = import('pkgconfig')

pkg.generate(lib,
  subdirs: [ 'ctr11', '.' ],
  description: 'Baremetal ARM11 library for the Nintendo 3DS',
  url: 'https://github.com/gemarcano/' + meson.project_name(),
)
