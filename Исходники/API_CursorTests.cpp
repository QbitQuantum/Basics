void CursorTests::TestSetConsoleCursorPosition()
{
    // Get initial buffer value for boundaries
    CONSOLE_SCREEN_BUFFER_INFOEX sbiInitial = { 0 };
    sbiInitial.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
    BOOL bResult = GetConsoleScreenBufferInfoEx(Common::_hConsole, &sbiInitial);
    VERIFY_WIN32_BOOL_SUCCEEDED(bResult, L"Retrieve the initial buffer information to calculate the boundaries for testing.");

    // Try several cases
    TestSetConsoleCursorPositionImpl(0, 0, TRUE); // Top left corner of buffer
    TestSetConsoleCursorPositionImpl(sbiInitial.dwSize.X - 1, sbiInitial.dwSize.Y - 1, TRUE); // Bottom right corner of buffer
    TestSetConsoleCursorPositionImpl(sbiInitial.dwSize.X, sbiInitial.dwSize.Y, FALSE); // 1 beyond bottom right corner (the size is 1 larger than the array indicies)
    TestSetConsoleCursorPositionImpl(MAXWORD, MAXWORD, FALSE); // Max values
}