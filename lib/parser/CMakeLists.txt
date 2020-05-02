add_library(parser STATIC
        src/parser.cpp
        src/config.cpp
        )
target_include_directories(parser PUBLIC include)
target_link_libraries(parser PUBLIC serial geometry job_thread fixed_queue)
