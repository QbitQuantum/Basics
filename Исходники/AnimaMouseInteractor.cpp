bool AnimaMouseInteractor::Remove()
{
	if (_installed == false)
		return false;

	// Rimuovo questo interactor dalla lista di interactor installati
	auto interactor = _installedInteractors.find(_windowId);
	if (interactor != _installedInteractors.end())
		_installedInteractors.erase(interactor);

	UnhookWindowsHook(WH_CALLWNDPROC, WindowsProcCallback);
	UnhookWindowsHook(WH_GETMESSAGE, MessageProcCallback);

	_windowId = 0;
	_installed = false;
	return true;
}