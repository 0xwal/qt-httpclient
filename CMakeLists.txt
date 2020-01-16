cmake_minimum_required(VERSION 3.15)

include(GNUInstallDirs)

set(BUILD_SHARED_LIBS FALSE)

project(HttpClient VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_COLOR_MAKEFILE ON)

set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "C:/Qt/5.13.2/mingw73_32")

find_package(Qt5 COMPONENTS Widgets Network)

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

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/include")

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets Qt5::Network)

set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/out")

install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        )


