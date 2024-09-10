void MainContentComponent::paint (Graphics& g)
{
	ColourGradient gradient(Colours::beige, 0, getHeight() / 2, Colours::aqua, 1280, getHeight() / 2, true);
	//ColourGradient gradient(Colours::beige, 0, getHeight() / 2, Colours::aqua, 1280, getHeight() / 2, true);
	//ColourGradient gradient(Colour::fromRGBA(50, 50, 50, 50), getWidth() / 2, getHeight() / 2, Colours::aqua, 0, 0, true);
	Colour kleuren[] = { Colours::red, Colours::azure, Colours::olive, Colours::khaki, Colours::hotpink, Colours::mistyrose, Colours::cyan, Colours::indianred, Colours::mediumspringgreen, Colours::gold };

	for (int tel3 = 0; tel3 < 10; tel3++)
	{
		if (touchpoint[tel3].getvisible() == true){
			float at = touchpoint[tel3].getX() / getWidth();
			if (at < 0)
			{
				at = 0;
			}
			else if (at > 1)
			{
				at = 1;
			}
			//touchpoint[tel3].setfreq(200 + getHeight() - touchpoint[tel3].getY());
			//touchpoint[tel3].setpan(touchpoint[tel3].getX() / getWidth());
			gradient.addColour(at, kleuren[tel3]);
		}

	}

	unsigned int thisframetime = GetTickCount();

	if ((thisframetime - lastframetime) > 0){
		fps = 1000 / (thisframetime - lastframetime);
	}
	else{
		fps = 9999;
		OutputDebugString("2 Frames tegelijk?");
	}


	gradient.multiplyOpacity(0.2);

	g.setGradientFill(gradient);
    g.fillAll ();

	

	g.drawImageAt(img, getWidth() / 2 - img.getWidth() / 2, getHeight() / 2 - img.getHeight() / 2);

    g.setFont (Font (16.0f));
    g.setColour (Colours::white);
	g.fillRect(getWidth() - 100, getHeight() - 20, 100, 20);
	g.setColour(Colours::black);

	g.drawText("freq: " + to_string((int)touchpoint[0].getfreq()) + " " + to_string(fps) + " fps", getLocalBounds(), Justification::bottomRight, true);
	
	for (float note = 0; note < 50; note++)
	{
		float x = 196 * powf(2, note / 12);
		
		if ((int)note % 12 == 0){
			g.drawHorizontalLine(200 + getHeight() - x, 0, 20);
		}


		g.drawHorizontalLine(200 + getHeight() - x, 0, 10);
	}

	for (size_t i = 0; i < 10; i++)
	{
		if (touchpoint[i].getvisible()){
			g.drawEllipse(touchpoint[i].getX() - 50, touchpoint[i].getY() - 50, 100, 100, 1);
		}
	}
	lastframetime = thisframetime;
}