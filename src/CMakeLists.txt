project(wxdraughts)
cmake_minimum_required( VERSION 3.1 )

# C++ standard requirements.
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(wxWidgets COMPONENTS core base REQUIRED)

include( "${wxWidgets_USE_FILE}" )


add_executable(
    ${PROJECT_NAME}
    draughts.cpp
    draughts.h
    mainwindow.cpp
    mainwindow.h
    movepiece.cpp
    movepiece.h
    )

target_link_libraries(
    ${PROJECT_NAME}
    ${wxWidgets_LIBRARIES}
    )

install(TARGETS wxdraughts DESTINATION ${CMAKE_INSTALL_PREFIX})




