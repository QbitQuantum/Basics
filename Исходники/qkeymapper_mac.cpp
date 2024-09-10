static int qt_mac_get_key(int modif, const QChar &key, int virtualKey)
{
#ifdef DEBUG_KEY_BINDINGS
    qDebug("**Mapping key: %d (0x%04x) - %d (0x%04x)", key.unicode(), key.unicode(), virtualKey, virtualKey);
#endif

    if (key == kClearCharCode && virtualKey == 0x47)
        return Qt::Key_Clear;

    if (key.isDigit()) {
#ifdef DEBUG_KEY_BINDINGS
            qDebug("%d: got key: %d", __LINE__, key.digitValue());
#endif
        return key.digitValue() + Qt::Key_0;
    }

    if (key.isLetter()) {
#ifdef DEBUG_KEY_BINDINGS
        qDebug("%d: got key: %d", __LINE__, (key.toUpper().unicode() - 'A'));
#endif
        return (key.toUpper().unicode() - 'A') + Qt::Key_A;
    }
    if (key.isSymbol()) {
#ifdef DEBUG_KEY_BINDINGS
        qDebug("%d: got key: %d", __LINE__, (key.unicode()));
#endif
        return key.unicode();
    }

    for (int i = 0; qt_mac_keyboard_symbols[i].qt_code; i++) {
        if (qt_mac_keyboard_symbols[i].mac_code == key) {
            /* To work like Qt for X11 we issue Backtab when Shift + Tab are pressed */
            if (qt_mac_keyboard_symbols[i].qt_code == Qt::Key_Tab && (modif & Qt::ShiftModifier)) {
#ifdef DEBUG_KEY_BINDINGS
                qDebug("%d: got key: Qt::Key_Backtab", __LINE__);
#endif
                return Qt::Key_Backtab;
            }

#ifdef DEBUG_KEY_BINDINGS
            qDebug("%d: got key: %s", __LINE__, qt_mac_keyboard_symbols[i].desc);
#endif
            return qt_mac_keyboard_symbols[i].qt_code;
        }
    }

    //last ditch try to match the scan code
    for (int i = 0; qt_mac_keyvkey_symbols[i].qt_code; i++) {
        if (qt_mac_keyvkey_symbols[i].mac_code == virtualKey) {
#ifdef DEBUG_KEY_BINDINGS
            qDebug("%d: got key: %s", __LINE__, qt_mac_keyvkey_symbols[i].desc);
#endif
            return qt_mac_keyvkey_symbols[i].qt_code;
        }
    }

    // check if they belong to key codes in private unicode range
    if (key >= 0xf700 && key <= 0xf747) {
        if (key >= 0xf704 && key <= 0xf726) {
            return Qt::Key_F1 + (key.unicode() - 0xf704) ;
        }
        for (int i = 0; qt_mac_private_unicode[i].qt_code; i++) {
            if (qt_mac_private_unicode[i].mac_code == key) {
                return qt_mac_private_unicode[i].qt_code;
            }
        }

    }

    //oh well
#ifdef DEBUG_KEY_BINDINGS
    qDebug("Unknown case.. %s:%d %d[%d] %d", __FILE__, __LINE__, key.unicode(), key.toLatin1(), virtualKey);
#endif
    return Qt::Key_unknown;
}