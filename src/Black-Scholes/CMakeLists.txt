set(Sources
    BlackScholes.cpp
)

add_library(blackScholes ${Sources})

target_include_directories(blackScholes 
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR})

# target_link_libraries(matcher
#     PUBLIC
#     order
#     )

# if(BUILD_TESTING)
#     add_subdirectory(test)
# endif()
