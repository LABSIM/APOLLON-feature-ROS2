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
# haptic_arm_world_position : position of the haptic arm in SI unit (meter)
#
geometry_msgs/Vector3 haptic_arm_world_position
#
# gate_world_position : position of the current haptic center of the gate in SI unit (meter)
#
geometry_msgs/Vector3 gate_world_position
#
# gate_size_forward : forward size zone of the current haptic gate in SI unit (meter)
#
geometry_msgs/Vector3 gate_size_forward
#
# gate_size_dodge : dodge size zone of the current haptic gate in SI unit (meter)
#
geometry_msgs/Vector3 gate_size_dodge
#
# gate_gradiant_force : gradiant of force applied by the haptic arm (N) ?
#
geometry_msgs/Vector3 gate_gradiant_force