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
#include <string_view>
#include <atomic>

// ROS2 include
#include "rclcpp/rclcpp.hpp"

// other msg include 
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

    class DownstreamGateway 
        : private NonCopyable
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

        using gateway_topic_type = lexikhum_oat_gateway_msgs::msg::Downstream; 

        // constants 

        //
        // TODO :
        // CREATE ISIR TOPIC NAME HERE (?)
        //
        // static constexpr auto _s_ISIR_topic_name  = "??"sv;
        //
        
        static constexpr auto _s_gateway_topic_name  = "ONERA_to_ISIR_Downstream"sv;
        static constexpr auto _s_gateway_node_name   = "lexikhum_oat_downstream_gateway"sv;

        static constexpr auto _s_gateway_tick_period = 100ms;

        // Default explicit Ctor
        
        explicit DownstreamGateway()
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

        rclcpp::Subscription<gateway_topic_type>::SharedPtr 
            m_subscriber{ };

        alignas(std::atomic_ref<gateway_topic_type>::required_alignment) 
        gateway_topic_type 
            m_downstream_buffer{ };

        std::atomic_ref<gateway_topic_type>
            m_downstream_buffer_ref{ this->m_downstream_buffer };

        size_t 
            m_uuid{ 0 };

    }; /* class DownstreamGateway */

} /* } Labsim::apollon::feature::ROS2 */

int main(int argc, char * argv[])
{

    // standard ROS2 Node  
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Labsim::apollon::feature::ROS2::DownstreamGateway>());
    rclcpp::shutdown();

    // sucess 
    std::exit(EXIT_SUCCESS);

} /* main() */