project(wxdraughts)
cmake_minimum_required( VERSION 3.1 )

# C++ standard requirements.
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(wxWidgets COMPONENTS core base REQUIRED)

include( "${wxWidgets_USE_FILE}" )

add_subdirectory(src)



