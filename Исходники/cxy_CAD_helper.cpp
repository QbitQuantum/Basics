    void cxy_CAD_helper::getNormal(
            geometry_msgs::Point const& v1
            , geometry_msgs::Point const& v2
            , geometry_msgs::Point const& v3
            , geometry_msgs::Vector3 & normal)
    {
        Eigen::Vector3d vec1, vec2;
        Eigen::Vector3d ev1, ev2, ev3;
        Eigen::Vector3d enormal;

        ev1 = Eigen::Vector3d(v1.x, v1.y, v1.z);
        ev2 = Eigen::Vector3d(v2.x, v2.y, v2.z);
        ev3 = Eigen::Vector3d(v3.x, v3.y, v3.z);

        vec1 = ev2 - ev1;
        vec2 = ev3 - ev1;

        try
        {
            enormal = vec1.cross(vec2);
            enormal.normalize();

            normal.x = enormal(0);
            normal.y = enormal(1);
            normal.z = enormal(2);
        }
        catch (...)
        {
            ROS_WARN_STREAM("cxy_CAD_helper::getNormal exception. Block 1.");
        }
    }