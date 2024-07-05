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

        auto subscription_lambda 
            = [this](gateway_topic_type const & _msg) 
                -> void
            {

                // inject from Unity
                this->m_downstream_buffer_ref = _msg;

                // keep track of current uuid 
                this->m_uuid = _msg.uuid;

                // RCLCPP_INFO_STREAM(
                //     this->get_logger(), 
                //     "I Receive: '" 
                //         << _msg.uuid 
                //         << "'"
                // );

            }; /* subscription_lambda */

        auto tick_lambda 
            = [this]()
                -> void
            {
        
                // load last value 
                auto buffer = this->m_downstream_buffer_ref.load();

                //
                // TODO :
                // ADD ISIR TOPIC PUBLISHING HERE (?)
                //
                // auto topic = ISIR_topic_type();
                // topic.? = buffer.?;
                // this->m_topic_publisher.publish(topic);
                //

            }; /* tick_lambda */

        //
        // TODO :
        // CREATE ISIR TOPIC PUBLISHER HERE (?)
        //
        // this->m_topic_publisher 
        //     = this->create_publisher<ISIR_topic_type>(
        //         /* topic_name        */ LEXIKHUMOATUpstreamGateway::_s_ISIR_topic_name.data(), 
        //         /* qos_history_depth */ 10
        //     );
        //

        this->m_subscriber 
            = this->create_subscription<gateway_topic_type>(
                /* topic_name        */ self_type::_s_gateway_topic_name.data(), 
                /* qos_history_depth */ 10, 
                /* callback          */ std::move(subscription_lambda)  
            );
    
        this->m_timer 
            = this->create_wall_timer(
                self_type::_s_gateway_tick_period, 
                std::move(tick_lambda)
            );

    } /* DownstreamGateway() */

} /* } Labsim::apollon::feature::ROS2 */