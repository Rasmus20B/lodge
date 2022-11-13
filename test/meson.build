gtest_proj = subproject('gtest') 

gtest_dep = dependency('gtest', main : true, required : false) 

gtest_lib = library('gtest', install : true)

tests_src = [ 'main_test.cpp', 'queue_test.cpp', 'queue_mc_test.cpp']
e = executable('lodge_tests',
                  sources : tests_src, 
                  dependencies : [ gtest_dep, lodge_dep],
                  link_with : [gtest_lib ])

test('gtest test', e)
