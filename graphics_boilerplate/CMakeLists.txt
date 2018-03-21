project(graphics_asgn1)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(src SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST} src/grass.cpp src/grass.h src/pool.cpp src/pool.h src/trampoline.cpp src/trampoline.h src/stand.cpp src/stand.h src/spike.cpp src/spike.h src/magnet.cpp src/magnet.h src/magnetstand.cpp src/magnetstand.h src/slab.cpp src/slab.h src/slab1.cpp src/slab1.h)

include(FindPkgConfig)

pkg_check_modules(GLFW3 REQUIRED glfw3)
include_directories(${GLFW3_INCLUDE_DIRS})
target_link_libraries (${PROJECT_NAME} ${GLFW3_LIBRARIES})

pkg_check_modules(GLEW REQUIRED glew)
include_directories(${GLEW_INCLUDE_DIRS})
target_link_libraries (${PROJECT_NAME} ${GLEW_LIBRARIES})

pkg_check_modules(GL REQUIRED gl)
include_directories(${GL_INCLUDE_DIRS})
target_link_libraries (${PROJECT_NAME} ${GL_LIBRARIES})

# pkg_check_modules(AO REQUIRED ao)
# include_directories(${AO_INCLUDE_DIRS})
# target_link_libraries (${PROJECT_NAME} ${AO_LIBRARIES})

# pkg_check_modules(LIBMPG123 REQUIRED libmpg123)
# include_directories(${LIBMPG123_INCLUDE_DIRS})
# target_link_libraries (${PROJECT_NAME} ${LIBMPG123_LIBRARIES})

configure_file(src/Sample_GL.vert Sample_GL.vert COPYONLY)
configure_file(src/Sample_GL.frag Sample_GL.frag COPYONLY)
# configure_file(assets/song.mp3 assets/song.mp3 COPYONLY)
