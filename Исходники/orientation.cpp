int hormodular::Orientation::getRelativeOrientation(int connector, hormodular::Orientation localOrient, hormodular::Orientation remoteOrient)
{
    //-- Create rotation matrices for local orientation:
    Eigen::AngleAxisd rollAngle( deg2rad(localOrient.getRoll()), Eigen::Vector3d::UnitZ());
    Eigen::AngleAxisd pitchAngle( deg2rad(localOrient.getPitch()), Eigen::Vector3d::UnitY());
    Eigen::AngleAxisd yawAngle( deg2rad(localOrient.getYaw()), Eigen::Vector3d::UnitX());

    Eigen::Quaterniond q0 = yawAngle * pitchAngle * rollAngle ;
    Eigen::Matrix3d rotationMatrix = q0.matrix();

    //-- Create rotation matrices for the other orientation:
    Eigen::AngleAxisd otherRollAngle(  deg2rad(remoteOrient.getRoll()), Eigen::Vector3d::UnitZ());
    Eigen::AngleAxisd otherPitchAngle( deg2rad(remoteOrient.getPitch()), Eigen::Vector3d::UnitY());
    Eigen::AngleAxisd otherYawAngle(   deg2rad(remoteOrient.getYaw()), Eigen::Vector3d::UnitX());

    Eigen::Quaterniond q1 = otherYawAngle * otherPitchAngle * otherRollAngle;
    Eigen::Matrix3d otherRotationMatrix = q1.matrix();

    Eigen::Matrix3d relativeRotation = rotationMatrix.inverse() * otherRotationMatrix;

    Eigen::Vector3d new_z = relativeRotation * Eigen::Vector3d::UnitZ();

//    std::cout << "New_z: " << std::endl << new_z << std::endl << std::endl;

    //-- Get connector base vector for the rotations:
    Eigen::Vector3d base_vector;
    if ( connector == 0 || connector == 2)
    {
        //-- Y axis
        base_vector = Eigen::Vector3d::UnitY();
    }
    else if ( connector == 1 || connector == 3)
    {
        //-- X axis
        base_vector = Eigen::Vector3d::UnitX();
    }

    //-- Try for rotations to fit the vector
    for ( int i = 0; i < 4; i++)
    {
        Eigen::AngleAxisd rotAngle( deg2rad(i*90), base_vector);
        Eigen::Matrix3d rotMatrix = rotAngle.matrix();
        Eigen::Vector3d result_vector = rotMatrix * Eigen::Vector3d::UnitZ();

//        std::cout << "i = " << i << std::endl << result_vector << std::endl << std::endl;

        if ( vector_equal(result_vector, new_z) )
            return i;
    }

    return -1;
}