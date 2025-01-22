cmake_minimum_required(VERSION 3.14)
project(PCO_LAB07 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(TEST_FILES
    main.cpp
)

set(TEST_HEADERS
    modeltemplate.h
    modelnumbers.h
    modelbarrier.h
    pcobarrier.h
)

add_executable(PCO_LAB07 ${TEST_FILES} ${TEST_HEADERS})

target_link_libraries(PCO_LAB07 PRIVATE -lpcosynchro modelchecking_lib)
