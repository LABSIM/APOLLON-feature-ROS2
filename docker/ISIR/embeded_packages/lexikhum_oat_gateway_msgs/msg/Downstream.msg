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
# param_gate_size_forward : parameterized forward size zone of the haptic gate in SI unit (meter)
#
geometry_msgs/Point param_gate_size_forward
#
# param_gate_size_dodge : parameterized dodge size zone of the haptic gate in SI unit (meter)
#
geometry_msgs/Point param_gate_size_dodge
#
# param_gate_gradiant_force : parameterized gradiant of force applied by the haptic arm (N) ?
#
geometry_msgs/Point param_gate_gradiant_force
