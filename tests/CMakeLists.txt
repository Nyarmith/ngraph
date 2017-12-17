add_executable(events_test events_test.cpp)
add_executable(entity_test entity_test.cpp)
add_executable(interwindow_test interwindow_test.cpp)
target_link_libraries(events_test curses)
target_link_libraries(entity_test curses)
target_link_libraries(interwindow_test curses)  #todo, add to lib separately and link against lib
#add_executable(drawing_test events_test.cpp)
#add_executable(windows_test events_test.cpp)
