bool MkCheatMessage::ExcuteMsg(const MkStr& command, const MkArray<MkStr>& argument, MkStr& resultMsg) const
{
	MkStr cmd = command;
	cmd.ToLower();

	if ((cmd == L"q") && argument.Empty())
	{
		MK_DEV_PANEL.__QuitApplication();
		return true;
	}

	if ((cmd == L"cls") && argument.Empty())
	{
		MK_DEV_PANEL.ClearLogWindow();
		return true;
	}

	return false;
}