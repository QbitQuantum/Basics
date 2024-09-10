void AttachToRLLog::readLatest()
{
    if (consoleConnected) {
        CONSOLE_SCREEN_BUFFER_INFO console_buffer_info = {0};
        if (GetConsoleScreenBufferInfo(hConsole, &console_buffer_info))
        {
            COORD screenBufferSize = console_buffer_info.dwSize;
            COORD curserLoc = console_buffer_info.dwCursorPosition;

            // special case to clear console once curser reaches max screen buffer size
            if (curserLoc.Y == screenBufferSize.Y - 1) {
                COORD topLeft  = { 0, 10 };
                DWORD written;
                FillConsoleOutputCharacterA(
                        hConsole, ' ', screenBufferSize.X * screenBufferSize.Y, topLeft, &written
                    );
                    FillConsoleOutputAttribute(
                        hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
                        screenBufferSize.X * screenBufferSize.Y, topLeft, &written
                    );
                    SetConsoleCursorPosition(hConsole, topLeft);
                    curserLoc =  topLeft;
                    linesRead = 9;
            }

            // begin actually reading lines
            int readToLine = curserLoc.Y;
            int readFromLine = linesRead;
            int linesToReadNow = readToLine - readFromLine;
            if (linesToReadNow > 0) {
                CHAR_INFO buffer[screenBufferSize.X * linesToReadNow];
                COORD buffer_size  = { screenBufferSize.X, linesToReadNow};
                COORD buffer_index = { 0, 0 };
                SMALL_RECT read_region = { 0, readFromLine, screenBufferSize.X - 1, readToLine};

                if (!ReadConsoleOutputA(hConsole, buffer, buffer_size, buffer_index, &read_region)) {
                    std::cout << "Error reading console output " << GetLastError() << std::endl;
                }
                // iterate lines
                for (int i = 0; i < linesToReadNow; i++) {
                    std::string line = "";
                    // iterate characters in line
                    for (int j = 0; j < screenBufferSize.X - 1; j++) {
                        line+= buffer[i * screenBufferSize.X + j].Char.AsciiChar;
                    }
                    //std::cout << line << std::endl;
                    emit newLineFound(line);
                }

            linesRead = readToLine;
            }


        } else {
            std::wcout << L"Could not get ScreenBufferInfo, last error: " << GetLastError() << std::endl;
        }
    }
}