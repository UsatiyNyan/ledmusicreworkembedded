add_library(LED STATIC src/LED.cpp)
target_include_directories(LED PUBLIC include)
target_link_libraries(LED rpi_ws281x)
