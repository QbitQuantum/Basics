void StatusScreen::init()
{
	who = 0;

	//Init background image
	background.init();
	background.setHandle("statScreen");
	background.setTranslate(310,180,0);
	background.setScale(0.8f, 0.6f, 0.0f);

	//Init Portraits
	Drawable temp;
	temp.init();
	for(int i = 0; i<3; i++)
	{
		temp.setTranslate(310,210,0);
		temp.setScale(0.4f, 0.4f, 0.0f);
		portraits.push_back(temp);
	}
	portraits[0].setHandle("gremFullPic");
	portraits[1].setHandle("lennFullPic");
	portraits[2].setHandle("lazFullPic");

	SCDATA scdata[] = {
		{100.0f, 580.0f, 555,50,595,200,L"Back"},
		{100.0f, 180.0f, 155,50,195,200,L"Grem"},
		{100.0f, 280.0f, 255,50,295,200,L"Lenn"},
		{100.0f, 380.0f, 355,50,395,200,L"Lazarus"},
	};

	Drawable tempCommands;
	RECT tempR;
	 
	for(int i = 0; i<sizeof(scdata)/sizeof(scdata[0]); i++){
		tempCommands.setTranslate(scdata[i].x,scdata[i].y,0.0f);
		tempR.left = scdata[i].l;
		tempR.right = scdata[i].r;
		tempR.top = scdata[i].t;
		tempR.bottom = scdata[i].b;
		tempCommands.init();
		tempCommands.setText(scdata[i].name);
		tempCommands.setRect(tempR);
		buttons.push_back(tempCommands);
	}
}