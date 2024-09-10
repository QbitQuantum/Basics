void ScrollPanel::Draw(const Point& screenPos)
{
	Panel::Draw(screenPos);

	Graphics * g = ui::Engine::Ref().g;

	//Vertical scroll bar
	if(maxOffset.Y>0 && InnerSize.Y>0)
	{
		float scrollHeight = float(Size.Y)*(float(Size.Y)/float(InnerSize.Y));
		float scrollPos = 0;
		if(-ViewportPosition.Y>0)
		{
			scrollPos = float(Size.Y-scrollHeight)*(float(offsetY)/float(maxOffset.Y));
		}

		g->fillrect(screenPos.X+(Size.X-scrollBarWidth), screenPos.Y, scrollBarWidth, Size.Y, 125, 125, 125, 100);
		g->fillrect(screenPos.X+(Size.X-scrollBarWidth), screenPos.Y+scrollPos, scrollBarWidth, scrollHeight, 255, 255, 255, 255);
	}
}