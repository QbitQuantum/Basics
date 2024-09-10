static void k213_GetErrorStatus (gpibioPtr dev)
{
    int error, s;
    char e_msg[256], *s_msg, rsp[256];

    gpibio_Out (dev, "E?");
    gpibio_In (dev, rsp);

    Scan (rsp, "%s>E%i", &error);
    switch (error) {
        case 1: MessagePopup ("Keithley 213 Message", "ERROR: Unrecognized command"); break;
        case 2: MessagePopup ("Keithley 213 Message", "ERROR: Invalid command parameter"); break;
        case 3: MessagePopup ("Keithley 213 Message", "ERROR: Command conflict"); break;
        case 4: MessagePopup ("Keithley 213 Message", "ERROR: Calibration switch not closed"); break;
        case 5:
            gpibio_Out (dev, "S?");
            gpibio_In (dev, rsp);
            Scan (rsp, "%s>S%i", &s);
            Fmt (e_msg, "ERROR: Non-volatile RAM error, system defaults or calibration may be lost.");
            if (s) s_msg = "User programmed defaults are still valid";
                else s_msg = "Factory defaults are in use, user programmed defaults were lost";
            Fmt (e_msg, "%s[a]<\n%s", s_msg);
            MessagePopup ("Keithley 213 Message", e_msg);
            break;
    }
}