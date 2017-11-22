#add_executable(ngraph ngraph.cpp main.cpp)
#add_library(ngl canvas.cpp handler.cpp entity.cpp)

#target_link_libraries(ngl curses)
#target_link_libraries(ngraph ngl)
#target_link_libraries(ngraph curses)
add_executable(ngraph main.cpp)
find_library(lib_path curses)
target_link_libraries(ngraph "${lib_path}")
