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
#ifndef LEXIKHUM_OAT_GATEWAY_LEXIKHUMOAT_NONCOPYABLE_HPP_
#define LEXIKHUM_OAT_GATEWAY_LEXIKHUMOAT_NONCOPYABLE_HPP_

// avoid namespace pollution
namespace Labsim::apollon::feature::ROS2
{    

    class NonCopyable
    {

        //
        // non-copyable pattern
        // - public constexpr default ctor
        // - public virtual protective dtor 
        // - public deleted copy ctor/assignment
        //

    public:

        // using 

        using self_type = NonCopyable;

        // Coplien form - rule of 5

        constexpr NonCopyable()
            = default;

        NonCopyable(self_type const & _rhs)
            = delete;

        NonCopyable(self_type && _rhs)
            = delete;

        virtual ~NonCopyable()
            = default;

        auto
        operator=(self_type const & _rhs)
            -> self_type & = delete;
        
        auto
        operator=(self_type && _rhs)
            -> self_type & = delete;

    }; /* class NonCopyable */

} /* } Labsim::apollon::feature::ROS2 */

#endif /* LEXIKHUM_OAT_GATEWAY_LEXIKHUMOAT_NONCOPYABLE_HPP_ */