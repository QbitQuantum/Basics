void OculusInterface::oculusDisplayWarning()
{
  // Health and Safety Warning display state.
  ovrHSWDisplayState hswDisplayState;
  ovrHmd_GetHSWDisplayState(m_hmd, &hswDisplayState);
  if (hswDisplayState.Displayed)
  {
  // Dismiss the warning if the user pressed the appropriate key or if the user
  // is tapping the side of the HMD.
  // If the user has requested to dismiss the warning via keyboard or controller input...
  if (m_warningOff)
    ovrHmd_DismissHSWDisplay(m_hmd);
  else
  {
  // Detect a moderate tap on the side of the HMD.
  ovrTrackingState ts = ovrHmd_GetTrackingState(m_hmd, ovr_GetTimeInSeconds());
  if (ts.StatusFlags & ovrStatus_OrientationTracked)
  {
  const OVR::Vector3f v(ts.RawSensorData.Accelerometer.x,
  ts.RawSensorData.Accelerometer.y,
  ts.RawSensorData.Accelerometer.z);
  // Arbitrary value and representing moderate tap on the side of the DK2 Rift.
  if (v.LengthSq() > 250.f)
  ovrHmd_DismissHSWDisplay(m_hmd);
  }
  }
}
}