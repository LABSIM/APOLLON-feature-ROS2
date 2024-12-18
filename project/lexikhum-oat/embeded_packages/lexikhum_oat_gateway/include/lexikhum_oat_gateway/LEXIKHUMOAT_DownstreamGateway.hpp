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

// guard
#ifndef LEXIKHUM_OAT_GATEWAY_LEXIKHUMOAT_DOWNSTREAMGATEWAY_HPP_
#define LEXIKHUM_OAT_GATEWAY_LEXIKHUMOAT_DOWNSTREAMGATEWAY_HPP_

// Lexikhum OAT include
#include "lexikhum_oat_gateway/LEXIKHUMOAT_NonCopyable.hpp"

// Lexikhum OAT msg include
#include "lexikhum_oat_gateway_msgs/msg/downstream.hpp"

//
// TODO :
// ADD ISIR MESSAGE INCLUDE DIRECTIVE HERE (?)
//

// std include
#include <cstdlib>
#include <chrono>
#include <memory>
#include <mutex>
// #include <atomic>
#include <string_view>

// ROS2 include
#include "rclcpp/rclcpp.hpp"

//
// TODO :
// ADD OTHER MESSAGE INCLUDE DIRECTIVE HERE (?)
//
// ==> [std_msgs/sensor_msgs/geometry_msgs] 
//     dependencies already added to CMakeLists.txt 
//     & package.xml via lexikhum_oat_gateway_msgs project
//
// #include "std_msgs/msg/bool.hpp"
// #include "std_msgs/msg/float64_multi_array.hpp"
// #include "sensor_msgs/msg/joint_state.hpp"
// #include "geometry_msgs/msg/vector3.hpp"
// #include "geometry_msgs/msg/wrench.hpp"
// #include "geometry_msgs/msg/twist.hpp"
//
#include "geometry_msgs/msg/point.hpp"
#include "geometry_msgs/msg/pose.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"

// avoid namespace pollution
namespace Labsim::apollon::feature::ROS2
{

    using namespace std::literals;
    using namespace std::chrono_literals;

    class DownstreamGateway 
        : public NonCopyable
        , public rclcpp::Node
    {

    public:

        // aliases

        using self_type = DownstreamGateway;
        using base_type = rclcpp::Node;
        
        //
        // TODO :
        // CREATE ISIR TOPIC TYPE ALIAS HERE (?)
        //
        //  using ISIR_topic_type = msg::ISIRTopicT;
        //
        using ISIR_sim_target_topic_type = geometry_msgs::msg::PoseStamped;

        using gateway_topic_type         = lexikhum_oat_gateway_msgs::msg::Downstream; 

        // constants 

        //
        // TODO :
        // CREATE ISIR TOPIC NAME HERE (?)
        //
        // static constexpr auto _s_ISIR_topic_name  = "??"sv;
        //
        static constexpr auto _s_ISIR_sim_target_topic_name = "/sim/target_position"sv;
        
        static constexpr auto _s_gateway_topic_name         = "/gateway/ONERA_to_ISIR_Downstream"sv;
        static constexpr auto _s_gateway_node_name          = "lexikhum_oat_downstream_gateway"sv;

        static constexpr auto _s_gateway_tick_period        = 10ms;

        // Coplien form - rule of 5

        DownstreamGateway();

        DownstreamGateway(self_type const & _rhs)
            = delete;

        DownstreamGateway(self_type && _rhs)
            = delete;

        ~DownstreamGateway() override
            = default;

        auto
        operator=(self_type const & _rhs)
            -> self_type & = delete;
        
        auto
        operator=(self_type && _rhs)
            -> self_type & = delete;

    private:

        // members 

        rclcpp::TimerBase::SharedPtr 
            m_timer{ };

        //
        // TODO :
        // ADD ISIR TOPIC PUBLISHER MEMBER HERE (?)
        //
        // rclcpp::Publisher<ISIR_topic_type>::SharedPtr 
        //     m_topic_publisher{ };
        //
        rclcpp::Publisher<ISIR_sim_target_topic_type>::SharedPtr 
            m_ISIR_sim_target_topic_publisher{ };

        rclcpp::Subscription<gateway_topic_type>::SharedPtr 
            m_subscriber{ };

        // alignas(std::atomic_ref<gateway_topic_type>::required_alignment) 
        // gateway_topic_type 
        //     m_downstream_buffer{ };

        // std::atomic_ref<gateway_topic_type>
        //     m_downstream_buffer_ref{ this->m_downstream_buffer };

        gateway_topic_type m_data{ };

        mutable std::mutex m_mutex{ };

        size_t 
            m_uuid{ 0 };


    }; /* class DownstreamGateway */

} /* } Labsim::apollon::feature::ROS2 */

#endif /* LEXIKHUM_OAT_GATEWAY_LEXIKHUMOAT_DOWNSTREAMGATEWAY_HPP_ */