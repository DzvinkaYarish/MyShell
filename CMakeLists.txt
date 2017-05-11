cmake_minimum_required(VERSION 3.3)
project(MyShell)

set(CMAKE_CXX_STANDARD 11)
find_package(Boost COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

set(SOURCE_FILES main.cpp callOuterCommands.cpp callOuterCommands.h innerCommands.cpp innerCommands.h sh_tools.h sh_tools.cpp)
set(SOURCE_FILES_COPY cp.cpp)
set(SOURCE_FILES_MKDIR mkdir.cpp)
set(SOURCE_FILES_RM rm.cpp)
set(SOURCE_FILES_MV mv.cpp)
set(SOURCE_FILES_LS ls.cpp sh_tools.h sh_tools.cpp)


add_executable(myShell ${SOURCE_FILES} )
add_executable(cp ${SOURCE_FILES_COPY})
add_executable(mkdir ${SOURCE_FILES_MKDIR})
add_executable(rm ${SOURCE_FILES_RM})
add_executable(mv ${SOURCE_FILES_MV})
add_executable(ls ${SOURCE_FILES_LS})



target_link_libraries(myShell ${Boost_LIBRARIES} )
target_link_libraries(cp ${Boost_LIBRARIES} )
target_link_libraries(rm ${Boost_LIBRARIES} )
target_link_libraries(mv ${Boost_LIBRARIES} )
target_link_libraries(ls ${Boost_LIBRARIES} )
