LRESULT CALLBACK PluginProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (message == BB_BROADCAST)
    {
        if (!_stricmp("@ShrinkMemory", (char*)(lParam)))
            SetProcessWorkingSetSize(hProcess, (SIZE_T)-1, (SIZE_T)-1);
        return 0;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}