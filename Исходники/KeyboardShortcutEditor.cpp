        void KeyboardShortcutEditor::OnKeyUp(wxKeyEvent& event) {
            if (m_key == WXK_NONE) {
                const int key = event.GetKeyCode();
                switch (key) {
                    case WXK_SHIFT:
                    case WXK_ALT:
                    case WXK_CONTROL:
                        if (m_modifierKey1 == key)
                            m_modifierKey1 = WXK_NONE;
                        else if (m_modifierKey2 == key)
                            m_modifierKey2 = WXK_NONE;
                        else if (m_modifierKey3 == key)
                            m_modifierKey3 = WXK_NONE;
                        break;
#if defined __APPLE__
                    case WXK_RAW_CONTROL:
                        // not supported
                        break;
#endif
                    default:
                        break;
                }
                update();
            } else {
                KeyboardShortcutEvent shortcutEvent(m_modifierKey1, m_modifierKey2, m_modifierKey3, m_key);
                shortcutEvent.SetEventType(EVT_KEYBOARD_SHORTCUT_EVENT);
                shortcutEvent.SetEventObject(this);
                shortcutEvent.SetId(GetId());
                ProcessEvent(shortcutEvent);
            }
        }