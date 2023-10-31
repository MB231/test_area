project(test LANGUAGES CXX C)

find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)
# set source and dependency variables
set(TEST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

file(GLOB TEST_HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")

add_executable(${PROJECT_NAME} ${TEST_SOURCES} ${TEST_HEADERS})
target_link_libraries(${PROJECT_NAME} CURL::libcurl)
target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json)

# link header/source file dir. Needed for "-I" to be set in linker to correctly find out of dir files.
target_include_directories(${PROJECT_NAME}
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/include",
        ${CURL_INCLUDE_DIRS}
)

