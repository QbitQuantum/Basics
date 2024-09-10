bool TopWindow::Key(dword key, int count)
{
	if(Ctrl::Key(key, count))
		return true;
	if(IsChild()) return false;
	if(key == K_DOWN || key == K_RIGHT || key == K_TAB) {
		Ctrl *ctrl = GetFocusChildDeep();
		if(ctrl && IterateFocusForward(ctrl, this))
			return true;
		ctrl = GetFirstChild();
		if(ctrl) {
			if(ctrl->SetWantFocus()) return true;
			return IterateFocusForward(ctrl, this);
		}
	}
	if(key == K_UP || key == K_LEFT || key == K_SHIFT_TAB) {
		Ctrl *ctrl = GetFocusChildDeep();
		if(ctrl && IterateFocusBackward(ctrl, this))
			return true;
		ctrl = GetLastChild();
		if(ctrl) {
			if(ctrl->SetWantFocus()) return true;
			return IterateFocusBackward(ctrl, this);
		}
	}
	return false;
}