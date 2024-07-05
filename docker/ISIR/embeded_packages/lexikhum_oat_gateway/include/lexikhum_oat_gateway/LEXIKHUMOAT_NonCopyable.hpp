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