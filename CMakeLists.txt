cmake_minimum_required(VERSION 3.15)

project(HttpClient VERSION 1.0.0)

set(CMAKE_CONFIGURATION_TYPES Debug Release)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_COLOR_MAKEFILE ON)

set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH $ENV{QT_PATH})

find_package(Qt5 COMPONENTS Network)

add_library(${PROJECT_NAME}
        HttpClient/include/HttpClient.h
        HttpClient/include/HttpContentInterface.h
        HttpClient/include/HttpGlobalRequestOptions.h
        HttpClient/include/HttpJsonContent.h
        HttpClient/include/HttpQueryContent.h
        HttpClient/include/HttpRequest.h
        HttpClient/include/HttpResponse.h
        HttpClient/include/HttpUtils.h
        HttpClient/source/HttpClient.cpp
        HttpClient/source/HttpGlobalRequestOptions.cpp
        HttpClient/source/HttpJsonContent.cpp
        HttpClient/source/HttpQueryContent.cpp
        HttpClient/source/HttpRequest.cpp
        HttpClient/source/HttpResponse.cpp
        HttpClient/source/HttpUtils.cpp)


set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})

target_compile_definitions(${PROJECT_NAME} PUBLIC HTTPCLIENT_VERSION="${PROJECT_VERSION}")

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/HttpClient/include")

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Network)

add_subdirectory(test)
enable_testing()
add_test(${PROJECT_NAME} MyTest COMMAND Test)
