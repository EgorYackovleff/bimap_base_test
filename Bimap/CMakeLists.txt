cmake_minimum_required(VERSION 3.2)

include(__17_and_warnings.cmake)
include(__find_sources.cmake)

project(bimap VERSION 1.0 LANGUAGES CXX)

create_app(${PROJECT_NAME} 17)

add_subdirectory(googletest)

target_link_libraries(${PROJECT_NAME}
    gtest
)




