add_executable(
    ${PROJECT_NAME}
    draughts.cpp
    draughts.h
    mainwindow.cpp
    mainwindow.h     
    )

target_link_libraries(
    ${PROJECT_NAME}
   ${wxWidgets_LIBRARIES}
    )

install(TARGETS wxdraughts DESTINATION ${CMAKE_INSTALL_PREFIX})




