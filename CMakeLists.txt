cmake_minimum_required(VERSION 3.14)

project(SmallTask5+6 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(STATUS "TESTS_BUILD_TYPE ${TESTS_BUILD_TYPE}")

if (TESTS_BUILD_TYPE MATCHES ASAN)
    set(COMPILE_OPTS -Wall -Wextra -Werror -pedantic -pedantic-errors -O1 -fsanitize=address -fno-omit-frame-pointer
        -fno-inline -fno-sanitize-recover=all)
    set(LINK_OPTS -fsanitize=address)
endif()
if (TESTS_BUILD_TYPE MATCHES MSAN)
    set(COMPILE_OPTS -Wall -Wextra -Werror -pedantic -pedantic-errors -O1 -fsanitize=leak
            -fno-omit-frame-pointer
            -fno-sanitize-recover=all)
    set(LINK_OPTS -fsanitize=leak)
endif()
if (TESTS_BUILD_TYPE MATCHES USAN)
    set(COMPILE_OPTS -Wall -Wextra -Werror -pedantic -pedantic-errors -O1
        -fsanitize=undefined,float-cast-overflow,float-divide-by-zero
        -fno-omit-frame-pointer -fno-sanitize-recover=all
        -fsanitize-recover=alignment)
    set(LINK_OPTS
        -fsanitize=undefined,float-cast-overflow,float-divide-by-zero)
endif()

# Configure clang-tidy
if (${USE_CLANG_TIDY})
    set(CMAKE_CXX_CLANG_TIDY clang-tidy)
endif()


find_package(Catch2 REQUIRED)

add_subdirectory(complex)
add_subdirectory(expressions)
add_subdirectory(test)
