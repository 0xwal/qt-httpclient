
project(HttpClientTest)

execute_process(COMMAND sh -c "../httpbin.sh")

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(${PROJECT_NAME}
        main.cpp
        HttpClientTest.cpp)

target_compile_definitions(${PROJECT_NAME} PRIVATE TEST_URL="http://localhost:80")

target_link_libraries(${PROJECT_NAME} PRIVATE HttpClient)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets Qt5::Network)
