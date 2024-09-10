void FlipHandsGoalRegion::sample(std::vector<double> &xyz_rpy)
{
    // compute the approach pose so that the gripper is perpendicular to the given direction with a random slant with
    // respect to the horizontal plane

    boost::uniform_real<double> dist(-0.5, 0.5) ;
    Vector3d pos2_offset = Vector3d(planner->x_tol * dist(gen), planner->y_tol * dist(gen), planner->z_tol * dist(gen)) ;

    // compute the pose of the grasping arm (arm 2)

    Vector3d pos2 = pos2_offset + p1.translation() ;

    double d = (p1.translation() - p2.translation()).norm() ;

    Vector3d pos1 = p2.translation() + pos2_offset +
            Vector3d(boost::uniform_real<double>(-0.05, 0.05)(gen), boost::uniform_real<double>(-0.05, 0.05)(gen), boost::uniform_real<double>(0, 0.2)(gen));

    double roll1, pitch1, yaw1, x1, y1, z1 ;

    x1 = pos1.x(), y1 = pos1.y(), z1 = pos1.z() ;
    if ( planner->arm == "r1" )
        rpyFromQuat(lookAt(Vector3d(1, 0, 0)), roll1, pitch1, yaw1) ;
    else
        rpyFromQuat(lookAt(Vector3d(-1, 0, 0)), roll1, pitch1, yaw1) ;


    double roll2, pitch2, yaw2, x2, y2, z2 ;

    x2 = pos2.x() ; y2 = pos2.y() ; z2 = pos2.z() ;
    rpyFromQuat(Quaterniond(p1.rotation()), roll2, pitch2, yaw2) ;

    double pitch = boost::uniform_real<double>(planner->pitch_tol_min, planner->pitch_tol_max)(gen) ;
    double yaw = boost::uniform_real<double>(planner->yaw_tol_min, planner->yaw_tol_max)(gen) ;
    double roll = boost::uniform_real<double>(planner->roll_tol_min, planner->roll_tol_max)(gen) ;

    roll1 += roll ;  yaw1 += yaw ; pitch1 += pitch ;

    if ( planner->arm == "r1" )
    {
        xyz_rpy.push_back(x1) ;  xyz_rpy.push_back(y1) ;   xyz_rpy.push_back(z1) ;
        xyz_rpy.push_back(roll1) ;  xyz_rpy.push_back(pitch1) ; xyz_rpy.push_back(yaw1) ;

        xyz_rpy.push_back(x2) ;  xyz_rpy.push_back(y2) ;   xyz_rpy.push_back(z2) ;
        xyz_rpy.push_back(roll2) ;  xyz_rpy.push_back(pitch2) ; xyz_rpy.push_back(yaw2) ;


    }
    else
    {
        xyz_rpy.push_back(x2) ;  xyz_rpy.push_back(y2) ;   xyz_rpy.push_back(z2) ;
        xyz_rpy.push_back(roll2) ;  xyz_rpy.push_back(pitch2) ; xyz_rpy.push_back(yaw2) ;

        xyz_rpy.push_back(x1) ;  xyz_rpy.push_back(y1) ;   xyz_rpy.push_back(z1) ;
        xyz_rpy.push_back(roll1) ;  xyz_rpy.push_back(pitch1) ; xyz_rpy.push_back(yaw1) ;

    }

}