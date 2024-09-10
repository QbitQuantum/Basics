/** ***************************************************************************/
bool HotkeyManager::unregisterHotkey(const QString &hk) {
    return unregisterHotkey(QKeySequence(hk));
}