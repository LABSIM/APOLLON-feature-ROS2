// std include
#include <cstdlib>
#include <functional>
#include <chrono>
#include <memory>
#include <string_view>
#include <atomic>

// ROS2 include
#include "rclcpp/rclcpp.hpp"
#include "lexikhum_oat_gateway_msgs/msg/downstream.hpp"

//
// TODO :
// ADD ISIR MESSAGE INCLUDE DIRECTIVE HERE (?)
//

#include "std_msgs/msg/bool.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
#include "sensor_msgs/msg/joint_state.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "geometry_msgs/msg/point.hpp"
#include "geometry_msgs/msg/wrench.hpp"
#include "geometry_msgs/msg/twist.hpp"

// avoid namespace pollution
namespace Labsim::apollon::feature::ROS2
{

    using namespace std::literals;
    using namespace std::chrono_literals;
    // using std::placeholders::_1;

    class LEXIKHUMOATDownstreamGateway 
        : public rclcpp::Node
    {

    public:
        using self_type = LEXIKHUMOATDownstreamGateway;
        using base_type = rclcpp::Node;

    public:
        static constexpr std::string_view _s_node_name  = "lexikhum_oat_gateway"sv;
        static constexpr std::string_view _s_topic_name = "ONERA_to_ISIR_Downstream"sv;

    public:
        explicit LEXIKHUMOATDownstreamGateway()
            : base_type(self_type::_s_node_name.data())
        {

            //
            // TODO :
            // CREATE ISIR TOPIC PUBLISHER HERE (?)
            //

            auto subscription_callback 
                = [this](lexikhum_oat_gateway_msgs::msg::Downstream const & _msg) 
                    -> void
                {

                    RCLCPP_INFO_STREAM(
                        this->get_logger(), 
                        "I heard: '" 
                            << _msg.uuid 
                            << "'"
                    );

                    this->m_buffer_ref = _msg;

                }; /* subscription_callback lambda */

            this->m_subscriber 
                = this->create_subscription<lexikhum_oat_gateway_msgs::msg::Downstream>(
                    /* topic_name        */ self_type::_s_topic_name.data(), 
                    /* qos_history_depth */ 10, 
                    /* callback lambda   */ std::move(subscription_callback)  
                );
        
            this->m_timer 
                = this->create_wall_timer(
                    500ms, 
                    std::bind(
                        &self_type::tick, 
                        this
                    )
                );

        } /* LEXIKHUMOATDownstreamGateway() */

    private:
        auto tick()
            -> void
        {

            //
            // TODO :
            // ADD ISIR TOPIC PUBLISHING HERE (?)
            //

        } /* tick() */

    private:

        rclcpp::TimerBase::SharedPtr 
            m_timer{ };

        //
        // TODO :
        // ADD ISIR TOPIC PUBLISHER HERE (?)
        //

        rclcpp::Subscription<lexikhum_oat_gateway_msgs::msg::Downstream>::SharedPtr 
            m_subscriber{ };

        alignas(std::atomic_ref< lexikhum_oat_gateway_msgs::msg::Downstream >::required_alignment) 
        lexikhum_oat_gateway_msgs::msg::Downstream 
            m_buffer{ };

        std::atomic_ref< lexikhum_oat_gateway_msgs::msg::Downstream >
            m_buffer_ref{ this->m_buffer };

        size_t 
            m_buffer_uuid{ 0 };

    }; /* class LEXIKHUMOATDownstreamGateway */

} /* } Labsim::apollon::feature::ROS2 */

int main(int argc, char * argv[])
{

    // standard ROS2 Node  
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Labsim::apollon::feature::ROS2::LEXIKHUMOATDownstreamGateway>());
    rclcpp::shutdown();

    // sucess 
    std::exit(EXIT_SUCCESS);

} /* main() */