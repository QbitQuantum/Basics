void HMDState::GetTimewarpMatrices(ovrEyeType eyeId, ovrPosef renderPose,
                                   ovrMatrix4f twmOut[2])
{
    // Get timewarp start/end timing
    double timewarpStartEnd[2];
    getTimewarpStartEnd(eyeId, timewarpStartEnd);

    ovrTrackingState startState = PredictedTrackingState(timewarpStartEnd[0]);
    ovrTrackingState endState   = PredictedTrackingState(timewarpStartEnd[1]);

    Quatf quatFromEye = Quatf(renderPose.Orientation);
    quatFromEye.Invert();   // because we need the view matrix, not the camera matrix

    Matrix4f timewarpStart, timewarpEnd;
    CalculateOrientationTimewarpMatrix(
        quatFromEye, startState.HeadPose.ThePose.Orientation, timewarpStart);
    CalculateOrientationTimewarpMatrix(
        quatFromEye, endState.HeadPose.ThePose.Orientation, timewarpEnd);

    twmOut[0] = timewarpStart;
    twmOut[1] = timewarpEnd;
}