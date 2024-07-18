//
// LEXIKHUM-OAT Gateway
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; see the file COPYING.
// If not, see <http://www.gnu.org/licenses/>.
//

// Lexikhum OAT include
#include "lexikhum_oat_gateway/LEXIKHUMOAT_UpstreamGateway.hpp"

// avoid namespace pollution
namespace Labsim::apollon::feature::ROS2 
{    
   
    // Default explicit Ctor implementation
    
    UpstreamGateway::UpstreamGateway()
        : base_type(self_type::_s_gateway_node_name.data())
    {

        //
        // TODO :
        // ADD ISIR TOPIC SUBSCRIBER LAMBDA HERE (?)
        //
        // auto ISIR_subscription_lambda 
        //     = [this](ISIR_topic_type const & _msg) 
        //         -> void
        //     {
        //
        //         auto buffer = this->m_upstream_buffer_ref.load();
        //
        //         buffer.? = _msg.?;
        //         [...]
        //         buffer.? = _msg.?;
        //
        //         this->m_upstream_buffer_ref = buffer;
        //
        //     }; /* ISIR_subscription_lambda */
        //
        auto ISIR_fd_ee_pose_topic_subscription_lambda 
            = [this](ISIR_fd_ee_pose_topic_type const & _msg) 
                -> void
            {
        
                auto buffer = this->m_upstream_buffer_ref.load();
        
                buffer.haptic_arm_world_position = _msg.pose.position;
        
                this->m_upstream_buffer_ref = buffer;
        
            }; /* ISIR_fd_ee_pose_topic_subscription_lambda */

        auto ISIR_ctrl_params_topic_subscription_lambda 
            = [this](ISIR_ctrl_params_topic_type const & _msg) 
                -> void
            {
        
                auto buffer = this->m_upstream_buffer_ref.load();
        
                buffer.gate_gradiant_force.y = _msg.data[0];
                buffer.gate_size_forward.y   = _msg.data[1];
                buffer.gate_size_dodge.y     = _msg.data[2];
        
                this->m_upstream_buffer_ref = buffer;
        
            }; /* ISIR_ctrl_params_topic_subscription_lambda */

        auto tick_lambda 
            = [this]()
                -> void
            {

                // load last value
                auto buffer = this->m_upstream_buffer_ref.load();

                // increment internal uuid
                buffer.uuid = this->m_uuid++;
        
                // eject into Unity
                this->m_publisher->publish(buffer);

                RCLCPP_INFO_STREAM(
                    this->get_logger(), 
                    "I Send: '" 
                        << buffer.uuid 
                        << " / "
                            << buffer.haptic_arm_world_position.x
                            << ","
                            << buffer.haptic_arm_world_position.y
                            << ","
                            << buffer.haptic_arm_world_position.z
                        << " / "
                            << buffer.gate_world_position.x
                            << ","
                            << buffer.gate_world_position.y
                            << ","
                            << buffer.gate_world_position.z
                        << " / "
                            << buffer.gate_size_forward.x
                            << ","
                            << buffer.gate_size_forward.y
                            << ","
                            << buffer.gate_size_forward.z
                        << " / "
                            << buffer.gate_size_dodge.x
                            << ","
                            << buffer.gate_size_dodge.y
                            << ","
                            << buffer.gate_size_dodge.z
                        << " / "
                            << buffer.gate_gradiant_force.x
                            << ","
                            << buffer.gate_gradiant_force.y
                            << ","
                            << buffer.gate_gradiant_force.z
                    << "'"
                );

            }; /* tick_lambda */

        this->m_publisher 
            = this->create_publisher<gateway_topic_type>(
                /* topic_name        */ self_type::_s_gateway_topic_name.data(), 
                /* qos_history_depth */ 10
            );

        //
        // TODO :
        // CREATE ISIR TOPIC SUBSCRIBER CALLBACK HERE (?)
        //            
        // this->m_ISIR_subscriber 
        //     = this->create_subscription<ISIR_topic_type>(
        //         /* topic_name        */ self_type::_s_ISIR_topic_name.data(), 
        //         /* qos_history_depth */ 10, 
        //         /* callback          */ std::move(ISIR_subscription_lambda)  
        //     );
        //
        this->m_ISIR_fd_ee_pose_topic_subscriber 
            = this->create_subscription<ISIR_fd_ee_pose_topic_type>(
                /* topic_name        */ self_type::_s_ISIR_fd_ee_pose_topic_name.data(), 
                /* qos_history_depth */ 10, 
                /* callback          */ std::move(ISIR_fd_ee_pose_topic_subscription_lambda)  
            );
        this->m_ISIR_ctrl_params_topic_subscriber 
            = this->create_subscription<ISIR_ctrl_params_topic_type>(
                /* topic_name        */ self_type::_s_ISIR_ctrl_params_topic_name.data(), 
                /* qos_history_depth */ 10, 
                /* callback          */ std::move(ISIR_ctrl_params_topic_subscription_lambda)  
            );
        
        this->m_timer 
            = this->create_wall_timer(
                self_type::_s_gateway_tick_period, 
                std::move(tick_lambda)
            );

    } /* UpstreamGateway() */

} /* } Labsim::apollon::feature::ROS2 */