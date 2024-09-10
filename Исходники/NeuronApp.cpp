void mouseClick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		Vec2 mousePos((float)x, (float)y);
		for (int i = 0; i < rectangles.size(); ++i)
		{
			if (rectangles[i]->Intersects(mousePos))
			{
				nnet->ApplyChanges(changes[i]);
				GenerateMutations();
				return;
			}
		}
		float* thingToChange = 0;

		if (colourRect.Intersects(mousePos))
			thingToChange = &colourWeight;
		else if (sizeRect.Intersects(mousePos))
			thingToChange = &sizeWeight;
		else if (distanceRect.Intersects(mousePos))
			thingToChange = &distanceWeight;
		else if (areaRect.Intersects(mousePos))
			thingToChange = &areaWeight;

		if (thingToChange)
		{	
			if (y > 700)
				*thingToChange -= 0.1f;
			else
				*thingToChange += 0.1f;
		}
	}
}