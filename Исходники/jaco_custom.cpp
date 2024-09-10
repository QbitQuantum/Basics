// Move the end effector (tf jaco_tool_position) to a certain position
void JacoCustom::moveToPoint(tf::Transform tf_){

    geometry_msgs::Twist arm;
    arm.linear.x = tf_.getOrigin().getX();
    arm.linear.y = tf_.getOrigin().getY();
    arm.linear.z = tf_.getOrigin().getZ();

//    double roll, pitch, yaw;
//    tf_.getBasis().getRPY(roll,pitch, yaw);
//    arm.angular.x = roll;
//    arm.angular.y = pitch;
//    arm.angular.z = yaw;



    wpi_jaco_msgs::QuaternionToEuler conv;
    geometry_msgs::Quaternion quat;
    tf::quaternionTFToMsg(tf_.getRotation(), quat);
    conv.request.orientation = quat;
    if(quaternion_to_euler_service_client.call(conv)){
        arm.angular.x = conv.response.roll;
        arm.angular.y = conv.response.pitch;
        arm.angular.z = conv.response.yaw;
    }

    moveToPoint(arm);
}