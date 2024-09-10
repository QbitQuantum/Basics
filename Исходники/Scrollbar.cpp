void ScrollBar::processMessage(Message& msg) {
	switch (msg.message) {
		case wmReflect + WM_HSCROLL :
		case wmReflect + WM_VSCROLL : {
			SCROLLINFO info;
			info.cbSize = sizeof(info);
			info.fMask = SIF_ALL;
			verify(GetScrollInfo(handle(), SB_CTL, &info));
			int pos = info.nPos;
			bool tracking = false;
			switch (LOWORD(msg.wparam)) {
				case SB_THUMBPOSITION : pos = info.nTrackPos; break;
				case SB_THUMBTRACK    : pos = info.nTrackPos; tracking = true; break;
				case SB_LINEUP        : pos = pos - lineSize(); break;
				case SB_LINEDOWN      : pos = pos + lineSize(); break;
				case SB_PAGEUP        : pos = pos - static_cast<int>(info.nPage); break;
				case SB_PAGEDOWN      : pos = pos + static_cast<int>(info.nPage); break;
				case SB_TOP           : pos = 0; break;
				case SB_BOTTOM        : pos = info.nMax - info.nPage + 1; break;
			}
			pos = min(pos, info.nMax - static_cast<int>(info.nPage) + 1);
			pos = max(pos, info.nMin);
			const int oldPos = info.nPos;
			if (pos != oldPos) {
				info.fMask = SIF_POS;
				info.nPos = pos;
				SetScrollInfo(handle(), SB_CTL, &info, TRUE);
			}
			if (pos != oldPos || LOWORD(msg.wparam) == SB_THUMBPOSITION) {
				Scroll event(*this, info.nPos, pos, tracking);
				onScroll()(event);
			}
		} break;
		case wmReflect + WM_CTLCOLORSCROLLBAR : {
			HBRUSH brush = this->brush();
			if (brush) {
				Graphics graphics((HDC)msg.wparam);
				graphics.brushOrigin(brushOrigin());
				msg.result = (LRESULT)brush;
			} else {
				Control::processMessage(msg);
			}
		} break;
		case WM_MOUSEWHEEL : {
			SCROLLINFO info;
			info.cbSize = sizeof(info);
			info.fMask = SIF_POS | SIF_RANGE | SIF_PAGE;
			verify(GetScrollInfo(handle(), SB_CTL, &info));
			int delta = GET_WHEEL_DELTA_WPARAM(msg.wparam);
			delta = (delta / WHEEL_DELTA) * lineSize();
			int pos = info.nPos - delta;
			pos = min(pos, info.nMax - static_cast<int>(info.nPage) + 1);
			pos = max(pos, info.nMin);
			value(pos);
			Control::processMessage(msg);
		} break;
		default : {
			Control::processMessage(msg);
		} break;
	}
}