add_library(my_wc_lib args_reader.cpp options.cpp counts.cpp counter.cpp driver.cpp count_result.h)

target_include_directories(my_wc_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
