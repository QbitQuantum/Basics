///@brief This function will detect a moderate tap on the Rift via the accelerometer.
///@return true if a tap was detected, false otherwise.
bool RiftAppSkeleton::CheckForTapOnHmd()
{
    const ovrTrackingState ts = ovrHmd_GetTrackingState(m_Hmd, ovr_GetTimeInSeconds());
    if (!(ts.StatusFlags & ovrStatus_OrientationTracked))
        return false;

    const OVR::Vector3f v(ts.RawSensorData.Accelerometer);
    // Arbitrary value and representing moderate tap on the side of the DK2 Rift.
    if (v.LengthSq() > 250.f)
    {
        // Limit tapping rate
        static double lastTapTime = 0.0;
        if (ovr_GetTimeInSeconds() - lastTapTime > 0.5)
        {
            lastTapTime = ovr_GetTimeInSeconds();
            DismissHealthAndSafetyWarning();
            ToggleShaderWorld();
            return true;
        }
    }
    return false;
}