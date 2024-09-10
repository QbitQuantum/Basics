	void redraw(IDrawContext& context) override
	{
		context.drawIcon(context.widgetRect, icon_);
	}