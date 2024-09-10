void HeaderManipulation::publishMsg(const topic_tools::ShapeShifter &msg, const ros::Time &msg_in_time)
{
    ROS_DEBUG("HeaderManipulation publishMsg Thread started with timestamp %f", msg_in_time.toSec());
    ros::Time end_time(ros::Time::now());
    ros::Time last_time;
    config_mutex_.lock();
    ros::Time time_to_pub(msg_in_time + msg_delay_);
    config_mutex_.unlock();
    do
    {
        last_time = end_time;
        ROS_DEBUG("waiting to publish msg from %f at %f", msg_in_time.toSec(), time_to_pub.toSec());
        if (end_time > time_to_pub)
        {
            boost::mutex::scoped_lock pub_lock(pub_mutex_);
            ROS_DEBUG("publishing msg which should be held back till: %f", time_to_pub.toSec());
            generic_pub_.publish(msg);
            return;
        }
        boost::mutex::scoped_lock config_lock(config_mutex_);
        publish_retry_rate_.sleep();
        time_to_pub = msg_in_time + msg_delay_;
        end_time = ros::Time::now();
    } while (last_time <= end_time);
    ROS_WARN("Detected jump back in time. Dropping msg. last: %f, end %f",
             last_time.toSec(), end_time.toSec());
    return;
}