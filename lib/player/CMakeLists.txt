add_library(player STATIC
        src/player.cpp
        )
target_include_directories(player PUBLIC include)
target_link_libraries(player led geometry parser base_exception fixed_queue job_thread)
