cmake_minimum_required(VERSION 3.29.6)
project(Project_Work_TPSIT)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_DIR src)
set(INCLUDE_DIR include)

include_directories(${INCLUDE_DIR})

add_library(Serra STATIC ${SOURCE_DIR}/Serra.cpp)
add_library(Impianto STATIC ${SOURCE_DIR}/Impianto.cpp)
add_library(Time STATIC ${SOURCE_DIR}/Time.cpp)
add_library(Manuale STATIC ${SOURCE_DIR}/Manuale.cpp)
add_library(Automatico STATIC ${SOURCE_DIR}/Automatico.cpp)
add_library(Adattivo STATIC ${SOURCE_DIR}/Adattivo.cpp)
add_library(UserInterface STATIC ${SOURCE_DIR}/UserInterface.cpp)

add_executable(Project_Work_TPSIT ${SOURCE_DIR}/main.cpp)

target_link_libraries(Project_Work_TPSIT Serra Impianto Time)