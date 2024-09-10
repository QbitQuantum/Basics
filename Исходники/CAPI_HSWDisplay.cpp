bool HSWDisplay::TickState(ovrHSWDisplayState *hswDisplayState)
{
    bool newlyDisplayed = false;
    const double currentTime = ovr_GetTimeInSeconds();

    // See if we need to be currently displayed. By design we automatically display but don't automatically dismiss.
    if (Displayed)
    {
        if (DismissRequested) // If dismiss was previously requested, see if it can be executed.
            Dismiss();

        if (Displayed) // If not already dismissed above...
        {
            // We currently have the debug behavior that we permit dismiss very soon after launch.
            #if defined(OVR_BUILD_DEBUG)
                if(currentTime >= (StartTime + 2))
                {
                    DismissibleTime = StartTime;
                    //Dismiss();
                }
            #endif
        }

        if (Displayed) // If not already dismissed above...
        {
            const ovrTrackingState ts = ((OVR::CAPI::HMDState*)HMD->Handle)->PredictedTrackingState(currentTime);

            if (ts.StatusFlags & ovrStatus_OrientationTracked) // If the Accelerometer data is valid...
            {
				const OVR::Vector3f v(ts.HeadPose.LinearAcceleration.x, ts.HeadPose.LinearAcceleration.y, ts.HeadPose.LinearAcceleration.z);

                const float minTapMagnitude = 350.0f; // Empirically determined by some testing.

                if (v.LengthSq() > minTapMagnitude)
                    Dismiss(); // This will do nothing if the display is not present.
            }
        }
    }
    else
    {
        if (Enabled && (currentTime >= (LastPollTime + HSWDISPLAY_POLL_INTERVAL)))
        {
            LastPollTime = currentTime;

            // We need to display if any of the following are true:
            //     - The application is just started in Event Mode while the HMD is mounted (warning display would be viewable) and this app was not spawned from a launcher.
            //     - The current user has never seen the display yet while the HMD is mounted (warning display would be viewable).
            //     - The HMD is newly mounted (or the warning display is otherwise newly viewable).
            //     - The warning display hasn't shown in 24 hours (need to verify this as a requirement).
            // Event Mode refers to when the app is being run in a public demo event such as a trade show.

            OVR::CAPI::HMDState* pHMDState = (OVR::CAPI::HMDState*)HMD->Handle;

            if(pHMDState)
            {
                const time_t lastDisplayedTime = HSWDisplay::GetCurrentProfileLastHSWTime();

                // We currently unilaterally set HMDMounted to true because we don't yet have the ability to detect this. To do: Implement this when possible.
                const bool previouslyMounted = HMDMounted;
                HMDMounted = true;
                HMDNewlyMounted = (!previouslyMounted && HMDMounted); // We set this back to false in the Display function or if the HMD is unmounted before then.

                if((lastDisplayedTime == HSWDisplayTimeNever) || HMDNewlyMounted)
                {
                    if(IsDisplayViewable()) // If the HMD is mounted and otherwise being viewed by the user...
                    {
                        Display();
                        newlyDisplayed = true;
                    }
                }
            }
        }
    }

    if(hswDisplayState)
        GetState(hswDisplayState);

    return newlyDisplayed;
}