bool
InfoBoxContentSpeedGround::HandleKey(const InfoBoxKeyCodes keycode)
{
    if (!is_simulator())
        return false;
    if (!CommonInterface::Basic().gps.simulator)
        return false;

    const auto fixed_step = (fixed)Units::ToSysSpeed(fixed(10));
    const auto a5 = Angle::Degrees(5);

    switch (keycode) {
    case ibkUp:
        device_blackboard->SetSpeed(
            CommonInterface::Basic().ground_speed + fixed_step);
        return true;

    case ibkDown:
        device_blackboard->SetSpeed(fdim(CommonInterface::Basic().ground_speed,
                                         fixed_step));
        return true;

    case ibkLeft:
        device_blackboard->SetTrack(CommonInterface::Basic().track - a5);
        return true;

    case ibkRight:
        device_blackboard->SetTrack(CommonInterface::Basic().track + a5);
        return true;
    }

    return false;
}