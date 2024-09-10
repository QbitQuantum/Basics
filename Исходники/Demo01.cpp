bool ImageWindow::OnEvent(const TBWidgetEvent &ev)
{
	if (ev.type == EVENT_TYPE_CLICK && ev.target->GetID() == TBIDC("remove"))
	{
		TBWidget *image = ev.target->GetParent();
		image->GetParent()->RemoveChild(image);
		delete image;
		return true;
	}
	return DemoWindow::OnEvent(ev);
}