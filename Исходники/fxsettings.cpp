bool Settings::RegistHotkey(QWidget *window,
		QChar keyValue,
		Qt::KeyboardModifiers keyMod)
{
#if WIN32
	WId w_handle = window ? window->winId(): 0;
		int modifiy = QtModToWinMod(keyMod);
		return RegisterHotKey(w_handle, hotkey_id, modifiy, VkKeyScan
				(keyValue.toAscii()));
#else //liunx or mac os are not implement...
		Q_UNUSED(window);
		Q_UNUSED(keyValue);
		Q_UNUSED(keyMod);
		return false;
#endif
		
}