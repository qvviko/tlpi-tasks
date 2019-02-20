enable_testing()

find_package(Threads REQUIRED)

include_directories(${CHECK_INCLUDE_DIRS})

add_executable(large_file large_file.c)
target_link_libraries(large_file LINK_PUBLIC tlpi)

add_executable(appending appending.c)
target_link_libraries(appending LINK_PUBLIC tlpi)

add_executable(atomic_append atomic_append.c)
target_link_libraries(atomic_append LINK_PUBLIC tlpi)

add_executable(my_dupes my_dupes.c my_dupes.h)
target_link_libraries(my_dupes LINK_PUBLIC tlpi)

add_executable(writes writes.c)
target_link_libraries(writes LINK_PUBLIC tlpi)

link_libraries(${CHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
