
project(llp_lab_6_ C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wall -Werror")


add_executable(llp_lab_6_ src/main.c src/lib/bmp.h src/lib/bmp_transform.c src/lib/bmp_transform.h src/lib/bmp_io.c src/lib/bmp_io.h src/lib/bmp_struct.h)
target_link_libraries(llp_lab_6_ m)
