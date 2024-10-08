  void RawInputKeyboard::onRawInput( const RAWKEYBOARD& input )
  {
    // Thanks to Stefan Reinalter for the special case correction advice:
    // http://molecularmusings.wordpress.com/2011/09/05/properly-handling-keyboard-input/

    VirtualKeyCode virtualKey = input.VKey;
    UINT scanCode = input.MakeCode;
    UINT flags = input.Flags;

    if ( virtualKey == 0xFF )
      return;

    if ( virtualKey == VK_SHIFT )
      virtualKey = MapVirtualKeyW( scanCode, MAPVK_VSC_TO_VK_EX );
    else if ( virtualKey == VK_NUMLOCK )
      scanCode = ( MapVirtualKeyW( virtualKey, MAPVK_VK_TO_VSC ) | 0x100 );

    const bool isE0 = ( ( flags & RI_KEY_E0 ) != 0 );
    const bool isE1 = ( ( flags & RI_KEY_E1 ) != 0 );

    if ( isE1 )
    {
      if ( virtualKey == VK_PAUSE )
        scanCode = 0x45;
      else
        scanCode = MapVirtualKeyW( virtualKey, MAPVK_VK_TO_VSC );
    }

    switch ( virtualKey )
    {
      case VK_CONTROL:
        virtualKey = ( isE0 ? Key_RightControl : Key_LeftControl );
      break;
      case VK_MENU:
        virtualKey = ( isE0 ? Key_RightAlt : Key_LeftAlt );
      break;
      case VK_RETURN:
        if ( isE0 )
          virtualKey = Key_NumpadEnter;
      break;
      case VK_INSERT:
        if ( !isE0 )
          virtualKey = VK_NUMPAD0;
      break;
      case VK_DELETE:
        if ( !isE0 )
          virtualKey = VK_DECIMAL;
      break;
      case VK_HOME:
        if ( !isE0 )
          virtualKey = VK_NUMPAD7;
      break;
      case VK_END:
        if ( !isE0 )
          virtualKey = VK_NUMPAD1;
      break;
      case VK_PRIOR:
        if ( !isE0 )
          virtualKey = VK_NUMPAD9;
      break;
      case VK_NEXT:
        if ( !isE0 )
          virtualKey = VK_NUMPAD3;
      break;
      case VK_LEFT:
        if ( !isE0 )
          virtualKey = VK_NUMPAD4;
      break;
      case VK_RIGHT:
        if ( !isE0 )
          virtualKey = VK_NUMPAD6;
      break;
      case VK_UP:
        if ( !isE0 )
          virtualKey = VK_NUMPAD8;
      break;
      case VK_DOWN:
        if ( !isE0 )
          virtualKey = VK_NUMPAD2;
      break;
      case VK_CLEAR:
        if ( !isE0 )
          virtualKey = VK_NUMPAD5;
      break;
    }

    if ( flags & RI_KEY_BREAK )
    {
      mPressedKeys.remove( virtualKey );
      for ( auto listener : mListeners )
        listener->onKeyReleased( this, virtualKey );
    }
    else
    {
      bool isPressed = false;
      for ( auto pressed : mPressedKeys )
        if ( pressed == virtualKey )
        {
          isPressed = true;
          break;
        }
      if ( isPressed )
      {
        for ( auto listener : mListeners )
          listener->onKeyRepeat( this, virtualKey );
      }
      else
      {
        mPressedKeys.push_back( virtualKey );
        for ( auto listener : mListeners )
          listener->onKeyPressed( this, virtualKey );
      }
    }

    /*if ( flags & RI_KEY_BREAK )
    {
      UINT key = (scanCode << 16) | (isE0 << 24);
      wchar_t buffer[512] = {};
      GetKeyNameTextW((LONG)key, buffer, 512);
      OutputDebugStringW( buffer );
    }*/
  }