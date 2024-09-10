void UGlobalHotkeys::RegisterHotkey(const UKeySequence& keySeq, size_t id) {
    if (keySeq.Size() == 0) {
        throw UException("Empty hotkeys");
    }
    if (Registered.find(id) != Registered.end()) {
        UnregisterHotkey(id);
    }
    #if defined(Q_OS_WIN)
    size_t winMod = 0;
    size_t key = VK_F2;

    for (size_t i = 0; i != keySeq.Size(); i++) {
        if (keySeq[i] == Qt::Key_Control) {
            winMod |= MOD_CONTROL;
        } else if (keySeq[i] == Qt::Key_Alt) {
            winMod |= MOD_ALT;
        } else if (keySeq[i] == Qt::Key_Shift) {
            winMod |= MOD_SHIFT;
        } else if (keySeq[i] == Qt::Key_Meta) {
            winMod |= MOD_WIN;
        } else {
            key = QtKeyToWin(keySeq[i]);
        }
    }

    if (!RegisterHotKey((HWND)winId(), id, winMod, key)) {
        qDebug() << "Error activating hotkey!";
    } else {
        Registered.insert(id);
    }
    #elif defined(Q_OS_LINUX)
    regLinuxHotkey(keySeq, id);
    #endif
}