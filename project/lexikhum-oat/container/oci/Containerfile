#
# LEXIKHUM-OAT Gateway
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; see the file COPYING.
# If not, see <http://www.gnu.org/licenses/>.
#

FROM docker.io/ros:humble-ros-base

# Make ROS2 Workspace Dirss
RUN mkdir -p /home/dev_ws/src

# Copy ROS2 packages into workspace
COPY ./embeded_packages /home/dev_ws/src

# Check out ROS-TCP-Endpoint, ROS2 version
RUN git clone https://github.com/Unity-Technologies/ROS-TCP-Endpoint /home/dev_ws/src/ros_tcp_endpoint -b ROS2v0.7.0

# Reference script with commands to source workspace
COPY ./container/source_ros.sh /home/dev_ws/source_ros.sh

# Change to workspace on sign in
RUN echo "cd home/dev_ws" >> ~/.bashrc

# Build the workspace
#RUN cd home/dev_ws && . /opt/ros/humble/setup.sh && colcon build
RUN cd home/dev_ws && . /opt/ros/humble/setup.sh && VERBOSE=1 colcon build --event-handlers console_direct+ 

# Source the workspace on sign in
RUN echo ". install/local_setup.bash" >> ~/.bashrc