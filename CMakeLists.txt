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
        include/HttpClient.h
        include/HttpContentInterface.h
        include/HttpGlobalRequestOptions.h
        include/HttpJsonContent.h
        include/HttpQueryContent.h
        include/HttpRequest.h
        include/HttpResponse.h
        include/HttpUtils.h
        source/HttpClient.cpp
        source/HttpGlobalRequestOptions.cpp
        source/HttpJsonContent.cpp
        source/HttpQueryContent.cpp
        source/HttpRequest.cpp
        source/HttpResponse.cpp
        source/HttpUtils.cpp)


set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})

target_compile_definitions(${PROJECT_NAME} PUBLIC HTTPCLIENT_VERSION="${PROJECT_VERSION}")

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Network)
