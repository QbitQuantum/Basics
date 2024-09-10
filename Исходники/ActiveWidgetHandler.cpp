void ActiveWidgetHandler::Input_InputModeChanged(Input::InputMode mode)
{
	if (mode != Input::IM_GUI && mLastMode == Input::IM_GUI) {
		//save the current active widget
		CEGUI::Window* window = mGuiManager.getMainSheet()->getActiveChild();
		if (window) {
			mLastActiveWindow = window;
			mLastActiveWindowDestructionStartedConnection = window->subscribeEvent(CEGUI::Window::EventDestructionStarted, CEGUI::Event::Subscriber(&ActiveWidgetHandler::lastActiveWindowDestructionStarted, this));
			window->deactivate();
			//deactivate all parents
			while ((window = window->getParent())) {
				window->deactivate();
			}
		} else {
			mLastActiveWindow = nullptr;
		}
		mLastMode = mode;
	} else if (mode == Input::IM_GUI) {
		if (mLastActiveWindow) {
			//restore the previously active widget
			try {
				mLastActiveWindow->activate();
			} catch (...)
			{
				S_LOG_WARNING("Error when trying to restore previously captured window.");
			}
			mLastActiveWindow = 0;
			mLastActiveWindowDestructionStartedConnection->disconnect();
		}
		mLastMode = mode;
	}
}