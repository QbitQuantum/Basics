JNIEXPORT void JNICALL Java_org_cef_browser_CefBrowser_1N_N_1SendKeyEvent
  (JNIEnv *env, jobject obj, jobject key_event) {
  CefRefPtr<CefBrowser> browser = JNI_GET_BROWSER_OR_RETURN(env, obj);
  jclass cls = env->GetObjectClass(key_event);
  if (!cls)
    return;

  JNI_STATIC_DEFINE_INT(env, cls, KEY_PRESSED);
  JNI_STATIC_DEFINE_INT(env, cls, KEY_RELEASED);
  JNI_STATIC_DEFINE_INT(env, cls, KEY_TYPED);

  int event_type, modifiers;
  char key_char;
  if (!CallJNIMethodI_V(env, cls, key_event, "getID", &event_type) ||
      !CallJNIMethodC_V(env, cls, key_event, "getKeyChar", &key_char) ||
      !CallJNIMethodI_V(env, cls, key_event, "getModifiersEx", &modifiers)) {
    return;
  }

  CefKeyEvent cef_event;
  cef_event.modifiers = GetCefModifiers(env, cls, modifiers);

#if defined(OS_WIN)
  BYTE VkCode = LOBYTE(VkKeyScanA(key_char));
  UINT scanCode = MapVirtualKey(VkCode, MAPVK_VK_TO_VSC);
  cef_event.native_key_code = (scanCode << 16) |  // key scan code
                              1;  // key repeat count
#elif defined(OS_LINUX) || defined(OS_MACOSX)
  int key_code;
  if (!CallJNIMethodI_V(env, cls, key_event, "getKeyCode", &key_code)) {
    return;
  }

  JNI_STATIC_DEFINE_INT(env, cls, VK_BACK_SPACE);
  JNI_STATIC_DEFINE_INT(env, cls, VK_DELETE);
  JNI_STATIC_DEFINE_INT(env, cls, VK_DOWN);
  JNI_STATIC_DEFINE_INT(env, cls, VK_ENTER);
  JNI_STATIC_DEFINE_INT(env, cls, VK_ESCAPE);
  JNI_STATIC_DEFINE_INT(env, cls, VK_LEFT);
  JNI_STATIC_DEFINE_INT(env, cls, VK_RIGHT);
  JNI_STATIC_DEFINE_INT(env, cls, VK_TAB);
  JNI_STATIC_DEFINE_INT(env, cls, VK_UP);

#if defined(OS_LINUX)
  if (key_code == JNI_STATIC(VK_BACK_SPACE))
    cef_event.native_key_code = GDK_BackSpace;
  else if (key_code == JNI_STATIC(VK_DELETE))
    cef_event.native_key_code = GDK_Delete;
  else if (key_code == JNI_STATIC(VK_DOWN))
    cef_event.native_key_code = GDK_Down;
  else if (key_code == JNI_STATIC(VK_ENTER))
    cef_event.native_key_code = GDK_KEY_KP_Enter;
  else if (key_code == JNI_STATIC(VK_ESCAPE))
    cef_event.native_key_code = GDK_Escape;
  else if (key_code == JNI_STATIC(VK_LEFT))
    cef_event.native_key_code = GDK_Left;
  else if (key_code == JNI_STATIC(VK_RIGHT))
    cef_event.native_key_code = GDK_Right;
  else if (key_code == JNI_STATIC(VK_TAB))
    cef_event.native_key_code = GDK_Tab;
  else if (key_code == JNI_STATIC(VK_UP))
    cef_event.native_key_code = GDK_Up;
  else
    cef_event.native_key_code = key_char;
#elif defined(OS_MACOSX)
  if (key_code == JNI_STATIC(VK_BACK_SPACE)) {
    cef_event.native_key_code = kVK_Delete;
    cef_event.unmodified_character = kBackspaceCharCode;
  } else if (key_code == JNI_STATIC(VK_DELETE)) {
    cef_event.native_key_code = kVK_ForwardDelete;
    cef_event.unmodified_character = kDeleteCharCode;
  } else if (key_code == JNI_STATIC(VK_DOWN)) {
    cef_event.native_key_code = kVK_DownArrow;
    cef_event.unmodified_character = /* NSDownArrowFunctionKey */ 0xF701;
  } else if (key_code == JNI_STATIC(VK_ENTER)) {
    cef_event.native_key_code = kVK_Return;
    cef_event.unmodified_character = kReturnCharCode;
  } else if (key_code == JNI_STATIC(VK_ESCAPE)) {
    cef_event.native_key_code = kVK_Escape;
    cef_event.unmodified_character = kEscapeCharCode;
  } else if (key_code == JNI_STATIC(VK_LEFT)) {
    cef_event.native_key_code = kVK_LeftArrow;
    cef_event.unmodified_character = /* NSLeftArrowFunctionKey */ 0xF702;
  } else if (key_code == JNI_STATIC(VK_RIGHT)) {
    cef_event.native_key_code = kVK_RightArrow;
    cef_event.unmodified_character = /* NSRightArrowFunctionKey */ 0xF703;
  } else if (key_code == JNI_STATIC(VK_TAB)) {
    cef_event.native_key_code = kVK_Tab;
    cef_event.unmodified_character = kTabCharCode;
  } else if (key_code == JNI_STATIC(VK_UP)) {
    cef_event.native_key_code = kVK_UpArrow;
    cef_event.unmodified_character = /* NSUpArrowFunctionKey */ 0xF700;
  } else {
    cef_event.native_key_code = GetMacKeyCodeFromChar(key_char);
    if (cef_event.native_key_code == -1)
      return;
    
    cef_event.unmodified_character = key_char;
  }

  cef_event.character = cef_event.unmodified_character;

  // Fill in |character| according to flags.
  if (cef_event.modifiers & EVENTFLAG_SHIFT_DOWN) {
    if (key_char >= '0' && key_char <= '9') {
      cef_event.character = kShiftCharsForNumberKeys[key_char - '0'];
    } else if (key_char >= 'A' && key_char <= 'Z') {
      cef_event.character = 'A' + (key_char - 'A');
    } else {
      switch (cef_event.native_key_code) {
        case kVK_ANSI_Grave:
          cef_event.character = '~';
          break;
        case kVK_ANSI_Minus:
          cef_event.character = '_';
          break;
        case kVK_ANSI_Equal:
          cef_event.character = '+';
          break;
        case kVK_ANSI_LeftBracket:
          cef_event.character = '{';
          break;
        case kVK_ANSI_RightBracket:
          cef_event.character = '}';
          break;
        case kVK_ANSI_Backslash:
          cef_event.character = '|';
          break;
        case kVK_ANSI_Semicolon:
          cef_event.character = ':';
          break;
        case kVK_ANSI_Quote:
          cef_event.character = '\"';
          break;
        case kVK_ANSI_Comma:
          cef_event.character = '<';
          break;
        case kVK_ANSI_Period:
          cef_event.character = '>';
          break;
        case kVK_ANSI_Slash:
          cef_event.character = '?';
          break;
        default:
          break;
      }
    }
  }

  // Control characters.
  if (cef_event.modifiers & EVENTFLAG_CONTROL_DOWN) {
    if (key_char >= 'A' && key_char <= 'Z')
      cef_event.character = 1 + key_char - 'A';
    else if (cef_event.native_key_code == kVK_ANSI_LeftBracket)
      cef_event.character = 27;
    else if (cef_event.native_key_code == kVK_ANSI_Backslash)
      cef_event.character = 28;
    else if (cef_event.native_key_code == kVK_ANSI_RightBracket)
      cef_event.character = 29;
  }
#endif  // defined(OS_MACOSX)
#endif  // defined(OS_LINUX) || defined(OS_MACOSX)

  if (event_type == JNI_STATIC(KEY_PRESSED)) {
#if defined(OS_WIN)
    cef_event.windows_key_code = VkCode;
#endif
    cef_event.type = KEYEVENT_RAWKEYDOWN;
  } else if (event_type == JNI_STATIC(KEY_RELEASED)) {
#if defined(OS_WIN)
    cef_event.windows_key_code = VkCode;
    // bits 30 and 31 should always be 1 for WM_KEYUP
    cef_event.native_key_code |= 0xC0000000;
#endif
    cef_event.type = KEYEVENT_KEYUP;
  } else if (event_type == JNI_STATIC(KEY_TYPED)) {
#if defined(OS_WIN)
    cef_event.windows_key_code = key_char;
#endif
    cef_event.type = KEYEVENT_CHAR;
  } else {
    return;
  }

  browser->GetHost()->SendKeyEvent(cef_event);
}