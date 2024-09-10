void revert_applied_readings_since(const ros::Time& time)
{
    int msec = (int)(time.toNSec()/1000l);

    int k = 0;

    for(std::vector<ras_arduino_msgs::Encoders>::reverse_iterator it = _ringbuffer.rbegin(); it != _ringbuffer.rend(); ++it)
    {
        ras_arduino_msgs::Encoders& enc = *it;
        if (enc.timestamp >= msec)
        {
            ++k;

            double dist_l = (2.0*M_PI*robot::dim::wheel_radius) * (enc.delta_encoder1 / robot::prop::ticks_per_rev);
            double dist_r = (2.0*M_PI*robot::dim::wheel_radius) * (enc.delta_encoder2 / robot::prop::ticks_per_rev);

            _theta += (dist_r - dist_l) / robot::dim::wheel_distance;

            double dist = (dist_r + dist_l) / 2.0;

            _x += dist * cos(_theta);
            _y += dist * sin(_theta);

            //remove reading
            _ringbuffer.erase(--it.base());
        }
    }

    ROS_ERROR("[PoseGenerator::revertReadingsSince] Reverted %d readings.",k);
}