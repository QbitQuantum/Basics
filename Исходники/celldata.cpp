void ATOM_CellData::onRButtonUp (ATOM_WidgetRButtonUpEvent *event)
{
	ATOM_STACK_TRACE(ATOM_CellData::onRButtonUp);

	if (getRenderer()->getCapture() == this)
	{
		setBorderMode (ATOM_Widget::Raise);
		releaseCapture ();

		if (isMouseHover ())
		{
			ATOM_Widget *parent = getParent ();
			if (parent)
			{
				parent->queueEvent (ATOM_NEW(ATOM_CellRightClickEvent, getId(), 0, 0), ATOM_APP);
			}
		}
	}
}