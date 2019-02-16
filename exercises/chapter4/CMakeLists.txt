enable_testing()

find_package(Threads REQUIRED)

include_directories(${CHECK_INCLUDE_DIRS})

add_executable(tee tee.c)
target_link_libraries(tee LINK_PUBLIC tlpi)
link_libraries(${CHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
