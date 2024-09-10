void WindowsTaskBar::alert(bool on)
{
	if (on) {
		FLASHWINFO fi = {0};
		fi.cbSize  = sizeof(fi);
		fi.dwFlags = FLASHW_TRAY;
		fi.hwnd    = window()->winId();
		fi.uCount  = 1;
		FlashWindowEx(&fi);
	}
}