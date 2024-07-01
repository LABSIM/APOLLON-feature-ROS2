cmake_minimum_required(VERSION 3.8)
project(lexikhum_oat_gateway)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(lexikhum_oat_gateway_msgs REQUIRED)

# targets 
add_executable(
    lexikhum_oat_downstream_gateway 
    src/LEXIKHUMOATDownstreamGateway.cpp
)
ament_target_dependencies(
    lexikhum_oat_downstream_gateway 
    rclcpp 
    lexikhum_oat_gateway_msgs
)
 
add_executable(
    lexikhum_oat_upstream_gateway 
    src/LEXIKHUMOATUpstreamGateway.cpp
)
ament_target_dependencies(
    lexikhum_oat_upstream_gateway 
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