cmake_minimum_required(VERSION 3.8)
project(lexikhum_oat_gateway)

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
find_package(rclcpp REQUIRED)
find_package(lexikhum_oat_gateway_msgs REQUIRED)

# target => lexikhum_oat_downstream_gateway
add_executable(
    lexikhum_oat_downstream_gateway 
    src/LEXIKHUMOAT_DownstreamGateway.cpp
)
target_include_directories(
    lexikhum_oat_downstream_gateway
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)
target_link_libraries(
    lexikhum_oat_downstream_gateway
    PRIVATE
        atomic
)
ament_target_dependencies(
    lexikhum_oat_downstream_gateway 
    PUBLIC
        rclcpp
        lexikhum_oat_gateway_msgs
)
 
# target => lexikhum_oat_upstream_gateway
add_executable(
    lexikhum_oat_upstream_gateway 
    src/LEXIKHUMOAT_UpstreamGateway.cpp
)
target_include_directories(
    lexikhum_oat_upstream_gateway
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)
target_link_libraries(
    lexikhum_oat_upstream_gateway
    PRIVATE
        atomic
)
ament_target_dependencies(
    lexikhum_oat_upstream_gateway
    PUBLIC
        rclcpp
        lexikhum_oat_gateway_msgs
)

# install
install(
    TARGETS
        lexikhum_oat_downstream_gateway
        lexikhum_oat_upstream_gateway
    DESTINATION 
        lib/${PROJECT_NAME}
)
install(
    DIRECTORY
        launch
    DESTINATION 
        share/${PROJECT_NAME}
)
# install(
#     DIRECTORY
#         config
#     DESTINATION 
#         share/${PROJECT_NAME}
# )

if(BUILD_TESTING)
    find_package(ament_lint_auto REQUIRED)
    # the following line skips the linter which checks for copyrights
    # comment the line when a copyright and license is added to all source files
    set(ament_cmake_copyright_FOUND TRUE)
    # the following line skips cpplint (only works in a git repo)
    # comment the line when this package is in a git repo and when
    # a copyright and license is added to all source files
    set(ament_cmake_cpplint_FOUND TRUE)
    ament_lint_auto_find_test_dependencies()
endif()

ament_package()