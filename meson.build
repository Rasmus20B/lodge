project ( 
  'lodge',
  'cpp',
  version: '0.0.1',
  license: 'GPL2',
  default_options: [
    'buildtype=release',
    'warning_level=3',
    'cpp_std=c++20'
  ]
)

is_subproject = meson.is_subproject()
fmt_proj = subproject('fmt')
fmt_dep = dependency('fmt', required : true) 
fmt_lib = library('fmt', install : true )


subdir('src')

build_tests = get_option('build_tests') and not is_subproject
if build_tests
subdir('test')
endif

build_examples = get_option('build_examples') and not is_subproject
if build_examples
subdir('examples')
endif


