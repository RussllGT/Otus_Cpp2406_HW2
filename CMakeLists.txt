cmake_minimum_required(VERSION 3.5)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(IpFilter VERSION ${PROJECT_VESRION} LANGUAGES CXX)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

configure_file(ip_filter.tsv ip_filter.tsv)

add_executable(ip_filter main.cpp)
add_executable(test_ips test_ips.cpp)
add_library(auxiliary auxiliary.cpp)
add_library(ip_address ip_address.cpp)
add_library(filtration filtration.cpp)
add_library(readwrite readwrite.cpp)
add_library(test_stream test_stream.cpp)

set_target_properties(ip_filter auxiliary ip_address filtration readwrite PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(ip_filter
    PRIVATE "${CMAKE_BINARY_DIR}"
)

set_target_properties(test_ips auxiliary ip_address readwrite filtration test_stream PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(ip_address PRIVATE auxiliary)
target_link_libraries(readwrite PRIVATE ip_address)
target_link_libraries(filtration PRIVATE ip_address)
target_link_libraries(test_stream PRIVATE readwrite filtration)
target_link_libraries(ip_filter PRIVATE filtration readwrite)
target_link_libraries(test_ips PRIVATE ${Boost_LIBRARIES} test_stream)

if (MSVC)
    target_compile_options(auxiliary PRIVATE /W4)
    target_compile_options(ip_address PRIVATE /W4)
    target_compile_options(filtration PRIVATE /W4)
    target_compile_options(readwrite PRIVATE /W4)
    target_compile_options(test_stream PRIVATE /W4)
    target_compile_options(ip_filter PRIVATE /W4)
    target_compile_options(test_ips PRIVATE /W4)
else ()
    target_compile_options(auxiliary PRIVATE -Wall -Wextra -pedantic -Werror)
    target_compile_options(ip_address PRIVATE -Wall -Wextra -pedantic -Werror)
    target_compile_options(filtration PRIVATE -Wall -Wextra -pedantic -Werror)
    target_compile_options(readwrite PRIVATE -Wall -Wextra -pedantic -Werror)
    target_compile_options(test_stream PRIVATE -Wall -Wextra -pedantic -Werror)
    target_compile_options(ip_filter PRIVATE -Wall -Wextra -pedantic -Werror)
    target_compile_options(test_ips PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()

add_test(test_ips test_ips)