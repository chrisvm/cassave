set(INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/deps/v8")

set(SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/src")

set(V8_LIB "${CMAKE_CURRENT_LIST_DIR}/deps/v8/out/x64.release/obj.target/tools/gyp")
set(ICU_LIB "${CMAKE_CURRENT_LIST_DIR}/deps/v8/out/x64.release/obj.target/third_party/icu")

set(PROJECT_NAME "cassave.js")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/build")

set(OUTPUT_DIR "${CMAKE_CURRENT_LIST_DIR}/build")

cmake_minimum_required(VERSION 3.2)
project(${PROJECT_NAME})
include_directories(${INCLUDE_DIR})


#####################################################################
###### cassave Target ###########################################
#####################################################################

set(NATIVE_TEST_TARGET "cassave")
set(NATIVE_TEST_SOURCE "${SOURCE_DIR}")
set(SOURCE_FILES
	"${NATIVE_TEST_SOURCE}/cassave.cpp"
	"${NATIVE_TEST_SOURCE}/array_buff_alloc.cpp"
	"${NATIVE_TEST_SOURCE}/util_methods.cpp"
	"${NATIVE_TEST_SOURCE}/option_parser.cpp"
	"${NATIVE_TEST_SOURCE}/global_funcs.cpp"
	"${NATIVE_TEST_SOURCE}/v8_methods.cpp"
		src/native_binding.h
		src/native_binding.cpp
		src/cassave_io.h
		src/cassave_io.cpp
        src/cassave_natives.cpp
        src/cassave_natives.h
        src/native_require.cpp)

add_executable(${NATIVE_TEST_TARGET} ${SOURCE_FILES})
set_target_properties(${NATIVE_TEST_TARGET}
	PROPERTIES
	CXX_STANDARD 11
	RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

file(GLOB SNAPSHOT_BINS "${CMAKE_CURRENT_LIST_DIR}/deps/v8/out/x64.release/*.bin")
file(COPY ${SNAPSHOT_BINS} DESTINATION ${OUTPUT_DIR})

if (APPLE)
    set(V8_LIB "${INCLUDE_DIR}/out/x64.release")
    set(ICU_LIB "${V8_LIB}")

    include_directories("${INCLUDE_DIR}/include")
    target_link_libraries(${NATIVE_TEST_TARGET}
    "${V8_LIB}/libv8_base.a"
    "${V8_LIB}/libv8_libbase.a"
    "${V8_LIB}/libv8_external_snapshot.a"
    "${V8_LIB}/libv8_libplatform.a"
    "${ICU_LIB}/libicuuc.a"
    "${ICU_LIB}/libicui18n.a"
    "${ICU_LIB}/libicudata.a"
    "pthread"
    "dl")
else()
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
endif()
