add_executable(events_test events_test.cpp)
add_executable(entity_test entity_test.cpp)
add_executable(interwindow_test interwindow_test.cpp)
add_executable(gui_test1 gui_test1.cpp)
add_executable(gui_test2 gui_test2.cpp)
add_executable(gui_test3 gui_test3.cpp)
add_executable(gui_test4 gui_test4.cpp)
add_executable(tetris_test tetris.cpp)
target_link_libraries(events_test curses)
target_link_libraries(entity_test curses)
target_link_libraries(interwindow_test curses)  #todo, add to lib separately and link against lib
target_link_libraries(gui_test1 curses)
target_link_libraries(gui_test2 curses)
target_link_libraries(gui_test3 curses)
target_link_libraries(gui_test4 curses)
target_link_libraries(tetris_test curses)
#add_executable(drawing_test events_test.cpp)
#add_executable(windows_test events_test.cpp)
