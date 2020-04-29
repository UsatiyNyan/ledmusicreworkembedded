find_package(Threads REQUIRED)

add_subdirectory(base_exception)
add_subdirectory(file_descriptor)
add_subdirectory(rpi_ws281x)
add_subdirectory(serial)
add_subdirectory(parser)
add_subdirectory(player)
add_subdirectory(LED)

set(LIBS file_descriptor base_exception rpi_ws281x parser serial player PARENT_SCOPE)
