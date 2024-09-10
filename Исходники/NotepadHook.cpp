void NotepadHook::Uninstall()
{
    Autosaver::GetInstance()->Stop();
    UnhookWindowsHookEx(_keyboardHookHandle);
}