if get_option('with_sysprof')

sysprof_resources = gnome.compile_resources(
  'gbp-sysprof-resources',
  'sysprof.gresource.xml',
  c_name: 'gbp_sysprof',
)

sysprof_sources = [
  sysprof_resources[0],
  sysprof_resources[1],
  'gbp-sysprof-plugin.c',
  'gbp-sysprof-perspective.c',
  'gbp-sysprof-perspective.h',
  'gbp-sysprof-workbench-addin.c',
  'gbp-sysprof-workbench-addin.h',
]

sysprof_deps = plugin_deps + [
  dependency('sysprof-ui-2', version: '>=3.21.90'),
]

shared_module('sysprof-plugin', sysprof_sources,
  dependencies: sysprof_deps,
  link_args: plugin_link_args,
  link_depends: plugin_link_deps,
  install: true,
  install_dir: plugindir,
)

install_data('sysprof.plugin', install_dir: plugindir)

endif
