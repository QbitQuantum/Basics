static void win32_setup_keymap(void)
{
        default_keymap = GetKeyboardLayout(0);
        us_keymap = LoadKeyboardLayout("00000409", KLF_ACTIVATE|KLF_REPLACELANG|KLF_NOTELLSHELL);
        ActivateKeyboardLayout(default_keymap,0);
}