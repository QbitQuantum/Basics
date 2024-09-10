void encoderTickCallback(const sek_drive::encoders::ConstPtr& msg)
{
    renc = - msg->right_wheel;
    lenc = msg->left_wheel;
    current_time = ros::Time::now();
    if ((current_time.toSec() - enc_loop_time.toSec())>=0.05)
    {
        calcOdom();
        enc_loop_time_2 = current_time;
    }
}