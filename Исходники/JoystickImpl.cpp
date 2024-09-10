        bool JoystickImpl::isConnected(Uint8 id)
        {
            JOYINFO joyInfo;

            return joyGetPos(id, &joyInfo) == JOYERR_NOERROR;
        }