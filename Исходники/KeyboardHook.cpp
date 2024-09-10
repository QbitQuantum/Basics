LRESULT CALLBACK globalKeyboardHookProcedure(int nCode, WPARAM wParam, LPARAM lParam)
{

    if (nCode >= HC_ACTION) {

        QWidget *focusWidget = QApplication::focusWidget();

        // qobject_cast return NULL when the cast fail.
        bool widgetIsFocusable = qobject_cast<QLineEdit *>(focusWidget) || qobject_cast<QComboBox *>(focusWidget);

        if (widgetIsFocusable) {
            KBDLLHOOKSTRUCT *keyData = reinterpret_cast<KBDLLHOOKSTRUCT *>(lParam);

            // SYSTEM events are not 'trapped' by Jamtaba
            if (wParam == WM_SYSKEYDOWN || wParam == WM_SYSKEYUP)
                return CallNextHookEx(NULL, nCode, wParam, lParam);

            bool usingIME = ImmGetOpenStatus(ImmGetContext(GetActiveWindow())); // detect if japanese input (IME) is activated - issue #472
            if (usingIME) {
                // we need detect if user is pressing VK_RETURN 2 times: 1 time to finish IME notation window and the second time to send the message in ninjam chat.
                bool hookingReturnKey = keyboardHook::lastImeKeyUpWasReturn && keyData->vkCode == VK_RETURN;
                if (wParam == WM_KEYUP) // we need "remember" if the last key was VK_RETURN
                    keyboardHook::lastImeKeyUpWasReturn = !hookingReturnKey && keyData->vkCode == VK_RETURN;

                if (!hookingReturnKey)
                    return CallNextHookEx(NULL, nCode, wParam, lParam);
            }

            QKeyEvent *ev = nullptr;
            QKeyEvent::Type eventType = (wParam == WM_KEYDOWN) ? QKeyEvent::KeyPress : QKeyEvent::KeyRelease;

            bool controlIsPressed = GetKeyState(VK_CONTROL) & 0x8000;
            bool shiftIsPressed = GetKeyState(VK_SHIFT) & 0x8000;

            // A-Z letters and numbers
            bool typingLetters = keyData->vkCode >= Qt::Key_A && keyData->vkCode <= Qt::Key_Z;
            bool typingNumbers = keyData->vkCode >= Qt::Key_0 && keyData->vkCode <= Qt::Key_9;
            bool typingInNumPad = keyData->vkCode >= VK_NUMPAD0 && keyData->vkCode <= VK_NUMPAD9;
            bool typingQuestionMark = keyData->vkCode == Qt::Key_questiondown || keyData->vkCode == Qt::Key_Question;
            if (typingLetters || typingNumbers || typingInNumPad || typingQuestionMark) {
                QString keyText = keyboardHook::vkCodeToText(keyData->vkCode, keyData->scanCode);
                Qt::KeyboardModifiers modifiers;
                if (controlIsPressed)
                    modifiers |= Qt::ControlModifier;
                if (shiftIsPressed) {
                    modifiers |= Qt::ShiftModifier;
                }
                ev = new QKeyEvent(eventType, keyData->vkCode, modifiers, keyText);
            }
            else { // other/special keys
                switch (keyData->vkCode) {
                case VK_BACK:
                    ev = new QKeyEvent(eventType, Qt::Key_Backspace, Qt::NoModifier);
                    break;
                case VK_DELETE:
                    ev = new QKeyEvent(eventType, Qt::Key_Delete, Qt::NoModifier);
                    break;
                case VK_SPACE:
                    ev = new QKeyEvent(eventType, Qt::Key_Space, Qt::NoModifier, " ");
                    break;
                case VK_RETURN:
                    ev = new QKeyEvent(eventType, Qt::Key_Return, Qt::NoModifier);
                    break;
                case VK_LEFT:
                    ev = new QKeyEvent(eventType, Qt::Key_Left, QApplication::queryKeyboardModifiers());
                    break;
                case VK_RIGHT:
                    ev = new QKeyEvent(eventType, Qt::Key_Right, QApplication::queryKeyboardModifiers());
                    break;
                case VK_END:
                    ev = new QKeyEvent(eventType, Qt::Key_End, QApplication::queryKeyboardModifiers());
                    break;
                case VK_HOME:
                    ev = new QKeyEvent(eventType, Qt::Key_Home, QApplication::queryKeyboardModifiers());
                    break;
                }
            }

            if (ev) {
                QApplication::postEvent(focusWidget, ev);
                return 1; // if we have a keyboard event Jamtaba will consume the event and don't forward to the Vst host.
            }
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam); // Forward the event to VST host
}