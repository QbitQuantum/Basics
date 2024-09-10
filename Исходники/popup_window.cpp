bool PopupWindow::onProcessMessage(Message* msg)
{
    switch (msg->type()) {

    case kCloseMessage:
        stopFilteringMessages();
        break;

    case kMouseLeaveMessage:
        if (m_hotRegion.isEmpty() && !isMoveable())
            closeWindow(NULL);
        break;

    case kKeyDownMessage:
        if (m_filtering) {
            KeyMessage* keymsg = static_cast<KeyMessage*>(msg);
            KeyScancode scancode = keymsg->scancode();

            if (scancode == kKeyEsc ||
                    scancode == kKeyEnter ||
                    scancode == kKeyEnterPad) {
                closeWindow(NULL);
            }

            // If we are filtering messages we don't propagate key-events
            // to other widgets. As we're a popup window and we're
            // filtering messages, the user shouldn't be able to start
            // other actions pressing keyboard shortcuts.
            return false;
        }
        break;

    case kMouseDownMessage:
        if (m_filtering) {
            gfx::Point mousePos = static_cast<MouseMessage*>(msg)->position();

            switch (m_clickBehavior) {

            // If the user click outside the window, we have to close
            // the tooltip window.
            case kCloseOnClickInOtherWindow: {
                Widget* picked = pick(mousePos);
                if (!picked || picked->getRoot() != this) {
                    closeWindow(NULL);
                }
                break;
            }

            case kCloseOnClickOutsideHotRegion:
                if (!m_hotRegion.contains(mousePos)) {
                    closeWindow(NULL);
                }
                break;
            }
        }
        break;

    case kMouseMoveMessage:
        if (!isMoveable() &&
                !m_hotRegion.isEmpty() &&
                getManager()->getCapture() == NULL) {
            gfx::Point mousePos = static_cast<MouseMessage*>(msg)->position();

            // If the mouse is outside the hot-region we have to close the
            // window.
            if (!m_hotRegion.contains(mousePos))
                closeWindow(NULL);
        }
        break;

    }

    return Window::onProcessMessage(msg);
}