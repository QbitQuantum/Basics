void Inn::init()
{
	bg.setHandle("inn");
	bg.setTranslate(300.0f,180.0f,0.0f);
	bg.setScale(.8f,.6f,0.0f);

	box.setHandle("blueBox");
	box.setTranslate(160.0f,460.0f,0.0f);
	box.setScale(.7f,.7f,0.0f);
	
	RData uiData[] = {
		{225, 0, 250, 200, 170, 465},	// back

	};
	for(int i = 0; i < INN_BUTTONS; i++) {
		Drawable temp;
		RECT rect;
		// NewGame
		rect.top = uiData[i].t; 
		rect.left = uiData[i].l;
		rect.bottom =  uiData[i].b; 
		rect.right =  uiData[i].r;
		temp.setTranslate( uiData[i].x, uiData[i].y, 0);
		temp.setRect(rect);
		buttons[i]= temp;
		buttons[i].setHandle("opButtons");
		//buttons[i].setTranslate(300,180,0);
		buttons[i].setScale(.4f,.8f,0.0f);
	}
}