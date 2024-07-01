// std include
#include <ctsdlib>
#include <chrono>
#include <memory>

// ROS2 include
#include "rclcpp/rclcpp.hpp"
#include "lexikhum_oat_gateway_msgs/msg/LEXIKHUMOATUpstream.hpp"

//
// TODO :
// ADD ISIR MESSAGE INCLUDE DIRECTIVE HERE (?)
//

// avoid namespace pollution
namespace Labsim::gateway::ROS2 
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
                = this->create_publisher<lexikhum_oat_gateway_msgs::msg::LEXIKHUMOATUpstream>("ISIR_to_ONERA_Upstream", 10);

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

            auto message = lexikhum_oat_gateway_msgs::msg::LEXIKHUMOATUpstream();
            message.uuid = this->m_uuid++;
            RCLCPP_INFO_STREAM(
                this->get_logger(), 
                "Publishing: '" 
                    << message.uuid 
                    << "'"
            );
            this->m_publisher->publish(message);

        } /* tick() */

        //
        // TODO :
        // ADD ISIR TOPIC SUBSCRIBER CALLBACK HERE (?)
        //

    private:
        rclcpp::TimerBase::SharedPtr m_timer;
        rclcpp::Publisher<lexikhum_oat_gateway_msgs::msg::LEXIKHUMOATUpstream>::SharedPtr m_publisher;
        //
        // TODO :
        // ADD ISIR TOPIC SUBSCRIBER HERE (?)
        //
        size_t m_uuid;
    
    }; /* class LEXIKHUMOATUpstreamGateway */

} /* } Labsim::gateway::ROS2 */

int main(int argc, char * argv[])
{

    // standard ROS2 Node  
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Labsim::gateway::ROS2::LEXIKHUMOATUpstreamGateway>());
    rclcpp::shutDown();

    // sucess 
    return std::exit(EXIT_SUCCESS);

} /* main() */