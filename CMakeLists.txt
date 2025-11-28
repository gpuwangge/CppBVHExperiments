cmake_minimum_required(VERSION 3.20)
SET(CMAKE_C_COMPILER "C:/mingw64/bin/gcc.exe")
SET(CMAKE_CXX_COMPILER "C:/mingw64/bin/g++.exe")
project(bvh_Project)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE "Debug")

#Set SRC, build and bin folders
aux_source_directory(${PROJECT_SOURCE_DIR}/source SRC)
# set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)
# set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/bin)

#Set variables so all cmakelists.txt in sub dirs can access
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib) #CMAKE_BINARY_DIR is build/, all lib goes here
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib) #this is not required in windows
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) #this is required in Windows, all dll/exe goes here




#add all files from SRC folder
add_executable(${PROJECT_NAME} ${SRC}) 

target_include_directories(${PROJECT_NAME} PRIVATE
    include
    $ENV{INCLUDE} #for glm
    #${CMAKE_SOURCE_DIR}/external #for yaml headers
)

#foreach(cppfile IN LISTS SRC)  
#    get_filename_component(filename ${cppfile} NAME_WE)  
#    add_executable(${filename} ${cppfile})  
#endforeach()  

