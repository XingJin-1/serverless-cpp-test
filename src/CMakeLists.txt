include_directories(${PROJECT_SOURCE_DIR}/libhello)
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/lib)

link_directories(${PROJECT_SOURCE_DIR}/libhello)
link_directories(${PROJECT_SOURCE_DIR}/lib)

# Add main.cpp file of project root directory as source file
set(APP_SRC app.cpp)
# Add executable target with source files listed in SOURCE_FILES variable
add_executable(hello ${APP_SRC})

find_package(Boost REQUIRED) 
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
    target_link_libraries(hello ${Boost_LIBRARIES})
endif()

target_link_libraries(hello libhello)
target_link_libraries(hello ${PROJECT_SOURCE_DIR}/lib/curl_a_debug)