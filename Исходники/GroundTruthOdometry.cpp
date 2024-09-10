Eigen::Matrix4f GroundTruthOdometry::getTransformation(uint64_t timestamp)
{
    Eigen::Matrix4f pose = Eigen::Matrix4f::Identity();

    if(last_utime != 0)
    {
        std::map<uint64_t, Eigen::Isometry3f>::const_iterator it = camera_trajectory.find(last_utime);
        if (it == camera_trajectory.end())
        {
            last_utime = timestamp;
            return pose;
        }

        //Poses are stored in the file in iSAM basis, undo it
        Eigen::Matrix4f M;
        M <<  0,  0, 1, 0,
             -1,  0, 0, 0,
              0, -1, 0, 0,
              0,  0, 0, 1;

        pose = M.inverse() * camera_trajectory[timestamp] * M;
    }
    else
    {
        std::map<uint64_t, Eigen::Isometry3f>::const_iterator it = camera_trajectory.find(timestamp);
        Eigen::Isometry3f ident = it->second;
        pose = Eigen::Matrix4f::Identity();
        camera_trajectory[last_utime] = ident;
    }

    last_utime = timestamp;

    return pose;
}