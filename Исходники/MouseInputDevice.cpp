void MouseInputDevice::updateCurrValues_()
{
	// Check if mouse is installed
	CURSORINFO info;
	info.cbSize = sizeof(CURSORINFO);
	if (!GetCursorInfo(&info))
		return;

	updatePos_();
	updateButtons_();
	currAKeys_[MAB_WHEEL] = 0;

	if (Engine::getInstance()->GetIsEditorMode() && Input::GetTriggered(0, "ToggleMouse") == 1.0f)
	{
		Lock(false);
		Visible(true);
	}

	updateLock_();
	updateVisiblility_();
}