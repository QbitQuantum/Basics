void HierarchicalWalkingIK::computeWalkingTrajectory(const Eigen::Matrix3Xf& comTrajectory,
                                                     const Eigen::Matrix6Xf& rightFootTrajectory,
                                                     const Eigen::Matrix6Xf& leftFootTrajectory,
                                                     std::vector<Eigen::Matrix3f>& rootOrientation,
                                                     Eigen::MatrixXf& trajectory)
{
    int rows = outputNodeSet->getSize();

    trajectory.resize(rows, rightFootTrajectory.cols());
    rootOrientation.resize(rightFootTrajectory.cols());

    Eigen::Vector3f com = colModelNodeSet->getCoM();

    Eigen::VectorXf configuration;
    int N = trajectory.cols();

    Eigen::Matrix4f leftFootPose  = Eigen::Matrix4f::Identity();
    Eigen::Matrix4f rightFootPose = Eigen::Matrix4f::Identity();
    Eigen::Matrix4f chestPose     = chest->getGlobalPose();
    Eigen::Matrix4f pelvisPose    = pelvis->getGlobalPose();

    for (int i = 0; i < N; i++)
    {
        VirtualRobot::MathTools::posrpy2eigen4f(1000 * leftFootTrajectory.block(0, i, 3, 1),  leftFootTrajectory.block(3, i, 3, 1),  leftFootPose);
        VirtualRobot::MathTools::posrpy2eigen4f(1000 * rightFootTrajectory.block(0, i, 3, 1), rightFootTrajectory.block(3, i, 3, 1), rightFootPose);

        // FIXME the orientation of the chest and chest is specific to armar 4
        // since the x-Axsis points in walking direction
        Eigen::Vector3f xAxisChest = (leftFootPose.block(0, 1, 3, 1) + rightFootPose.block(0, 1, 3, 1))/2;
        xAxisChest.normalize();
        chestPose.block(0, 0, 3, 3) = Bipedal::poseFromXAxis(xAxisChest);
        pelvisPose.block(0, 0, 3, 3) = Bipedal::poseFromYAxis(-xAxisChest);

        std::cout << "Frame #" << i << ", ";
        robot->setGlobalPose(leftFootPose);
        computeStepConfiguration(1000 * comTrajectory.col(i),
                                 rightFootPose,
                                 chestPose,
                                 pelvisPose,
                                 configuration);

        trajectory.col(i) = configuration;
        rootOrientation[i] = leftFootPose.block(0, 0, 3, 3);
    }
}