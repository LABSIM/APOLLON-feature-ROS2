FROM ros:humble-ros-base

# Make ROS2 Workspace Dirss
RUN mkdir -p /home/dev_ws/src

# Copy ROS2 packages into workspace
COPY ./docker/ISIR/embeded_packages /home/dev_ws/src

# Check out ROS-TCP-Endpoint, ROS2 version
RUN git clone https://github.com/Unity-Technologies/ROS-TCP-Endpoint /home/dev_ws/src/ros_tcp_endpoint -b ROS2v0.7.0

# Reference script with commands to source workspace
#COPY ./docker/ISIR/source_ros.sh /home/dev_ws/source_ros.sh

# Change to workspace on sign in
RUN echo "cd home/dev_ws" >> ~/.bashrc

# Build the workspace
RUN cd home/dev_ws && . /opt/ros/humble/setup.sh && colcon build
#RUN cd home/dev_ws && . /opt/ros/humble/setup.sh && VERBOSE=1 colcon build --event-handlers console_direct+ 

# Source the workspace on sign in
# RUN echo ". install/local_setup.bash" >> ~/.bashrc