add_library(led STATIC
        src/led.cpp)
target_include_directories(led PUBLIC include)
target_link_libraries(led rpi_ws281x)
