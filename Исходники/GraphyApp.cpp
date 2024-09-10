/* ========================================================
	mouseDrag(MouseEvent)
======================================================== */
void GraphyApp::mouseDrag(MouseEvent me)
{
	Vec2i pos = me.getPos();
	float deltaX = 0.0f;
	float deltaY = 0.0f;

	if (prevMouseSet)
	{
		deltaX = pos.x - prevMouseX;
		deltaY = pos.y - prevMouseY;
	}

	bool setPrev = true;

	if (panel.isDragging())
	{
		if (!panel.updatePos(ci::Vec2f(deltaX, deltaY)))
		{
			setPrev = false;
		}
	}
	else if (panel2.isDragging())
	{
		if (!panel2.updatePos(ci::Vec2f(deltaX, deltaY)))
		{
			setPrev = false;
		}
	}

	if (!setPrev)
	{
		prevMouseSet = false;
		int posX = (prevMouseX >= 0 ? (int)(prevMouseX + 0.5f) : (int)(prevMouseX - 0.5f));
		int posY = (prevMouseY >= 0 ? (int)(prevMouseY + 0.5f) : (int)(prevMouseY - 0.5f));
		SetPhysicalCursorPos(posX + ci::app::getWindowPos().x, posY + ci::app::getWindowPos().y);
	}
	else
	{
		prevMouseSet = true;
		prevMouseX = pos.x;
		prevMouseY = pos.y;
	}
}