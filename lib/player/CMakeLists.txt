add_library(player STATIC
        src/player.cpp
        src/polygon.cpp
        )
target_include_directories(player PUBLIC include)
#target_link_libraries(player rpi_ws281x)
