void CWaitCommandsAI::SquadWait::UpdateText()
{
	static char buf[64];
	SNPRINTF(buf, sizeof(buf), "%i/%i", (int)waitUnits.size(), squadCount);
	stateText = buf;
}