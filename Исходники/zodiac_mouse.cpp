void OSystem_PalmZodiac::undraw_mouse() {
	if (!_mouseDrawn)
		return;

	int h = _mouseOldState.h;

	// no need to do clipping here, since draw_mouse() did that already
	if (_overlayVisible) {
		uint16 *dst;
		uint16 *bak = (uint16 *)_mouseBackupP;

		TwGfxLockSurface(_overlayP, (void **)&dst);
		dst += _mouseOldState.y * _screenWidth + _mouseOldState.x;

		do {
			MemMove(dst, bak, _mouseOldState.w * 2);
			dst += _screenWidth;
			bak += _mouseOldState.w;
		} while (--h);

		TwGfxUnlockSurface(_overlayP, true);

	} else {
		byte *dst = _offScreenP + _mouseOldState.y * _screenWidth + _mouseOldState.x;
		byte *bak = _mouseBackupP;

		do {
			MemMove(dst, bak, _mouseOldState.w);
			dst += _screenWidth;
			bak +=  _mouseOldState.w;
		} while (--h);
	}

	_mouseDrawn = false;
}