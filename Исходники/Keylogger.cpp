void KeyLogger::clean()
{
    UnhookWindowsHookEx(instance().hHook_);
}