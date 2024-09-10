void DisplayOff()
{   /* Switch the screen off now */
    HDC hdc;
    VIDEO_POWER_MANAGEMENT vpm;

    hdc = GetDC(NULL);
    vpm.PowerState = VideoPowerOff;
    vpm.Length = sizeof(VIDEO_POWER_MANAGEMENT);

    ExtEscape(hdc,
              SETPOWERMANAGEMENT,
              sizeof(VIDEO_POWER_MANAGEMENT),
              (LPCSTR)&vpm,
              0,
              NULL);

    return;
}