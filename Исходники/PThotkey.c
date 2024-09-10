static VOID
sRemoveHotKeys (HWND hwnd)
{
	UnregisterHotKey (hwnd, kPurgePassphraseCache);
	UnregisterHotKey (hwnd, kEncryptCurrentWindow);
	UnregisterHotKey (hwnd, kSignCurrentWindow);
	UnregisterHotKey (hwnd, kEncryptSignCurrentWindow);
	UnregisterHotKey (hwnd, kDecryptCurrentWindow);
///	UnregisterHotKey (hwnd, kUnmountPGPDisks);
}