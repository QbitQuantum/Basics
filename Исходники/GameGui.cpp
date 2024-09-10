void GameGui::CloseWindowCallback(Gwen::Controls::Base* window)
{
	CloseWindow(*(Gwen::Controls::WindowControl*)window);
}