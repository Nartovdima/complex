add_executable(tests complexTest.cpp expressionsTest.cpp)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain complex-static expressions-static)