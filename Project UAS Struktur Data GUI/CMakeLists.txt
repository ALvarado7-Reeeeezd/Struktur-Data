cmake_minimum_required(VERSION 3.16)

project(RentalPS_GUI VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

# Output executable ke folder build yang rapi.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(RentalPS_GUI
    src/main.cpp
    src/mainwindow.cpp
    src/singlylist.cpp
    src/doublylist.cpp
    src/stackdata.cpp
    src/queuedata.cpp
    src/sorting.cpp
    src/searching.cpp
    src/recursive.cpp
    src/filehandler.cpp
    include/rental.h
    include/mainwindow.h
    include/singlylist.h
    include/doublylist.h
    include/stackdata.h
    include/queuedata.h
    include/sorting.h
    include/searching.h
    include/recursive.h
    include/filehandler.h
)


# Di Windows, jalankan sebagai GUI app tanpa console hitam tambahan.
if(WIN32)
    set_target_properties(RentalPS_GUI PROPERTIES WIN32_EXECUTABLE TRUE)
endif()

target_include_directories(RentalPS_GUI PRIVATE include)
target_link_libraries(RentalPS_GUI PRIVATE Qt6::Widgets)
