void
X360Controller::setMotorSpeeds (uint32_t gamePadIndex, float left, float right)
{
    if (gamePadIndex < MAX_GAME_PAD_COUNT)
    {
        XINPUT_VIBRATION vibration;
        memset( &vibration, 0, sizeof(XINPUT_VIBRATION) );
        vibration.wLeftMotorSpeed = WORD(left * 65535.0f); // use any value between 0-65535 here
        vibration.wRightMotorSpeed = WORD(right * 65535.0f); // use any value between 0-65535 here
        XInputSetState(gamePadIndex, &vibration );
    }
    else
    {
        LOG("Invalid X360 gamepadIndex " << gamePadIndex);
    }
}