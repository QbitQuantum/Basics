KeyID
CMSWindowsKeyState::getIDForKey(CKeyMap::KeyItem& item,
				KeyButton button, UINT virtualKey,
				PBYTE keyState, HKL hkl) const
{
	int n;
	KeyID id;
	if (m_is95Family) {
		// XXX -- how do we get characters not in Latin-1?
		WORD ascii;
		n  = ToAsciiEx(virtualKey, button, keyState, &ascii, 0, hkl);
		id = static_cast<KeyID>(ascii & 0xffu);
	}
	else {
		WCHAR unicode[2];
		n  = m_ToUnicodeEx(virtualKey, button, keyState,
								unicode, sizeof(unicode) / sizeof(unicode[0]),
								0, hkl);
		id = static_cast<KeyID>(unicode[0]);
	}
	switch (n) {
	case -1:
		return CKeyMap::getDeadKey(id);

	default:
	case 0:
		// unmapped
		return kKeyNone;

	case 1:
		return id;

	case 2:
		// left over dead key in buffer. this used to recurse,
		// but apparently this causes a stack overflow, so just
		// return no key instead.
		return kKeyNone;
	}
}