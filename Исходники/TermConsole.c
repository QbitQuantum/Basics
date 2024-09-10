/*--------------------------------------------------------------------------*/
static unsigned char TerminalGetchar(void)
{
    INPUT_RECORD irBuffer;
    DWORD n = 0;
    unsigned char ch = 0;
    do
    {
        /* http://bugzilla.scilab.org/show_bug.cgi?id=1052 */
        if ( ismenu() == 1 )
        {
            return 0;
        }

        WaitForSingleObject(Win32InputStream, INFINITE);
        PeekConsoleInput (Win32InputStream, &irBuffer, 1, &n);

        switch (irBuffer.EventType)
        {
            case KEY_EVENT:
            {
                if (irBuffer.Event.KeyEvent.bKeyDown)
                {
                    if (irBuffer.Event.KeyEvent.dwControlKeyState)
                    {
                        if (isCTRLPressed(irBuffer.Event.KeyEvent.dwControlKeyState))
                        {
                            char c = actionControlKey();
                            if (c)
                            {
                                ReadConsoleInputW (Win32InputStream, &irBuffer, 1, &n);
                                return c;
                            }
                            else
                            {
                                if (irBuffer.Event.KeyEvent.uChar.AsciiChar != '\0')
                                {
                                    ReadConsoleInputW (Win32InputStream, &irBuffer, 1, &n);
                                    c = irBuffer.Event.KeyEvent.uChar.AsciiChar;
                                    if ( (c > 0) && !iscntrl(c) )
                                    {
                                        return c;
                                    }
                                }
                                else
                                {
                                    ReadConsoleInput (Win32InputStream, &irBuffer, 1, &n);
                                }
                            }
                            break;
                        }

                        if (isALTPressed(irBuffer.Event.KeyEvent.dwControlKeyState))
                        {
                            if (irBuffer.Event.KeyEvent.uChar.AsciiChar != '\0')
                            {
                                ReadConsole (Win32InputStream, &ch, 1, &n, NULL);
                                return ch;
                            }
                            else
                            {
                                DWORD stateKey = 0;
                                WORD vk = 0;

                                ReadConsoleInput (Win32InputStream, &irBuffer, 1, &n);

                                stateKey = irBuffer.Event.KeyEvent.dwControlKeyState;
                                vk = irBuffer.Event.KeyEvent.wVirtualKeyCode;

                                switch (vk)
                                {
                                    case VK_F4:
                                        ALTF4_Command();
                                        break;

                                    default:
                                        break;
                                }
                            }
                            break;
                        }
                    }

                    if (irBuffer.Event.KeyEvent.uChar.AsciiChar != '\0')
                    {
                        ReadConsole (Win32InputStream, &ch, 1, &n, NULL);

                        switch (ch)
                        {
                            case VK_TAB:
                                TermCompletion();
                                break;
                            case VK_BACK:
                                deletePreviousChar();
                                break;
                            default:
                            {
                                if ( !iscntrl(ch) || (ch == CR_1) || (ch == CR_2) )
                                {
                                    return ch;
                                }
                            }
                            break;
                        }
                    }
                    else
                    {
                        WORD vk = 0;
                        ReadConsoleInput (Win32InputStream, &irBuffer, 1, &n);
                        vk = irBuffer.Event.KeyEvent.wVirtualKeyCode;

                        switch (vk)
                        {
                            case VK_F1:
                            case VK_HELP:
                                F1_Command();
                                break;
                            case VK_F2:
                                F2_Command();
                                break;
                            case VK_LEFT:
                                moveBackSingleChar();
                                break;
                            case VK_RIGHT:
                                moveForwardSingleChar();
                                break;
                            case VK_UP:
                                moveBackHistory();
                                break;
                            case VK_DOWN:
                                moveForwardHistory();
                                break;
                            case VK_DELETE:
                                deleteCurrentChar();
                                break;
                            case VK_HOME:
                                moveBeginningLine();
                                break;
                            case VK_END:
                                moveEndLine();
                                break;
                            default:
                                break;
                        }
                    }
                }
                else
                {
                    ReadConsoleInput (Win32InputStream, &irBuffer, 1, &n);
                }
            }
            break;
            case MOUSE_EVENT:
            {
                /* Read mouse Input but not used */
                ReadConsoleInput (Win32InputStream, &irBuffer, 1, &n);
            }
            break;
            case WINDOW_BUFFER_SIZE_EVENT:
            {
                /* Read resize event Input */
                setColumnsSize(irBuffer.Event.WindowBufferSizeEvent.dwSize.X);
                setLinesSize(irBuffer.Event.WindowBufferSizeEvent.dwSize.Y);

                ReadConsoleInput (Win32InputStream, &irBuffer, 1, &n);
            }
            break;
            case MENU_EVENT:
            {
                ReadConsoleInput (Win32InputStream, &irBuffer, 1, &n);
            }
            break;
            case FOCUS_EVENT:
            {
                ReadConsoleInput (Win32InputStream, &irBuffer, 1, &n);
            }
            break;
            default:
            {
                /* Read Input but not used */
                ReadConsoleInput (Win32InputStream, &irBuffer, 1, &n);
            }
            break;
        }
    }
    while (TRUE);
}