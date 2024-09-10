void Audio3DTest::update(float elapsedTime)
{
    float time = (float)elapsedTime / 1000.0f;

    _gamepad->update(elapsedTime);

    Vector2 move;

    if (_moveFlags != 0)
    {
        // Forward motion
        if (_moveFlags & MOVE_FORWARD)
        {
            move.y = 1;
        }
        else if (_moveFlags & MOVE_BACKWARD)
        {
            move.y = -1;
        }
        // Strafing
        if (_moveFlags & MOVE_LEFT)
        {
            move.x = 1;
        }
        else if (_moveFlags & MOVE_RIGHT)
        {
            move.x = -1;
        }
        move.normalize();

        // Up and down
        if (_moveFlags & MOVE_UP)
        {
            _fpCamera.moveUp(time * UP_DOWN_SPEED);
        }
        else if (_moveFlags & MOVE_DOWN)
        {
            _fpCamera.moveDown(time * UP_DOWN_SPEED);
        }
    }
    else if (_gamepad->isJoystickActive(0))
    {
        _gamepad->getJoystickAxisValues(0, &move);
        move.x = -move.x;
    }

    if (!move.isZero())
    {
        move.scale(time * MOVE_SPEED);
        _fpCamera.moveForward(move.y);
        _fpCamera.moveLeft(move.x);
    }

    if (!_buttonPressed && _gamepad->getButtonState(BUTTON_A) == Gamepad::BUTTON_PRESSED)
    {
        addSound("footsteps.wav");
    }
    _buttonPressed = _gamepad->getButtonState(BUTTON_A) == Gamepad::BUTTON_PRESSED;
}