// std include
#include <cstdlib>
#include <functional>
#include <chrono>
#include <memory>

// ROS2 include
#include "rclcpp/rclcpp.hpp"
#include "lexikhum_oat_gateway_msgs/msg/upstream.hpp"

//
// TODO :
// ADD ISIR MESSAGE INCLUDE DIRECTIVE HERE (?)
//

// avoid namespace pollution
namespace Labsim::apollon::feature::ROS2 
{

    using namespace std::chrono_literals;

    class LEXIKHUMOATUpstreamGateway
        : public rclcpp::Node
    {

    public:
        LEXIKHUMOATUpstreamGateway()
            : Node("lexikhum_oat_gateway")
            , m_uuid(0)
        {

            this->m_publisher 
                = this->create_publisher<lexikhum_oat_gateway_msgs::msg::Upstream>("ISIR_to_ONERA_Upstream", 10);

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

            auto msg = lexikhum_oat_gateway_msgs::msg::Upstream();
            msg.uuid = this->m_uuid++;
            RCLCPP_INFO_STREAM(
                this->get_logger(), 
                "Publishing: '" 
                    << msg.uuid 
                    << "'"
            );
            this->m_publisher->publish(msg);

        } /* tick() */

        //
        // TODO :
        // ADD ISIR TOPIC SUBSCRIBER CALLBACK HERE (?)
        //

    private:
        rclcpp::TimerBase::SharedPtr m_timer;
        rclcpp::Publisher<lexikhum_oat_gateway_msgs::msg::Upstream>::SharedPtr m_publisher;
        //
        // TODO :
        // ADD ISIR TOPIC SUBSCRIBER HERE (?)
        //
        size_t m_uuid;
    
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