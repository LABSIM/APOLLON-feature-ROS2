from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        # Node(
        #     package='lexikhum_oat_gateway',
        #     executable='lexikhum_oat_downstream_gateway',
        #     name='downstream'
        # ),
        Node(
            package='lexikhum_oat_gateway',
            executable='lexikhum_oat_upstream_gateway',
            name='upstream'
        ),
        Node(
            package='ros_tcp_endpoint',
            executable='default_server_endpoint',
            name='endpoint',
            arguments=[
                '-p','ROS_IP:=0.0.0.0',
                '-p','ROS_TCP_PORT:=10000'
            ]
        )
    ])
