// the callback function for the timer event
void SumAndAverageNode::timerCallback(ros::TimerEvent const& event)
{
// create the message containing the moving average
    std_msgs::Float32 moving_average_msg;
    if (moving_average_count_ > 0)
        moving_average_msg.data = moving_average_sum_ / moving_average_count_;
    else
        moving_average_msg.data = nan("");
// publish the moving average
    moving_average_pub_.publish(moving_average_msg);
// reset the moving average
    moving_average_sum_ = 0;
    moving_average_count_ = 0;
}