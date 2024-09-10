void QOpenKODEWindow::processKeyEvents(const KDEvent *event)
{
#ifdef KD_ATX_keyboard
    //KD_KEY_PRESS_ATX 1
    QEvent::Type keyPressed = QEvent::KeyRelease;
    if (event->data.keyboardInputKey.flags)
        keyPressed = QEvent::KeyPress;
//KD_KEY_LOCATION_LEFT_ATX // don't care for now
//KD_KEY_LOCATION_RIGHT_ATX
//KD_KEY_LOCATION_NUMPAD_ATX
    Qt::KeyboardModifiers mod = Qt::NoModifier;
    int openkodeMods = event->data.keyboardInputKey.flags;
    if (openkodeMods & KD_KEY_MODIFIER_SHIFT_ATX)
        mod |= Qt::ShiftModifier;
    if (openkodeMods & KD_KEY_MODIFIER_CTRL_ATX)
        mod |= Qt::ControlModifier;
    if (openkodeMods & KD_KEY_MODIFIER_ALT_ATX)
        mod |= Qt::AltModifier;
    if (openkodeMods & KD_KEY_MODIFIER_META_ATX)
        mod |= Qt::MetaModifier;

    Qt::Key qtKey;
    QChar keyText;
    int key = event->data.keyboardInputKey.keycode;
    if (key >= 0x20 && key <= 0x0ff){ // 8 bit printable Latin1
        qtKey = Qt::Key(key);
        keyText = QChar(event->data.keyboardInputKeyChar.character);
        if (!(mod & Qt::ShiftModifier))
            keyText = keyText.toLower();
    } else {
        qtKey = keyTranslator(key);
    }
    QWindowSystemInterface::handleKeyEvent(0,event->timestamp,keyPressed,qtKey,mod,keyText);
#endif
}