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
#
# uuid : unique message identifier (internal)
#
uint64 uuid
#
# ============================
#     Datagram to discuss
# ============================
#
# entity_world_pose : position & orientation of the piloted entity in SI unit (meter, radian)
#
geometry_msgs/Pose entity_world_pose
#
# current_gate_center : current target gate center in SI unit (meter) 
#
geometry_msgs/Point current_gate_center
#
# current_gate_width : current target gate width in SI unit (meter) 
#
uint64 current_gate_width
#
# current_mode : current experimental shared intention mode
# [
#     Undefined,  <- default
#     Haptic,  
#     Auditive, 
#     Visual, 
#     Practice
# ] 
#
string current_mode
#
# current_phase : current experimental phase (string)
# (
#     Undefined_Undefined, <- default
#     Initialize_Session, 
#     Initialize_Trial,  
#     End_Trial, 
#     End_Session, 
#     Cue_Left,
#     Cue_Right,
#     StrongCue_Left,
#     StrongCue_Right,
#     Success_Center,
#     Arrival_Center
# ) 
#
string current_phase