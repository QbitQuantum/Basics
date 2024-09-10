bool NeuroAndSimEvaluationStandardGuiApplication::setupGui() {
	//Register command line argument descriptions to the PlugInManager to support
	//switching the GUI on and off 
	CommandLineArgument *guiArgument = 
			new CommandLineArgument(
				"enableGui", "gui", "",
				"Starts the application with graphical user interface.",
				0, 0,
				true);
	CommandLineArgument *noGuiArgument = 
			new CommandLineArgument(
				"disableGui", "nogui", "",
				"Starts the application without graphical user interface.",
				0, 0,
				true);

	if(noGuiArgument->getParameterValue()->get() != "") {
		mEnableGui = false;
	}
	if(guiArgument->getParameterValue()->get() != "") {
		mEnableGui = true;
	}

	if(mEnableGui) {
		mGuiMainWindow = new GuiMainWindow(mEnableControl, mEnableDebugging);
		connect(this, SIGNAL(showGui()), mGuiMainWindow, SLOT(showWindow()));
	}
	return true;
}