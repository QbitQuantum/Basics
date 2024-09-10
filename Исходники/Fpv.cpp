void OculusWorldDemoApp::OnIdle()
{

    double curtime = pPlatform->GetAppTime();
    float  dt      = float(curtime - LastUpdate);
    LastUpdate     = curtime;


    if (LoadingState == LoadingState_DoLoad)
    {
        LoadingState = LoadingState_Finished;
        return;
    }

    // If one of Stereo setting adjustment keys is pressed, adjust related state.
    if (pAdjustFunc)
    {
        (this->*pAdjustFunc)(dt * AdjustDirection * (ShiftDown ? 5.0f : 1.0f));
    }



    // Rotate and position View Camera, using YawPitchRoll in BodyFrame coordinates.
    //
    Matrix4f rollPitchYaw = Matrix4f::RotationY(0) * Matrix4f::RotationX(0) * Matrix4f::RotationZ(0); // YAW PITCH ROLL
	const Vector3f	UpVector(0.0f, 1.0f, 0.0f);
	const Vector3f	ForwardVector(0.0f, 0.0f, -1.0f);
    Vector3f up      = rollPitchYaw.Transform(UpVector);
    Vector3f forward = rollPitchYaw.Transform(ForwardVector);


    // Minimal head modeling; should be moved as an option to SensorFusion.
    float headBaseToEyeHeight     = 0.15f;  // Vertical height of eye from base of head
    float headBaseToEyeProtrusion = 0.09f;  // Distance forward of eye from base of head

    Vector3f eyeCenterInHeadFrame(0.0f, headBaseToEyeHeight, -headBaseToEyeProtrusion);
    Vector3f shiftedEyePos = rollPitchYaw.Transform(eyeCenterInHeadFrame);
    shiftedEyePos.y -= eyeCenterInHeadFrame.y; // Bring the head back down to original height
    View = Matrix4f::LookAtRH(shiftedEyePos, shiftedEyePos + forward, up);

    //  Transformation without head modeling.
    // View = Matrix4f::LookAtRH(EyePos, EyePos + forward, up);

    // This is an alternative to LookAtRH:
    // Here we transpose the rotation matrix to get its inverse.
    //  View = (Matrix4f::RotationY(EyeYaw) * Matrix4f::RotationX(EyePitch) *
    //                                        Matrix4f::RotationZ(EyeRoll)).Transposed() *
    //         Matrix4f::Translation(-EyePos);




	//case Stereo_LeftDouble_Multipass:
	Render(SConfig.GetEyeRenderParams(StereoEye_Left));
	Render(SConfig.GetEyeRenderParams(StereoEye_Right));

    pRender->Present();
    // Force GPU to flush the scene, resulting in the lowest possible latency.
    pRender->ForceFlushGPU();
}