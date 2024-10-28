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

#include "lexikhum_oat_gateway/LEXIKHUMOAT_UpstreamGateway.hpp"

#include <functional>

// avoid namespace pollution
namespace Labsim::apollon::feature::ROS2 
{    
   
    // Default explicit Ctor implementation
    
    UpstreamGateway::UpstreamGateway()
        : base_type(self_type::_s_gateway_node_name.data())
    {

        constexpr std::uint32_t _queue_sz{10}; // check ISIR si bug Sync ??
        rclcpp::QoS current_qos = rclcpp::QoS(_queue_sz);

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
        
                // lock data
                std::lock_guard<std::mutex> lock{this->m_mutex};
            
                // ok ?
                this->m_data.effector_world_position 
                    = _msg.pose.position;

                // dbg
                // RCLCPP_INFO(
                //     this->get_logger(), 
                //     "Upstream (ISIR_fd_ee_pose_topic_subscription_lambda)=> m_data.effector_world_position[%f,%f,%f]"
                //     , this->m_data.effector_world_position.x
                //     , this->m_data.effector_world_position.y
                //     , this->m_data.effector_world_position.z
                // );
        
            }; /* ISIR_fd_ee_pose_topic_subscription_lambda */

        auto ISIR_ctrl_params_topic_subscription_lambda 
            = [this](ISIR_ctrl_params_topic_type const & _msg) 
                -> void
            {
        
                // lock data
                std::lock_guard<std::mutex> lock{this->m_mutex};
        
                this->m_data.force_feedback_gradiant_force.x = 0.0f;
                this->m_data.force_feedback_gradiant_force.y = _msg.data[0];
                this->m_data.force_feedback_gradiant_force.z = 0.0f;
        
                // dbg
                // RCLCPP_INFO(
                //     this->get_logger(), 
                //     "Upstream (ISIR_ctrl_params_topic_subscription_lambda)=> m_data.force_feedback_gradiant_force[%f,%f,%f]"
                //     , this->m_data.force_feedback_gradiant_force.x
                //     , this->m_data.force_feedback_gradiant_force.y
                //     , this->m_data.force_feedback_gradiant_force.z
                // );

            }; /* ISIR_ctrl_params_topic_subscription_lambda */

        auto sync_lambda 
            = [this](
                ISIR_fd_ee_pose_topic_type::ConstSharedPtr const &  _fd_ee_pose_msg, 
                ISIR_ctrl_params_topic_type::ConstSharedPtr const & _ctrl_params_msg
            ) -> void
            {
                
                // lock data
                std::lock_guard<std::mutex> lock{this->m_mutex};
            
                // ok ?
                this->m_data.effector_world_position 
                    = _fd_ee_pose_msg->pose.position;
                // this->m_data.force_feedback_objective_world_position     
                //     = ??
                this->m_data.force_feedback_gradiant_force.y 
                    = _ctrl_params_msg->data[0];
                
                // dbg
                RCLCPP_INFO(
                    this->get_logger(), 
                    "Upstream (sync)=> m_data.effector_world_position[%f,%f,%f], m_data.force_feedback_objective_world_position[%f,%f,%f], m_data.force_feedback_gradiant_force[%f,%f,%f]"
                    , this->m_data.effector_world_position.x
                    , this->m_data.effector_world_position.y
                    , this->m_data.effector_world_position.z
                    , this->m_data.force_feedback_objective_world_position.x
                    , this->m_data.force_feedback_objective_world_position.y
                    , this->m_data.force_feedback_objective_world_position.z
                    , this->m_data.force_feedback_gradiant_force.x
                    , this->m_data.force_feedback_gradiant_force.y
                    , this->m_data.force_feedback_gradiant_force.z
                );

            }; /* sync_lambda */

