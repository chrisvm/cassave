set(INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/deps/v8")

set(SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/src")

set(V8_LIB "${CMAKE_CURRENT_LIST_DIR}/deps/v8/out/x64.release/obj.target/tools/gyp")
set(ICU_LIB "${CMAKE_CURRENT_LIST_DIR}/deps/v8/out/x64.release/obj.target/third_party/icu")

set(PROJECT_NAME "grapefruit.js")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/build")

set(OUTPUT_DIR "${CMAKE_CURRENT_LIST_DIR}/build")

cmake_minimum_required(VERSION 3.2)
project(${PROJECT_NAME})
include_directories(${INCLUDE_DIR})


###################################################################
###### v8_test Target #############################################
###################################################################

set(V8_TEST_TARGET "v8_test")
set(V8_TEST_SOURCE "${SOURCE_DIR}/v8_test")
set(SOURCE_FILES
	"${V8_TEST_SOURCE}/hello_world.cpp")

add_executable(${V8_TEST_TARGET} ${SOURCE_FILES})
set_target_properties(${V8_TEST_TARGET} 
	PROPERTIES 
	CXX_STANDARD 11
	RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

file(GLOB SNAPSHOT_BINS "${CMAKE_CURRENT_LIST_DIR}/deps/v8/out/x64.release/*.bin")
file(COPY ${SNAPSHOT_BINS} DESTINATION ${OUTPUT_DIR})

target_link_libraries(${V8_TEST_TARGET} 
	"-Wl,--start-group"
	"${V8_LIB}/libv8_base.a" 
	"${V8_LIB}/libv8_libbase.a"
	"${V8_LIB}/libv8_external_snapshot.a"
	"${V8_LIB}/libv8_libplatform.a"
	"${ICU_LIB}/libicuuc.a"
	"${ICU_LIB}/libicui18n.a"
	"${ICU_LIB}/libicudata.a"
	"-Wl,--end-group"
	"rt"
	"dl"
	"pthread")


#####################################################################
###### native_test Target ###########################################
#####################################################################

set(NATIVE_TEST_TARGET "native_test")
set(NATIVE_TEST_SOURCE "${SOURCE_DIR}/native_test")
set(SOURCE_FILES 
	"${NATIVE_TEST_SOURCE}/native_test.cpp"
	"${NATIVE_TEST_SOURCE}/array_buff_alloc.cpp" src/native_test/util_methods.cpp src/native_test/util_methods.h src/native_test/option_parser.cpp src/native_test/option_parser.h)

add_executable(${NATIVE_TEST_TARGET} ${SOURCE_FILES})
set_target_properties(${NATIVE_TEST_TARGET} 
	PROPERTIES 
	CXX_STANDARD 11
	RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

file(GLOB SNAPSHOT_BINS "${CMAKE_CURRENT_LIST_DIR}/deps/v8/out/x64.release/*.bin")
file(COPY ${SNAPSHOT_BINS} DESTINATION ${OUTPUT_DIR})

target_link_libraries(${NATIVE_TEST_TARGET} 
	"-Wl,--start-group"
	"${V8_LIB}/libv8_base.a" 
	"${V8_LIB}/libv8_libbase.a"
	"${V8_LIB}/libv8_external_snapshot.a"
	"${V8_LIB}/libv8_libplatform.a"
	"${ICU_LIB}/libicuuc.a"
	"${ICU_LIB}/libicui18n.a"
	"${ICU_LIB}/libicudata.a"
	"-Wl,--end-group"
	"pthread"
	"rt"
	"dl")