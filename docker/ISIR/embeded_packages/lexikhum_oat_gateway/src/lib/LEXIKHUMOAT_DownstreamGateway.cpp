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
#include "lexikhum_oat_gateway/LEXIKHUMOAT_DownstreamGateway.hpp"

// avoid namespace pollution
namespace Labsim::apollon::feature::ROS2
{
    
    // Default explicit Ctor implementation
    
    DownstreamGateway::DownstreamGateway()
        : base_type(self_type::_s_gateway_node_name.data())
    {

        constexpr std::uint32_t _queue_sz{10};
        rclcpp::QoS current_qos = rclcpp::QoS(_queue_sz);
        
        auto subscription_lambda 
            = [this](gateway_topic_type const & _msg) 
                -> void
            {

                // lock data
                std::lock_guard<std::mutex> lock{this->m_mutex};

                // inject from Unity
                this->m_data = _msg;

                // keep track of current uuid 
                this->m_uuid = _msg.uuid;

            }; /* subscription_lambda */

        auto tick_lambda 
            = [this]()
                -> void
            {
        
                // // load last value
                // auto buffer = this->m_downstream_buffer_ref.load();

                // lock data
                std::lock_guard<std::mutex> lock{this->m_mutex};

                //
                // TODO :
                // ADD ISIR TOPIC PUBLISHING HERE (?)
                //
                // auto topic = ISIR_topic_type();
                // topic.? = buffer.?;
                // this->m_topic_publisher->publish(topic);
                //
                auto ISIR_sim_target_topic = ISIR_sim_target_topic_type();

                /*
                ISIR_sim_target_topic.pose.position      = buffer.entity_world_pose.position;
                ISIR_sim_target_topic.pose               = buffer.current_gate_center;
                ISIR_sim_target_topic.current_gate_width = buffer.current_gate_width;
                ISIR_sim_target_topic.current_phase      = buffer.current_phase;

                */

                this->m_ISIR_sim_target_topic_publisher->publish(ISIR_sim_target_topic);

            }; /* tick_lambda */

        //
        // TODO :
        // CREATE ISIR TOPIC PUBLISHER HERE (?)
        //
        // this->m_topic_publisher   
        //     = this->create_publisher<ISIR_topic_type>(
        //         /* topic_name */ self_type::_s_ISIR_topic_name.data(), 
        //         /* QoS        */ current_qos
        //     );
        //
        this->m_ISIR_sim_target_topic_publisher 
            = this->create_publisher<ISIR_sim_target_topic_type>(
                /* topic_name */ self_type::_s_ISIR_sim_target_topic_name.data(), 
                /* QoS        */ current_qos
            );

        this->m_subscriber 
            = this->create_subscription<gateway_topic_type>(
                /* topic_name */ self_type::_s_gateway_topic_name.data(), 
                /* QoS        */ current_qos, 
                /* callback   */ std::move(subscription_lambda)  
            );
    
        this->m_timer 
            = this->create_wall_timer(
                self_type::_s_gateway_tick_period, 
                std::move(tick_lambda)
            );

    } /* DownstreamGateway() */

} /* } Labsim::apollon::feature::ROS2 */