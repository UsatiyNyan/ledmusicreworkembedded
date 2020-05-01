find_package(Threads REQUIRED)

add_subdirectory(base_exception) #
add_subdirectory(file_descriptor) #
add_subdirectory(serial) #
add_subdirectory(parser)
add_subdirectory(rpi_ws281x) #
add_subdirectory(geometry) #
add_subdirectory(led) #
add_subdirectory(fixed_queue)
add_subdirectory(player)
add_subdirectory(job_thread)

set(LIBS base_exception
        file_descriptor
        serial
        parser
        rpi_ws281x
        geometry
        led
        fixed_queue
        player
        job_thread
         PARENT_SCOPE)
