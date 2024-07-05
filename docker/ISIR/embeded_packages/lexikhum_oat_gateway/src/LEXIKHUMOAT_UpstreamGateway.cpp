// Lexikhum OAT include
#include "lexikhum_oat_gateway/LEXIKHUMOAT_NonCopyable.hpp"

// Lexikhum OAT msg include
#include "lexikhum_oat_gateway_msgs/msg/upstream.hpp"

//
// TODO :
// ADD ISIR MESSAGE INCLUDE DIRECTIVE HERE (?)
//

// std include
#include <cstdlib>
#include <functional>
#include <chrono>
#include <string_view>
#include <memory>
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

    class UpstreamGateway
        : public NonCopyable
        , public rclcpp::Node
    {
        
    public:
     
        // aliases

        using self_type = UpstreamGateway;
        using base_type = rclcpp::Node;

        //
        // TODO :
        // CREATE ISIR TOPIC TYPE ALIAS HERE (?)
        //
        //  using ISIR_topic_type = msg::ISIRTopicT;
        //

        using gateway_topic_type = lexikhum_oat_gateway_msgs::msg::Upstream;      
        
        // constants 

        //
        // TODO :
        // CREATE ISIR TOPIC NAME HERE (?)
        //
        // static constexpr auto _s_ISIR_topic_name  = "??"sv;
        //

        static constexpr auto _s_gateway_topic_name  = "ISIR_to_ONERA_Upstream"sv;
        static constexpr auto _s_gateway_node_name   = "lexikhum_oat_upstream_gateway"sv;

        static constexpr auto _s_gateway_tick_period = 100ms;

        // Default explicit Ctor

        explicit UpstreamGateway()
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
            //         this->m_downstream_buffer_ref.? = _msg.?;
            //         [...]
            //         this->m_downstream_buffer_ref.? = _msg.?;
            //
            //     }; /* ISIR_subscription_lambda */
            //

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

                    // RCLCPP_INFO_STREAM(
                    //     this->get_logger(), 
                    //     "I Send: '" 
                    //         << buffer.uuid 
                    //         << "'"
                    // );

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
            
            this->m_timer 
                = this->create_wall_timer(
                    self_type::_s_gateway_tick_period, 
                    std::move(tick_lambda)
                );

        } /* UpstreamGateway() */

    private:

        // members

        rclcpp::TimerBase::SharedPtr 
            m_timer{ };

        //
        // TODO :
        // ADD ISIR TOPIC SUBSCRIBER HERE (?)
        //
        // rclcpp::Subscription<ISIR_topic_type>::SharedPtr 
        //     m_ISIR_subscriber{ };
        //

        rclcpp::Publisher<gateway_topic_type>::SharedPtr 
            m_publisher{ };

        alignas(std::atomic_ref<gateway_topic_type>::required_alignment) 
        gateway_topic_type 
            m_upstream_buffer{ };

        std::atomic_ref<gateway_topic_type>
            m_upstream_buffer_ref{ this->m_upstream_buffer };

        size_t 
            m_uuid{ 0 };
    
    }; /* class UpstreamGateway */

} /* } Labsim::apollon::feature::ROS2 */

int main(int argc, char * argv[])
{

    // standard ROS2 Node  
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Labsim::apollon::feature::ROS2::UpstreamGateway>());
    rclcpp::shutdown();

    // success 
    std::exit(EXIT_SUCCESS);

} /* main() */