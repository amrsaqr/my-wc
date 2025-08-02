add_library(my_wc_lib args_reader.cpp options.cpp counts.cpp counter.cpp)

target_include_directories(my_wc_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
