void DynamicsRobot::setGlobalPose(Eigen::Matrix4f &gp)
{
    Eigen::Matrix4f currentPose = robot->getGlobalPose();
    Eigen::Matrix4f delta = gp * currentPose.inverse();

    robot->setGlobalPose(gp);
    std::map<VirtualRobot::RobotNodePtr, DynamicsObjectPtr>::iterator it = dynamicRobotNodes.begin();
    while (it != dynamicRobotNodes.end())
    {
        Eigen::Matrix4f newPose = it->second->getSceneObject()->getGlobalPose() * delta;
        it->second->setPose(newPose);
        it++;
    }
}