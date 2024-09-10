void MouseEventTool::RemoveHook()
{
    if (hhook) {
        UnhookWindowsHookEx(hhook);
    }
}