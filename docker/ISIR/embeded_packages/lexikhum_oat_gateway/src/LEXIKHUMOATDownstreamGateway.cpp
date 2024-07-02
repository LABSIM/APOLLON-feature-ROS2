// std include
#include <cstdlib>
#include <functional>
#include <chrono>
#include <memory>

// ROS2 include
#include "rclcpp/rclcpp.hpp"
#include "lexikhum_oat_gateway_msgs/msg/downstream.hpp"

//
// TODO :
// ADD ISIR MESSAGE INCLUDE DIRECTIVE HERE (?)
//

// avoid namespace pollution
namespace Labsim::apollon::feature::ROS2
{

    using namespace std::chrono_literals;
    // using std::placeholders::_1;

    class LEXIKHUMOATDownstreamGateway 
        : public rclcpp::Node
    {

    public:
        LEXIKHUMOATDownstreamGateway()
            : Node("lexikhum_oat_gateway")
            , m_uuid(0)
        {

            //
            // TODO :
            // CREATE ISIR TOPIC PUBLISHER HERE (?)
            //

            this->m_subscriber 
                = this->create_subscription<lexikhum_oat_gateway_msgs::msg::Downstream>(
                    "ONERA_to_ISIR_Downstream", 
                    10, 
                    std::bind(
                        &LEXIKHUMOATDownstreamGateway::ONERA_to_ISIR_Downstream_callback, 
                        this, 
                        std::placeholders::_1
                    )
                );

                            
            this->m_timer 
                = this->create_wall_timer(
                    500ms, 
                    std::bind(
                        &LEXIKHUMOATDownstreamGateway::tick, 
                        this
                    )
                );
        }

    private:
        void tick()
        {

            //
            // TODO :
            // ADD ISIR TOPIC PUBLISHING HERE (?)
            //

        } /* tick() */

        void ONERA_to_ISIR_Downstream_callback(lexikhum_oat_gateway_msgs::msg::Downstream const & _msg) const
        {

            RCLCPP_INFO_STREAM(
                this->get_logger(), 
                "I heard: '" 
                    << _msg.uuid 
                    << "'"
            );

        } /* ONERA_to_ISIR_Downstream_callback() */

        private:
        rclcpp::TimerBase::SharedPtr m_timer;
        //
        // TODO :
        // ADD ISIR TOPIC PUBLISHER HERE (?)
        //
        rclcpp::Subscription<lexikhum_oat_gateway_msgs::msg::Downstream>::SharedPtr m_subscriber;
        size_t m_uuid;

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