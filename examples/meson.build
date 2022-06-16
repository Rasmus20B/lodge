

fmt_dep = dependency('fmt') 

fmt_lib = library('fmt', install : true)

examples_src = [ 'example1.cpp']
e = executable('example1',
                  sources : [ examples_src ],
                  dependencies : [ fmt_dep ],
                  link_with : [ fmt_lib ]
)

