cmake_minimum_required(VERSION 3.28)
project(my_wc)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)

add_executable(my_wc src/main.cpp)
target_link_libraries(my_wc PRIVATE my_wc_lib)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/52eb8108c5bdec04579160ae17225d66034bd723.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(my_wc_test
        test/args_reader_test.cpp
        test/options_test.cpp
        test/counts_test.cpp)
target_link_libraries(my_wc_test PRIVATE my_wc_lib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(my_wc_test)
