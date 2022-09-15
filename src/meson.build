
lodge = library('lodge', sources : [ 'lodge.h', 'lodge.cc', 'queue.h', 'levels.h', 'sinks.h', 'sinks.cc', 'log_item.h' ],
  dependencies : [fmt_dep], install : true, cpp_args : '-DUSE_STD_FUNCTION') 

lodge_dep = declare_dependency(dependencies: [fmt_dep],
  include_directories : include_directories('.'), link_with : lodge )
