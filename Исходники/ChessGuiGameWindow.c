/** Quits the game and returns to the main menu. This event is prompted when the menu button is clicked. */
void onMainMenuClick(GuiButton* button)
{
	// Create new window and set it as active
	GuiWindow* mainMenu = createMainMenu();
	if (NULL == mainMenu)
		g_guiError = true; // Raise flag if an error occured, main loop will respond accordingly

	setActiveWindow(mainMenu); // Switch to main menu window
}