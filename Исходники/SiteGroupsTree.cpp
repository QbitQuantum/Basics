BOOL CSiteGroupsTree::PreTranslateMessage(MSG *msg)
{
    if (msg->message == WM_KEYDOWN) {
		// When an item is being edited make sure the edit control
		// receives certain important key strokes
		if (GetEditControl() && (msg->wParam == VK_RETURN || msg->wParam == VK_DELETE || msg->wParam == VK_ESCAPE || GetKeyState(VK_CONTROL))) {
			::TranslateMessage(msg);
			::DispatchMessage(msg);
			return TRUE; // Do NOT process further
		}
    }

    return CTreeCtrl::PreTranslateMessage(msg);
}