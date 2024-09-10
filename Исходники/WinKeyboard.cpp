/**
 * Set current state of a keyboard modifier.
 *
 * @param   idModifier        Modifier to set (VK_CAPITAL, VK_SCROLL or VK_NUMLOCK)
 * @param   fState            State to set
 */
static void winSetModifierState(int idModifier, bool fState)
{
    AssertReturnVoid((idModifier == VK_CAPITAL) || (idModifier == VK_SCROLL) || (idModifier == VK_NUMLOCK));

    /* If the modifier is already in desired state, just do nothing. Otherwise, toggle it. */
    if (winGetModifierState(idModifier) != fState)
    {
        /* Simulate KeyUp+KeyDown keystroke */
        keybd_event(idModifier, 0, KEYEVENTF_EXTENDEDKEY, 0);
        keybd_event(idModifier, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);

        /* Process posted above keyboard events immediately: */
        MSG msg;
        while (::PeekMessage(&msg, NULL, WM_KEYFIRST, WM_KEYLAST, PM_REMOVE))
            ::DispatchMessage(&msg);

        LogRel2(("HID LEDs sync: setting %s state to %s (0x%X).\n",
                 VBOX_CONTROL_TO_STR_NAME(idModifier), VBOX_BOOL_TO_STR_STATE(fState), MapVirtualKey(idModifier, MAPVK_VK_TO_VSC)));
    }
    else
    {
        LogRel2(("HID LEDs sync: setting %s state: skipped: state is already %s (0x%X).\n",
                 VBOX_CONTROL_TO_STR_NAME(idModifier), VBOX_BOOL_TO_STR_STATE(fState), MapVirtualKey(idModifier, MAPVK_VK_TO_VSC)));
    }
}