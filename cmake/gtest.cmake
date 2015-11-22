########################### GTEST
# Enable ExternalProject CMake module
include(ExternalProject)

function(import_library _package _name _path)
	add_library(${_name} UNKNOWN IMPORTED)
	set_property(TARGET ${_name} PROPERTY IMPORTED_LOCATION ${_path})
	add_dependencies(${_name} ${_package})
endfunction()

if(WIN32)
	set(GTEST_EXTRA_PARAMS "-Dgtest_force_shared_crt=ON")
else()
	set(GTEST_EXTRA_PARAMS "-DCMAKE_CXX_FLAGS=-fPIC -D_GLIBCXX_USE_CXX11_ABI=0")
endif()

# Add gtest
# http://stackoverflow.com/questions/9689183/cmake-googletest
externalproject_add(
	googletest
	URL http://googletest.googlecode.com/files/gtest-1.7.0.zip
	# TIMEOUT 10
	# # Force separate output paths for debug and release builds to allow easy
	# # identification of correct lib in subsequent TARGET_LINK_LIBRARIES commands
	# CMAKE_ARGS -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=DebugLibs
	#            -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=ReleaseLibs
	#            -Dgtest_force_shared_crt=ON
	# Disable install step
	CMAKE_ARGS ${GTEST_EXTRA_PARAMS} -DCMAKE_BUILD_TYPE=Release -DGTEST_LINKED_AS_SHARED_LIBRARY=1
	INSTALL_COMMAND ""
	# Wrap download, configure and build steps in a script to log output
	LOG_DOWNLOAD ON
	LOG_CONFIGURE ON
	LOG_BUILD ON)

# Specify include dir
externalproject_get_property(googletest source_dir)
set(GTEST_INCLUDE_DIR ${source_dir}/include)

# Library
externalproject_get_property(googletest binary_dir)
set(GTEST_LIBRARY_PATH ${binary_dir}/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_STATIC_LIBRARY_SUFFIX})
set(GTEST_LIBRARY gtest)
import_library(googletest ${GTEST_LIBRARY} ${GTEST_LIBRARY_PATH})

set(GTEST_MAIN_LIBRARY_PATH ${binary_dir}/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_STATIC_LIBRARY_SUFFIX})
set(GTEST_MAIN_LIBRARY gtest_main)
import_library(googletest ${GTEST_MAIN_LIBRARY} ${GTEST_MAIN_LIBRARY_PATH})

include_directories(SYSTEM ${GTEST_INCLUDE_DIR})
