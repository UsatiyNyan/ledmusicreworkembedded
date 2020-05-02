add_library(led STATIC
        src/led.cpp)
target_include_directories(led PUBLIC include)
target_link_libraries(led PUBLIC rpi_ws281x geometry)
