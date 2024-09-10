void FrameTimeManager::GetTimewarpMatrices(ovrHmd hmd, ovrEyeType eyeId,
                                           ovrPosef renderPose, ovrMatrix4f twmOut[2])
{
    if (!hmd)
    {
        return;
    }

    double timewarpStartEnd[2] = { 0.0, 0.0 };    
    GetTimewarpPredictions(eyeId, timewarpStartEnd);
      
    ovrSensorState startState = ovrHmd_GetSensorState(hmd, timewarpStartEnd[0]);
    ovrSensorState endState   = ovrHmd_GetSensorState(hmd, timewarpStartEnd[1]);

    if (TimewarpIMUTimeSeconds == 0.0)
        TimewarpIMUTimeSeconds = startState.Recorded.TimeInSeconds;

    Quatf quatFromStart = startState.Predicted.Pose.Orientation;
    Quatf quatFromEnd   = endState.Predicted.Pose.Orientation;
    Quatf quatFromEye   = renderPose.Orientation; //EyeRenderPoses[eyeId].Orientation;
    quatFromEye.Invert();
    
    Quatf timewarpStartQuat = quatFromEye * quatFromStart;
    Quatf timewarpEndQuat   = quatFromEye * quatFromEnd;

    Matrix4f timewarpStart(timewarpStartQuat);
    Matrix4f timewarpEnd(timewarpEndQuat);
    

    // The real-world orientations have:                                  X=right, Y=up,   Z=backwards.
    // The vectors inside the mesh are in NDC to keep the shader simple: X=right, Y=down, Z=forwards.
    // So we need to perform a similarity transform on this delta matrix.
    // The verbose code would look like this:
    /*
    Matrix4f matBasisChange;
    matBasisChange.SetIdentity();
    matBasisChange.M[0][0] =  1.0f;
    matBasisChange.M[1][1] = -1.0f;
    matBasisChange.M[2][2] = -1.0f;
    Matrix4f matBasisChangeInv = matBasisChange.Inverted();
    matRenderFromNow = matBasisChangeInv * matRenderFromNow * matBasisChange;
    */
    // ...but of course all the above is a constant transform and much more easily done.
    // We flip the signs of the Y&Z row, then flip the signs of the Y&Z column,
    // and of course most of the flips cancel:
    // +++                        +--                     +--
    // +++ -> flip Y&Z columns -> +-- -> flip Y&Z rows -> -++
    // +++                        +--                     -++
    timewarpStart.M[0][1] = -timewarpStart.M[0][1];
    timewarpStart.M[0][2] = -timewarpStart.M[0][2];
    timewarpStart.M[1][0] = -timewarpStart.M[1][0];
    timewarpStart.M[2][0] = -timewarpStart.M[2][0];

    timewarpEnd  .M[0][1] = -timewarpEnd  .M[0][1];
    timewarpEnd  .M[0][2] = -timewarpEnd  .M[0][2];
    timewarpEnd  .M[1][0] = -timewarpEnd  .M[1][0];
    timewarpEnd  .M[2][0] = -timewarpEnd  .M[2][0];

    twmOut[0] = timewarpStart;
    twmOut[1] = timewarpEnd;
}