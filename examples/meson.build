

fmt_dep = dependency('fmt') 

fmt_lib = library('fmt', install : true)

examples_src = [ 'example.cpp']
e = executable('example',
                  sources : [ examples_src ],
                  dependencies : [ fmt_dep, lodge_dep],
                  link_with : [ fmt_lib, lodge_lib ]
)

