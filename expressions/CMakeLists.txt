add_library(expressions-static STATIC
	"include/expressions/expressions.hpp"
	expressions.cpp
)

target_link_libraries(expressions-static PRIVATE complex-static)

target_include_directories(expressions-static
    PUBLIC
        "include"
)

target_link_libraries(complex-static)