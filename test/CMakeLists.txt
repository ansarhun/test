add_executable(tst_lib tst_lib.cpp)
target_link_libraries(tst_lib gtest gtest_main pthread MyLib)

# From: http://stackoverflow.com/a/7264990
add_custom_target(check)
macro(run_test test_target)
	add_custom_target(${test_target}_runtest
		COMMAND ${test_target} \$\(ARGS\)
		DEPENDS ${test_target}
		WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")
	add_dependencies(check ${test_target}_runtest)
endmacro()

run_test(tst_lib)