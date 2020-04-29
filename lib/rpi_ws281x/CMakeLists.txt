file(GLOB rpi_SRC
        "src/*.c"
        )
add_library(rpi_ws281x STATIC ${rpi_SRC})
target_include_directories(rpi_ws281x PUBLIC include)