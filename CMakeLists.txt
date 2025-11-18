cmake_minimum_required(VERSION 3.13)
project(FiguresProject VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

add_library(utils
    src/Utils/Exceptions.cpp
    src/Utils/Predicates.cpp
    src/Utils/Readers.cpp
    src/Utils/CinRedirect.cpp
)
target_include_directories(utils PUBLIC src/Utils)

add_library(factories
    src/Factories/StringToFigure.cpp
    src/Factories/StreamFigureFactory.cpp
    src/Factories/RandomFigureFactory.cpp
    src/Factories/AbstractFactory.cpp
)
target_include_directories(factories PUBLIC src/Factories)
target_link_libraries(factories PUBLIC utils)

add_library(figures
    src/Figures/Circle.cpp
    src/Figures/Rectangle.cpp
    src/Figures/Triangle.cpp
)
target_include_directories(figures PUBLIC src/Figures)
target_link_libraries(figures PUBLIC factories)

add_library(userapi
    src/UserAPI/Manager.cpp
)
target_include_directories(userapi PUBLIC src/UserAPI)
target_link_libraries(userapi PUBLIC figures)

add_executable(application src/main.cpp)
target_link_libraries(application PRIVATE userapi)

enable_testing()
add_subdirectory(lib/Catch2)

add_executable(tests 
test/utils-tests.cpp
test/figure-tests.cpp
test/factory-tests.cpp
test/manager-tests.cpp
)
target_link_libraries(tests PRIVATE userapi Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(tests)
