cmake_minimum_required(VERSION 3.6)
project(MyShell)

set(CMAKE_CXX_STANDARD 11)
set(Boost_INCLUDE_DIR /usr/local/include)
set(Boost_LIBRARY_DIR /usr/local/include/boost)
find_package(Boost COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

set(SOURCE_FILES main.cpp callOuterCommands.cpp callOuterCommands.h innerCommands.cpp innerCommands.h)
set(SOURCE_FILES_COPY cp.cpp)
set(SOURCE_FILES_MKDIR mkdir.cpp)
set(SOURCE_FILES_RM rm.cpp)
set(SOURCE_FILES_MV mv.cpp)
set(SOURCE_FILES_LS ls.cpp)
set(SOURCE_FILES_TEST testsomefunc.cpp)


add_executable(myShell ${SOURCE_FILES} )
add_executable(cp ${SOURCE_FILES_COPY})
add_executable(mkdir ${SOURCE_FILES_MKDIR})
add_executable(rm ${SOURCE_FILES_RM})
add_executable(mv ${SOURCE_FILES_MV})
add_executable(ls ${SOURCE_FILES_LS})
add_executable(testsomefunc ${SOURCE_FILES_TEST})



target_link_libraries(myShell ${Boost_LIBRARIES} )
target_link_libraries(cp ${Boost_LIBRARIES} )
target_link_libraries(rm ${Boost_LIBRARIES} )
target_link_libraries(mv ${Boost_LIBRARIES} )
target_link_libraries(ls ${Boost_LIBRARIES} )
target_link_libraries(testsomefunc ${Boost_LIBRARIES} )

