project('gnome-builder', 'c',
  license: 'GPL3+',
  version: '3.23.90',
  meson_version: '>= 0.37.0',
  default_options: [
    'c_std=gnu11',
    'cpp_std=c++11',
    'warning_level=2',
  ],
)

version_split = meson.project_version().split('.')
MAJOR_VERSION = version_split[0]
MINOR_VERSION = version_split[1]
MICRO_VERSION = version_split[2]

conf = configuration_data()
conf.set_quoted('PACKAGE_NAME', 'gnome-builder')
conf.set_quoted('PACKAGE_VERSION', meson.project_version())
conf.set_quoted('PACKAGE_STRING', 'gnome-builder-' + meson.project_version())
conf.set_quoted('PACKAGE_DATADIR', join_paths(get_option('prefix'), get_option('datadir')))
conf.set_quoted('PACKAGE_LIBDIR', join_paths(get_option('prefix'), get_option('libdir')))
conf.set_quoted('PACKAGE_LOCALE_DIR', join_paths(get_option('prefix'), get_option('datadir'), 'locale'))
conf.set_quoted('PACKAGE_LIBEXECDIR', join_paths(get_option('prefix'), get_option('libexecdir')))

conf.set('GETTEXT_PACKAGE', 'PACKAGE_NAME')
conf.set('LOCALEDIR', 'PACKAGE_LOCALE_DIR')

conf.set10('ENABLE_NLS', true) # Always enabled

# We should probably avoid using these
conf.set_quoted('SRCDIR', meson.source_root())
conf.set_quoted('BUILDDIR', meson.build_root())

add_global_arguments([
  '-DHAVE_CONFIG_H',
  '-I' + meson.build_root(), # config.h
  '-D_GNU_SOURCE',
], language: 'c')

cc = meson.get_compiler('c')
global_c_args = []
test_c_args = [
  '-Wcast-align',
  '-Wdeclaration-after-statement',
  ['-Werror=format-security', '-Werror=format=2'],
  '-Wformat-nonliteral',
  '-Wformat-security',
  '-Wmissing-include-dirs',
  '-Wnested-externs',
  '-Wno-missing-field-initializers',
  '-Wno-sign-compare',
  '-Wno-strict-aliasing',
  '-Wno-uninitialized',
  '-Wno-unused-parameter',
  '-Wpointer-arith',
  '-Wredundant-decls',
  '-Wshadow',
  '-Wswitch-default',
  '-Wswitch-enum',
  '-Wundef',
]
if get_option('buildtype') != 'plain'
  test_c_args += '-fstack-protector-strong'
endif
if get_option('enable_profiling')
  test_c_args += '-pg'
endif

foreach arg: test_c_args
  if cc.has_multi_arguments(arg)
    global_c_args += arg
  endif
endforeach
add_project_arguments(
  global_c_args,
  language: 'c'
)

global_link_args = []
test_link_args = [
  '-Wl,-z,relro',
  '-Wl,-z,now',
]
if not get_option('buildtype').startswith('debug')

  # TODO: Maybe reuse 'b_ndebug' option
  add_global_arguments([
    '-DG_DISABLE_CAST_CHECKS',
    '-DG_DISABLE_ASSERT',
    '-DG_DISABLE_CHECKS',
  ], language: 'c')

  test_link_args += [
    '-Wl,-Bsymbolic',
    '-fno-plt',
  ]

endif

foreach arg: test_link_args
  if cc.has_argument(arg)
    global_link_args += arg
  endif
endforeach
add_project_link_arguments(
  global_link_args,
  language: 'c'
)

if cc.has_function('sched_getcpu')
  conf.set('HAVE_SCHED_GETCPU', true)
endif

configure_file(
  output: 'config.h',
  configuration: conf
)

# Commonly used deps
libgio_dep = dependency('gio-2.0', version: '>= 2.50.0')
libgtk_dep = dependency('gtk+-3.0', version: '>= 3.22.1')
libpeas_dep = dependency('libpeas-1.0', version: '>= 1.18.0')
libm_dep = cc.find_library('m', required: false)
libjson_glib_dep = dependency('json-glib-1.0', version: '>= 1.2.0')

if get_option('with_flatpak') or get_option('with_git')
  libgit_dep = dependency('libgit2-glib-1.0', version: '>= 0.25.0')

  libgit_thread_safe_check = '''
    #include <libgit2-glib/ggit.h>
    int main(int argc, const char *argv[])
    {
      ggit_init ();
      return ((ggit_get_features() & GGIT_FEATURE_THREADS) != 0) ? 0 : 1;
    }
  '''
  res = cc.run(libgit_thread_safe_check,
    dependencies: libgit_dep,
  )
  if res.returncode() != 0
    error('libgit2 was not compiled with -DTHREADSAFE:BOOL=ON')
  endif

  libgit_ssh_check = '''
    #include <libgit2-glib/ggit.h>
    int main(int argc, const char *argv[])
    {
      ggit_init ();
      return ((ggit_get_features() & GGIT_FEATURE_SSH) != 0) ? 0 : 1;
    }
  '''
  res = cc.run(libgit_ssh_check,
    dependencies: libgit_dep,
  )
  if res.returncode() != 0
    error('libgit2 was not compiled with SSH support')
  endif
endif


pkglibdir_abs = join_paths(get_option('prefix'), get_option('libdir'), 'gnome-builder')
pkglibdir = join_paths(get_option('libdir'), 'gnome-builder')
pkggirdir = join_paths(get_option('datadir'),'gnome-builder', 'gir-1.0')
pkgtypelibdir = join_paths(get_option('libdir'), 'gnome-builder', 'girepository-1.0')
pkgvapidir = join_paths(get_option('datadir'), 'gnome-builder/vapi')
gnome = import('gnome')

subdir('data')
subdir('data/fonts')
subdir('data/gsettings')
subdir('data/icons')
subdir('data/style-schemes')
subdir('contrib/egg')
subdir('contrib/gd')
subdir('contrib/jsonrpc-glib')
subdir('contrib/libeditorconfig')
subdir('contrib/nautilus')
subdir('contrib/pnl')
subdir('contrib/rg')
subdir('contrib/search')
subdir('contrib/tmpl')
subdir('contrib/xml')
subdir('contrib/gstyle') # Depends on libsearch/libxml
subdir('libide')
subdir('plugins')
subdir('po')
subdir('tests')
subdir('tools')

exe_link_args = [
  '-pie',
]
exe_c_args = [
  '-fPIE',
]

executable('gnome-builder', 'src/main.c',
  gui_app: true,
  install: true,
  c_args: exe_c_args,
  link_args: exe_link_args,
  install_rpath: pkglibdir_abs,
  dependencies: libide_deps + [libide_dep],
)

executable('gnome-builder-cli', 'src/main.c',
  gui_app: false,
  install: true,
  c_args: exe_c_args,
  link_args: exe_link_args,
  install_rpath: pkglibdir_abs,
  dependencies: libide_deps + [libide_dep],
)

executable('gnome-builder-worker', 'src/main.c',
  gui_app: false,
  install: true,
  install_dir: get_option('libexecdir'),
  c_args: exe_c_args,
  link_args: exe_link_args,
  install_rpath: pkglibdir_abs,
  dependencies: libide_deps + [libide_dep],
)

meson.add_install_script('build/meson/meson_post_install.py')
