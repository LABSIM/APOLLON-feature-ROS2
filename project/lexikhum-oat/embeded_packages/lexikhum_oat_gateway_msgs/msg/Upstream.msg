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
# effector_world_position : real position of the effector, aka. the haptic arm, in SI unit (meter)
#
geometry_msgs/Point effector_world_position
#
# force_feedback_objective_world_position : position of the computed current force feedback objective in SI unit (meter)
#
geometry_msgs/Point force_feedback_objective_world_position
#
# force_feedback_gradiant_force : gradiant of force applied by the force feedback arm (N) ?
#
geometry_msgs/Point force_feedback_gradiant_force