        auto tick_lambda 
            = [this]()
                -> void
            {

                // lock data
                std::lock_guard<std::mutex> lock{this->m_mutex};

                // increment internal uuid
                this->m_data.uuid = this->m_uuid++;
        
                // eject into Unity
                this->m_publisher->publish(this->m_data);

                // dbg
                RCLCPP_INFO(
                    this->get_logger(), 
                    "Upstream (tick)=> m_data.uuid[%lu], m_data.effector_world_position[%f,%f,%f], m_data.force_feedback_objective_world_position[%f,%f,%f], m_data.force_feedback_gradiant_force[%f,%f,%f]"
                    , this->m_data.uuid
                    , this->m_data.effector_world_position.x
                    , this->m_data.effector_world_position.y
                    , this->m_data.effector_world_position.z
                    , this->m_data.force_feedback_objective_world_position.x
                    , this->m_data.force_feedback_objective_world_position.y
                    , this->m_data.force_feedback_objective_world_position.z
                    , this->m_data.force_feedback_gradiant_force.x
                    , this->m_data.force_feedback_gradiant_force.y
                    , this->m_data.force_feedback_gradiant_force.z
                );

            }; /* tick_lambda */

        this->m_publisher 
            = this->create_publisher<gateway_topic_type>(
                /* topic_name */ self_type::_s_gateway_topic_name.data(), 
                /* QoS        */ current_qos
            );

        //
        // TODO :
        // CREATE ISIR TOPIC SUBSCRIBER CALLBACK HERE (?)
        //            
        // this->m_ISIR_subscriber 
        //     = this->create_subscription<ISIR_topic_type>(
        //         /* topic_name */ self_type::_s_ISIR_topic_name.data(), 
        //         /* qos        */ current_qos, 
        //         /* callback   */ std::move(ISIR_subscription_lambda)  
        //     );
        this->m_ISIR_fd_ee_pose_topic_subscriber 
            = this->create_subscription<ISIR_fd_ee_pose_topic_type>(
                /* topic_name */ self_type::_s_ISIR_fd_ee_pose_topic_name.data(), 
                /* qos        */ current_qos, 
                /* callback   */ std::move(ISIR_fd_ee_pose_topic_subscription_lambda)  
            );
        this->m_ISIR_ctrl_params_topic_subscriber 
            = this->create_subscription<ISIR_ctrl_params_topic_type>(
                /* topic_name */ self_type::_s_ISIR_ctrl_params_topic_name.data(), 
                /* qos        */ current_qos, 
                /* callback   */ std::move(ISIR_ctrl_params_topic_subscription_lambda)  
            );
        
        this->m_ISIR_fd_ee_pose_topic_sync_subscriber 
            = std::make_shared< 
                message_filters::Subscriber<ISIR_fd_ee_pose_topic_type> 
            >(
                /* node ptr   */ this,
                /* topic_name */ self_type::_s_ISIR_fd_ee_pose_topic_name.data(), 
                /* QoS        */ current_qos.get_rmw_qos_profile() 
            );
        this->m_ISIR_ctrl_params_topic_sync_subscriber
            = std::make_shared<
                message_filters::Subscriber<ISIR_ctrl_params_topic_type>
            >(
                /* node ptr   */ this,
                /* topic_name */ self_type::_s_ISIR_ctrl_params_topic_name.data(), 
                /* QoS        */ current_qos.get_rmw_qos_profile() 
            );

        // the sync mechanism
        this->m_pSync 
            = std::make_shared<
                message_filters::Synchronizer<
                    message_filters::sync_policies::ApproximateTime<
                        ISIR_fd_ee_pose_topic_type, 
                        ISIR_ctrl_params_topic_type
                    >
                >
            >(
                message_filters::sync_policies::ApproximateTime<
                    ISIR_fd_ee_pose_topic_type, 
                    ISIR_ctrl_params_topic_type
                >(_queue_sz),
                *(this->m_ISIR_fd_ee_pose_topic_sync_subscriber), 
                *(this->m_ISIR_ctrl_params_topic_sync_subscriber)
            );
        this->m_pSync->setAgePenalty(0.50);
        this->m_pSync->registerCallback(
            std::bind(
                std::move(sync_lambda),
                std::placeholders::_1,
                std::placeholders::_2
            )
        );
        
        this->m_timer 
            = this->create_wall_timer(
                self_type::_s_gateway_tick_period, 
                std::move(tick_lambda)
            );

    } /* UpstreamGateway() */

} /* } Labsim::apollon::feature::ROS2 */