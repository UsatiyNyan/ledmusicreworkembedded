find_package(Threads REQUIRED)

add_subdirectory(rpi_ws281x)
add_subdirectory(parser)
add_subdirectory(serial)
add_subdirectory(player)
add_subdirectory(LED)

set(LIBS rpi_ws281x parser serial player PARENT_SCOPE)
