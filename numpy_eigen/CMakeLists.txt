cmake_minimum_required(VERSION 2.8.3)
project(numpy_eigen)

find_package(catkin_simple REQUIRED)
catkin_simple()

find_package(Boost REQUIRED COMPONENTS system)

add_definitions(${EIGEN_DEFINITIONS})
include_directories(include ${Eigen_INCLUDE_DIRS})

include_directories("${PROJECT_SOURCE_DIR}/include/numpy_eigen")

add_definitions(-std=c++0x -D__STRICT_ANSI__)

include_directories(include ${Boost_INCLUDE_DIRS})

INCLUDE(src/autogen_files.cmake)
add_python_export_library(${PROJECT_NAME} 
  ${PROJECT_SOURCE_DIR}/python/${PROJECT_NAME} ${AUTOGEN_FILES}
)

target_link_libraries(${PROJECT_NAME} 
                      ${catkin_LIBRARIES} ${Boost_LIBRARIES})


#TODO remove this condition again as soon as issue #137 is fixed
IF(NOT APPLE)

INCLUDE(src/autogen_test_files.cmake)
add_python_export_library(${PROJECT_NAME}_test 
      ${PROJECT_SOURCE_DIR}/python/${PROJECT_NAME} ${AUTOGEN_TEST_FILES}
  )


## Add nosetest based cpp test target.
catkin_add_nosetests(test/numpy_eigen_tests.py)

ENDIF()

cs_install()
cs_export()
