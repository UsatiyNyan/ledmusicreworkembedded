add_library(parser STATIC src/parser.cpp)
target_include_directories(parser PUBLIC include)
target_link_libraries(parser serial)
