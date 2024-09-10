void
fromPose(const geometry_msgs::Pose &source, Eigen::Matrix4f &dest, tf::Transform &tf_dest)
{
    Eigen::Quaternionf q(source.orientation.w, source.orientation.x, source.orientation.y, source.orientation.z);
    q.normalize();
    Eigen::Vector3f t(source.position.x, source.position.y, source.position.z);
    Eigen::Matrix3f R(q.toRotationMatrix());
    dest(0,0) = R(0,0);
    dest(0,1) = R(0,1);
    dest(0,2) = R(0,2);
    dest(1,0) = R(1,0);
    dest(1,1) = R(1,1);
    dest(1,2) = R(1,2);
    dest(2,0) = R(2,0);
    dest(2,1) = R(2,1);
    dest(2,2) = R(2,2);
    dest(3,0) = dest(3,1)= dest(3,2) = 0;
    dest(3,3) = 1;
    dest(0,3) = t(0);
    dest(1,3) = t(1);
    dest(2,3) = t(2);
    tf::Quaternion qt(q.x(), q.y(), q.z(), q.w());
    tf_dest.setOrigin(tf::Vector3(t(0), t(1), t(2)));
    tf_dest.setRotation(qt);
}