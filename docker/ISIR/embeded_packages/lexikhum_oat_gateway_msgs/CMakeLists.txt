cmake_minimum_required(VERSION 3.8)
project(lexikhum_oat_gateway_msgs)

#
# Default build :
# - Release build type
# - strict C99
# - strict C++20
#

set(CMAKE_BUILD_TYPE "Release")

if(NOT CMAKE_C_STANDARD)

    set(CMAKE_C_STANDARD 99)
    set(CMAKE_C_STANDARD_REQUIRED ON)
    set(CMAKE_C_EXTENSIONS OFF)

endif()

if(NOT CMAKE_CXX_STANDARD)

    set(CMAKE_CXX_STANDARD 20)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)

endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")

    add_compile_options(-Wall -Wextra -Wpedantic)

endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)

rosidl_generate_interfaces(
    ${PROJECT_NAME}
        "msg/Downstream.msg"
        "msg/Upstream.msg"
    DEPENDENCIES 
        std_msgs 
        geometry_msgs
        sensor_msgs
)

if(BUILD_TESTING)

	find_package(ament_lint_auto REQUIRED)

	# the following line skips the linter which checks for copyrights
	# uncomment the line when a copyright and license is not present in all source files
	set(ament_cmake_copyright_FOUND TRUE)

	# the following line skips cpplint (only works in a git repo)
	# uncomment the line when this package is not in a git repo
	#set(ament_cmake_cpplint_FOUND TRUE)
	ament_lint_auto_find_test_dependencies()
    
endif()

ament_export_dependencies(
    rosidl_default_runtime 
    std_msgs 
    geometry_msgs
    sensor_msgs
)

ament_export_include_directories(
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

ament_package()