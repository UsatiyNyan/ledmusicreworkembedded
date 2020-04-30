add_library(polygon STATIC
        src/polygon.cpp
        src/circle.cpp
        )
target_include_directories(polygon PUBLIC include)
target_link_libraries(polygon PUBLIC base_exception)
