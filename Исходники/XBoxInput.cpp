void XInput::vibrate( int index, float leftVal, float rightVal, float fTime )
{
    if(!is_connected(index)) return;
    if(fTime <= 0.0f) return;
    leftVal = bx::fclamp(leftVal, 0.0f, 1.0f);
    rightVal = bx::fclamp(rightVal, 0.0f, 1.0f);
#ifdef HAVOK_COMPILE
    XINPUT_VIBRATION tmpVibration;
    tmpVibration.wLeftMotorSpeed = (WORD)(leftVal * VIBRATION_MAX);
    tmpVibration.wRightMotorSpeed = (WORD)(rightVal * VIBRATION_MAX);
    m_vibrateTime[index] = fTime;
    XInputSetState(index, &tmpVibration);
#endif
}