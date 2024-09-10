void mtsIntuitiveResearchKitPSM::RunPositionCartesian(void)
{
    //! \todo: should prevent user to go to close to RCM!

    if (IsCartesianGoalSet == true) {
        vctDoubleVec jointSet(6, 0.0);
        jointSet.Assign(JointCurrent, 6);

        // compute desired slave position
        CartesianPositionFrm.From(CartesianGoalSet.Goal());
        CartesianPositionFrm = CartesianPositionFrm * Frame6to7Inverse;

        Manipulator.InverseKinematics(jointSet, CartesianPositionFrm);
        jointSet.resize(7);
        jointSet[6] = DesiredOpenAngle;
#if 1 // Anton
        const double difference = JointCurrent[3] - jointSet[3];
        const double differenceInTurns = nearbyint(difference / (2.0 * cmnPI));
        jointSet[3] = jointSet[3] + differenceInTurns * 2.0 * cmnPI;
        /*
        if (differenceInTurns != 0.0) {
            CMN_LOG_CLASS_RUN_DEBUG << GetName()
                                    << " diff = " << difference
                                    << " turns = " << difference / (2.0 * cmnPI)
                                    << " corr = " << differenceInTurns
                                    << " res = " << jointSet[3] << std::endl;
        }
        */
#endif // Anton
        SetPositionJointLocal(jointSet);

        // reset flag
        IsCartesianGoalSet = false;
    }
}