// Hook window-key for prevent a window being disabled when window-key pressed.
// To use window-key, save key-state with SetKeyboardState().
static LRESULT CALLBACK KeyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode == HC_ACTION && systemKeyDisabled)
    {
        KBDLLHOOKSTRUCT *pkbhs = (KBDLLHOOKSTRUCT *)lParam;
        if (pkbhs->vkCode == VK_LWIN || pkbhs->vkCode == VK_RWIN)
        {
            static BYTE keyState[256];
            // To use window-key as regular key, update keyState.
            if (wParam == WM_KEYDOWN)
            {
                GetKeyboardState(keyState);
                keyState[pkbhs->vkCode] = 0x80;
                SetKeyboardState(keyState);
            }
            else if (wParam == WM_KEYUP)
            {
                GetKeyboardState(keyState);
                keyState[pkbhs->vkCode] = 0x00;
                SetKeyboardState(keyState);
            }
            return 1;
        }
    }
    return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}