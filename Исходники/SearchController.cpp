void SearchController::OpenSave(int saveID, int saveDate)
{
	if(activePreview)
		delete activePreview;
	Graphics * g = ui::Engine::Ref().g;
	g->fillrect(XRES/3, WINDOWH-20, XRES/3, 20, 0, 0, 0, 150); //dim the "Page X of Y" a little to make the CopyTextButton more noticeable
	activePreview = new PreviewController(saveID, saveDate, instantOpen, new OpenCallback(this));
	ui::Engine::Ref().ShowWindow(activePreview->GetView());
}