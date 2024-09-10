	void GUIEdge::draw(CDC& context) const
	{
		context.CreatePen(PS_SOLID, 1, visible ? RGB(0, 0, 0) : RGB(223, 223, 223));
		context.MoveTo(side1->getX(), side1->getY());
		context.LineTo(side2->getX(), side2->getY());
		if (blocked)
			context.Ellipse(getX() - 16, getY() - 16, getX() + 16, getY() + 16);
		drawLabel(context, 0, 16);
		context.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	}