libexpr_src = ['lib/eval.cc', 'lib/value.cc']
libexpr_inc = [include_directories('include')]
libexpr_deps = [gobject, libnix_expr]

libexpr_shlib = shared_library('nix-gobject-util', libexpr_src,
  dependencies: libexpr_deps,
  include_directories: libexpr_inc)
