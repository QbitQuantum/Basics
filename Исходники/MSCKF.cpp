void MSCKF::addSlideState()
{
    SlideState newState;
    int nominalStateLength = (int)fullNominalState.size();
    int errorStateLength = (int)fullErrorCovariance.rows();
    
    VectorXd tmpNominal = VectorXd::Zero(nominalStateLength + NOMINAL_POSE_STATE_SIZE);
    MatrixXd tmpCovariance = MatrixXd::Zero(errorStateLength + ERROR_POSE_STATE_SIZE, errorStateLength + ERROR_POSE_STATE_SIZE);
    MatrixXd Jpi = MatrixXd::Zero(9, errorStateLength);
    
    tmpNominal.head(nominalStateLength) = fullNominalState;
    tmpNominal.segment(nominalStateLength, NOMINAL_POSE_STATE_SIZE) = fullNominalState.head(NOMINAL_POSE_STATE_SIZE);
    fullNominalState = tmpNominal;
    
    newState.q = fullNominalState.head(4);
    newState.p = fullNominalState.segment(4, 3);
    newState.v = fullNominalState.segment(7, 3);
    
    slidingWindow.push_back(newState);
    
    Jpi.block<3,3>(0, 0) = Matrix3d::Identity(3, 3);
    Jpi.block<3,3>(3, 3) = Matrix3d::Identity(3, 3);
    Jpi.block<3,3>(6, 6) = Matrix3d::Identity(3, 3);
    tmpCovariance.block(0, 0, errorStateLength, errorStateLength) = fullErrorCovariance;
    tmpCovariance.block(errorStateLength, 0, 9, errorStateLength) = Jpi * fullErrorCovariance;
    tmpCovariance.block(0, errorStateLength, errorStateLength, 9) = fullErrorCovariance * Jpi.transpose();
    tmpCovariance.block<ERROR_POSE_STATE_SIZE, ERROR_POSE_STATE_SIZE>(errorStateLength, errorStateLength) =
        Jpi * fullErrorCovariance * Jpi.transpose();
    
    fullErrorCovariance = tmpCovariance;
}