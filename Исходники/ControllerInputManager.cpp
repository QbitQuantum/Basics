///////////////////////////////////////
///VIBRATION FUNCTION
///SET BOTH TO 0 TO STOP VIBRATION
///////////////////////////////////////
void ControllerInputManager::vibrate(int controllerNum, int leftVal, int rightVal)
{
	if (!controllerIsValid(controllerNum))
		return;

    // Create a Vibraton State
    XINPUT_VIBRATION Vibration;

    // Zeroise the Vibration
    ZeroMemory(&Vibration, sizeof(XINPUT_VIBRATION));

    // Set the Vibration Values
    Vibration.wLeftMotorSpeed = leftVal;
    Vibration.wRightMotorSpeed = rightVal;

    // Vibrate the controller
    XInputSetState(controllerNum, &Vibration);
}