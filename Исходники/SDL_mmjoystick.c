/* Function to scan the system for joysticks.
 * This function should set SDL_numjoysticks to the number of available
 * joysticks.  Joystick 0 should be the system default joystick.
 * It should return 0, or -1 on an unrecoverable fatal error.
 */
int
SDL_SYS_JoystickInit(void)
{
    int i;
    int maxdevs;
    JOYINFOEX joyinfo;
    JOYCAPSA joycaps;
    MMRESULT result;

    /* Reset the joystick ID & name mapping tables */
    for (i = 0; i < MAX_JOYSTICKS; ++i) {
        SYS_JoystickID[i] = 0;
        SYS_JoystickName[i] = NULL;
    }

    /* Loop over all potential joystick devices */
    SDL_SYS_numjoysticks = 0;
    maxdevs = joyGetNumDevs();
    for (i = JOYSTICKID1; i < maxdevs && SDL_SYS_numjoysticks < MAX_JOYSTICKS; ++i) {

        joyinfo.dwSize = sizeof(joyinfo);
        joyinfo.dwFlags = JOY_RETURNALL;
        result = joyGetPosEx(i, &joyinfo);
        if (result == JOYERR_NOERROR) {
            result = joyGetDevCapsA(i, &joycaps, sizeof(joycaps));
            if (result == JOYERR_NOERROR) {
                SYS_JoystickID[SDL_SYS_numjoysticks] = i;
                SYS_Joystick[SDL_SYS_numjoysticks] = joycaps;
                SYS_JoystickName[SDL_SYS_numjoysticks] =
                    GetJoystickName(i, joycaps.szRegKey);
                SDL_SYS_numjoysticks++;
            }
        }
    }
    return (SDL_SYS_numjoysticks);
}