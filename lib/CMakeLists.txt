find_package(Threads REQUIRED)

add_subdirectory(base_exception)
add_subdirectory(file_descriptor)
add_subdirectory(rpi_ws281x)
add_subdirectory(serial)
add_subdirectory(geometry)
add_subdirectory(led)
add_subdirectory(parser)
add_subdirectory(player)

set(LIBS base_exception
        file_descriptor
        rpi_ws281x
        serial
        geometry
        led
        parser
        player
         PARENT_SCOPE)
