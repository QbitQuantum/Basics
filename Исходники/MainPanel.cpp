void MainPanel::Draw()
{
	FrameTimer loadTimer;
	glClear(GL_COLOR_BUFFER_BIT);
	
	engine.Draw();
	
	if(isDragging)
	{
		if(canDrag)
		{
			const Color &dragColor = *GameData::Colors().Get("drag select");
			LineShader::Draw(dragSource, Point(dragSource.X(), dragPoint.Y()), .8f, dragColor);
			LineShader::Draw(Point(dragSource.X(), dragPoint.Y()), dragPoint, .8f, dragColor);
			LineShader::Draw(dragPoint, Point(dragPoint.X(), dragSource.Y()), .8f, dragColor);
			LineShader::Draw(Point(dragPoint.X(), dragSource.Y()), dragSource, .8f, dragColor);
		}
		else
			isDragging = false;
	}
	
	if(Preferences::Has("Show CPU / GPU load"))
	{
		string loadString = to_string(lround(load * 100.)) + "% GPU";
		const Color &color = *GameData::Colors().Get("medium");
		FontSet::Get(14).Draw(loadString, Point(10., Screen::Height() * -.5 + 5.), color);
	
		loadSum += loadTimer.Time();
		if(++loadCount == 60)
		{
			load = loadSum;
			loadSum = 0.;
			loadCount = 0;
		}
	}
}