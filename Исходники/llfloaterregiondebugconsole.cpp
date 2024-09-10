BOOL LLFloaterRegionDebugConsole::postBuild()
{
	LLLineEditor* input = getChild<LLLineEditor>("region_debug_console_input");
	input->setEnableLineHistory(true);
	input->setCommitCallback(boost::bind(&LLFloaterRegionDebugConsole::onInput, this, _1, _2));
	input->setFocus(true);
	input->setCommitOnFocusLost(false);

	mOutput = getChild<LLTextEditor>("region_debug_console_output");

	std::string url = gAgent.getRegion()->getCapability("SimConsoleAsync");
	if (url.empty())
	{
		// Fall back to see if the old API is supported.
		url = gAgent.getRegion()->getCapability("SimConsole");
		if (url.empty())
		{
			mOutput->appendText(
				CONSOLE_NOT_SUPPORTED + PROMPT,
				false, false);
			return TRUE;
		}
	}

	mOutput->appendText("> ", false, false);
	return TRUE;
}