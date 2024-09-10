bool	Win32Explorer::generateClickEvent(short int buttonID)
{
    //     mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MOVE|MOUSEEVENTF_LEFTDOWN,x,y,0,0);
    switch (buttonID)
    {
    case LeftClick:
        mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
        mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
        break;
    case MiddleClick:
        mouse_event(MOUSEEVENTF_MIDDLEDOWN,0,0,0,0);
        mouse_event(MOUSEEVENTF_MIDDLEUP,0,0,0,0);
        break;
    case RightClick:
        mouse_event(MOUSEEVENTF_RIGHTDOWN,0,0,0,0);
        mouse_event(MOUSEEVENTF_RIGHTUP,0,0,0,0);
        break;
    case LeftDbClick:
        mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
        mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
        mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
        mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
        break;
    default:
        break;
    }
    return (true);
}