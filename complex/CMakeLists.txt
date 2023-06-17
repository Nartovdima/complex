add_library(complex-static STATIC
	"include/complex/complex.hpp"
	complex.cpp
)

target_include_directories(complex-static
    PUBLIC
        "include"
)