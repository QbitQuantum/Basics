bool GlobalHotkey::registerHotkey(const int hk)
{
	// Unregister other hotkeys before registering new ones
    unregisterHotkey();

	//TODO make this capable of multiple key, so that the old one does not have to be unregistered whil registereing another
	if (_impl->registerNativeHotkey(hk)) {
		_hotkey = hk;
        emit hotKeyChanged(hk);
		return true;
	}
	return false;
}