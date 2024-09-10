ErrorWindow::~ErrorWindow(void)
{
	Project* project = fParent->GetProject();
	if (project == NULL)
		return;

	BRect frame(Frame());
	BNode node(project->GetPath().GetFullPath());
	node.WriteAttr("error_frame", B_RECT_TYPE, 0, &frame, sizeof(frame));
}