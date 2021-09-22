cmake_minimum_required(VERSION 2.8)
project (crow_template)

include_directories(${CMAKE_SOURCE_DIR}/libhello)
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/lib)

link_directories(${CMAKE_SOURCE_DIR}/libhello)
link_directories(${CMAKE_SOURCE_DIR}/lib)
#set(YOUR_LIBRARIES ${YOUR_LIBRARIES} ${CMAKE_SOURCE_DIR}/lib/libcurl_a_debug.lib)
#set(YOUR_LIBRARIES ${YOUR_LIBRARIES} ${CMAKE_SOURCE_DIR}/lib/AdvAPI32.Lib)
#set(YOUR_LIBRARIES ${YOUR_LIBRARIES} ${CMAKE_SOURCE_DIR}/lib/Crypt32.Lib)
#set(YOUR_LIBRARIES ${YOUR_LIBRARIES} ${CMAKE_SOURCE_DIR}/lib/normaliz.lib)
#set(YOUR_LIBRARIES ${YOUR_LIBRARIES} ${CMAKE_SOURCE_DIR}/lib/Wldap32.Lib)
#set(YOUR_LIBRARIES ${YOUR_LIBRARIES} ${CMAKE_SOURCE_DIR}/lib/WS2_32.Lib)

# Add main.cpp file of project root directory as source file
set(APP_SRC app.cpp)
# Add executable target with source files listed in SOURCE_FILES variable
add_executable(example ${APP_SRC})

target_link_libraries(example ${Boost_LIBRARIES})
target_link_libraries(example ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(example libhello)
target_link_libraries(example ${YOUR_LIBRARIES})
target_link_libraries(example ${CURL_LIBRARIES})