void DestroyKeyboard() {
	XkbSetDetectableAutoRepeat(g.Disp, 0, NULL);

    // Enable cursor and revert grab cursor if mouse
    if (g.cfg.PadDef[0].Type == PSE_PAD_TYPE_MOUSE ||
        g.cfg.PadDef[1].Type == PSE_PAD_TYPE_MOUSE) {
        grabCursor(g.Disp, window, 0);
        showCursor(g.Disp, window, 1);
    } else if (g.cfg.HideCursor) {
        showCursor(g.Disp, window, 1);
    }

    // Enable screensaver if it was disabled - this could be in different place
    if (resumeScrSaver) {
        char buf[64];
        printf("Resuming Window ID 0x%x to activate screensaver.\n", window);
        snprintf(buf, 64, "xdg-screensaver resume 0x%x", window);
        FILE *phandle = popen(buf, "r");
        pclose(phandle);
    }
}