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
#include "lexikhum_oat_gateway/LEXIKHUMOAT_UpstreamGateway.hpp"

int main(int argc, char * argv[])
{

    // standard ROS2 Node  
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Labsim::apollon::feature::ROS2::UpstreamGateway>());
    rclcpp::shutdown();

    // success 
    std::exit(EXIT_SUCCESS);

} /* main() */