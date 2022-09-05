
lodge = library('lodge', sources : [ 'lodge.hpp', 'log_item.hpp', 'queue.hpp', 'levels.hpp', 'sinks.hpp' ],
  dependencies : [fmt_dep], install : true)

lodge_dep = declare_dependency(dependencies: [fmt_dep],
  include_directories : include_directories('.'), link_with : lodge )
