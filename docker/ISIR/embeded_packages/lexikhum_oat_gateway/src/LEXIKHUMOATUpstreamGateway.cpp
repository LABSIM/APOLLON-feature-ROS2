// std include
#include <cstdlib>
#include <functional>
#include <chrono>
#include <string_view>
#include <memory>
#include <atomic>

// ROS2 include
#include "rclcpp/rclcpp.hpp"
#include "lexikhum_oat_gateway_msgs/msg/upstream.hpp"

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

    class LEXIKHUMOATUpstreamGateway
        : public rclcpp::Node
    {

    public:
        static constexpr std::string_view _s_node_name  = "lexikhum_oat_gateway"sv;
        static constexpr std::string_view _s_topic_name = "ONERA_to_ISIR_Downstream"sv;

    public:
        LEXIKHUMOATUpstreamGateway()
            : Node(LEXIKHUMOATUpstreamGateway::_s_node_name.data())
        {

            this->m_publisher 
                = this->create_publisher<lexikhum_oat_gateway_msgs::msg::Upstream>(
                    /* topic_name        */ LEXIKHUMOATUpstreamGateway::_s_topic_name.data(), 
                    /* qos_history_depth */ 10
                );

            //
            // TODO :
            // CREATE ISIR TOPIC SUBSCRIBER CALLBACK HERE (?)
            //
            
            this->m_timer 
                = this->create_wall_timer(
                    500ms, 
                    std::bind(
                        &LEXIKHUMOATUpstreamGateway::tick, 
                        this
                    )
                );

        } /* LEXIKHUMOATUpstreamGateway() */

    private:
        void tick()
        {

            auto current_build = lexikhum_oat_gateway_msgs::msg::Upstream();
            current_build.uuid = this->m_buffer_uuid++;

            RCLCPP_INFO_STREAM(
                this->get_logger(), 
                "Publishing: '" 
                    << current_build.uuid 
                    << "'"
            );
            
            this->m_buffer_ref = current_build;
            this->m_publisher->publish(this->m_buffer_ref.load());

        } /* tick() */

        //
        // TODO :
        // ADD ISIR TOPIC SUBSCRIBER CALLBACK HERE (?)
        //

    private:

        rclcpp::TimerBase::SharedPtr 
            m_timer{ };

        //
        // TODO :
        // ADD ISIR TOPIC SUBSCRIBER HERE (?)
        //

        rclcpp::Publisher<lexikhum_oat_gateway_msgs::msg::Upstream>::SharedPtr 
            m_publisher{ };

        alignas(std::atomic_ref< lexikhum_oat_gateway_msgs::msg::Upstream >::required_alignment) 
        lexikhum_oat_gateway_msgs::msg::Upstream 
            m_buffer{ };

        std::atomic_ref< lexikhum_oat_gateway_msgs::msg::Upstream >
            m_buffer_ref{ this->m_buffer };

        size_t 
            m_buffer_uuid{ 0 };
    
    }; /* class LEXIKHUMOATUpstreamGateway */

} /* } Labsim::apollon::feature::ROS2 */

int main(int argc, char * argv[])
{

    // standard ROS2 Node  
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Labsim::apollon::feature::ROS2::LEXIKHUMOATUpstreamGateway>());
    rclcpp::shutdown();

    // success 
    std::exit(EXIT_SUCCESS);

} /* main() */