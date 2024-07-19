add_executable(part-i part-i.cpp
        part-iv.cpp
        part-v.cpp)
target_link_libraries(part-i PUBLIC CGAL::CGAL)

add_executable(part-ii part-ii.cpp)
target_link_libraries(part-ii PUBLIC CGAL::CGAL)

add_executable(part-iii part-iii.cpp)
target_link_libraries(part-iii PUBLIC CGAL::CGAL)

add_executable(part-iv part-iv.cpp)
target_link_libraries(part-iv PUBLIC CGAL::CGAL)

add_executable(part-v part-v.cpp)
target_link_libraries(part-v PUBLIC CGAL::CGAL)
