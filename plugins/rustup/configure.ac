# --enable-rustup-plugin=yes/no
AC_ARG_ENABLE([rustup-plugin],
              [AS_HELP_STRING([--enable-rustup-plugin=@<:@yes/no@:>@],
                              [Build with support for RustUp integration.])],
              [enable_rustup_plugin=$enableval],
              [enable_rustup_plugin=yes])

# for if ENABLE_RUSTUP_PLUGIN in Makefile.am
AM_CONDITIONAL(ENABLE_RUSTUP_PLUGIN, test x$enable_rustup_plugin = xyes)

# Ensure our makefile is generated by autoconf
AC_CONFIG_FILES([plugins/rustup/Makefile])
