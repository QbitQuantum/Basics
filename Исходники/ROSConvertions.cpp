void ros_convertions::toROS( ros::Time& ros, ::base::Time const& value )
{
    ros.fromNSec(value.toMicroseconds() * 1000);
}