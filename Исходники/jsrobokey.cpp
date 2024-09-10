BOOL SendText( LPCTSTR lpctszText )
{
    std::vector<INPUT> EventQueue;

    TCHAR Buff[120 * sizeof(TCHAR)] = {0};
    GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_ILANGUAGE, Buff, sizeof(Buff));
    HKL hKeyboardLayout = ::LoadKeyboardLayout( Buff, KLF_ACTIVATE );

    const size_t Len = wcslen( lpctszText );
    for( size_t Index = 0; Index < Len; ++Index )
    {
        INPUT Event = { 0 };

        const SHORT Vk = VkKeyScanEx(lpctszText[Index], hKeyboardLayout);
        const UINT VKey = ::MapVirtualKey( LOBYTE( Vk ), 0 );

        if( HIBYTE( Vk ) == 1 ) // Check if shift key needs to be pressed for this key
        {
            // Press shift key
            ::ZeroMemory( &Event, sizeof( Event ));
            Event.type = INPUT_KEYBOARD;
            Event.ki.dwFlags = KEYEVENTF_SCANCODE;
            Event.ki.wScan = ::MapVirtualKey( VK_LSHIFT, 0 );
            EventQueue.push_back( Event );
        }

        // Keydown
        ::ZeroMemory( &Event, sizeof( Event ));
        Event.type = INPUT_KEYBOARD;
        Event.ki.dwFlags = KEYEVENTF_SCANCODE;
        Event.ki.wScan = VKey;
        EventQueue.push_back( Event );

        // Keyup
        ::ZeroMemory( &Event, sizeof( Event ));
        Event.type = INPUT_KEYBOARD;
        Event.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
        Event.ki.wScan = VKey;
        EventQueue.push_back( Event );

        if( HIBYTE( Vk ) == 1 )// Release if previously pressed
        {
            // Release shift key
            ::ZeroMemory( &Event, sizeof( Event ));
            Event.type = INPUT_KEYBOARD;
            Event.ki.dwFlags = KEYEVENTF_SCANCODE| KEYEVENTF_KEYUP;
            Event.ki.wScan = ::MapVirtualKey( VK_LSHIFT, 0 );
            EventQueue.push_back( Event );
        }
    }// End for

    if( hKeyboardLayout )
    {
        UnloadKeyboardLayout( hKeyboardLayout );
    }

    return static_cast<BOOL>(::SendInput( static_cast<UINT>(EventQueue.size()), &EventQueue[0], sizeof( INPUT )));
}