void GUI::MenuDraw()
{

	/////////////
	//WATERMARK//
	/////////////
	if(Cvars.misc_watermark==1)
	{
	gNeeded.DrawString2((HFont)6,55,5,255,255,255,255,L"h00k");
	}

	if (IsKeyPressed(VK_INSERT))
    {
		bActive = !bActive;
    }

	if (!bActive) return;


	int x = Cvars.menu_x;
	int y = Cvars.menu_y;
	int h = 16;
	int w = 130;

	gNeeded.FillRGBA(x,y,w,h,240,150,46,170); //TITLE BOX
	gNeeded.blackBorder(x,y,w,h);
	gNeeded.DrawString2((HFont)10,x + 15,y,255,255,255,255,L"h00k by johnny");

	gNeeded.FillRGBA(x,y + h + 5,w,menuItems * 16,130,130,130,170); //MENU BOX
	gNeeded.blackBorder(x,y + h + 5,w,menuItems * 16);


	for(int i=0;i<menuItems;i++)
	{

		int vIn = (int)*menu[i].value;
		wchar_t vOut [12];
		_itow_s(vIn,vOut,sizeof(vOut)/2,10);


		if( i!=menuIndex)
		{	
			gNeeded.DrawString2((HFont)10,x + 3, y + (16*i) + 20, 60, 60, 60,255,menu[i].title);
			gNeeded.DrawString2((HFont)10,x + 100, y + (16*i) + 20, 60,60,60,255,vOut);
		}
		else
		{
			gNeeded.DrawString2((HFont)10,x + 3, y + (16*i) + 20, 255, 255, 255,255,menu[i].title);
			gNeeded.DrawString2((HFont)10,x + 100, y + (16*i) + 20, 255,255,255,255,vOut);
		}
	}

	


		if(IsKeyPressed(VK_UP)) //uparrow || mwheelup
		{
		if( menuIndex>0 ) menuIndex--;
		else menuIndex = menuItems - 1;
		}

		else if( IsKeyPressed(VK_DOWN)) //downarrow || mwheeldown
		{
		if( menuIndex<menuItems-1 ) menuIndex++;
		else menuIndex = 0;
		}


		else if( IsKeyPressed(VK_LEFT) ) //leftarrow || leftbutton
		{
			if( menu[menuIndex].value )
			{
			menu[menuIndex].value[0] -= menu[menuIndex].step;
			if( menu[menuIndex].value[0] < menu[menuIndex].min )
				menu[menuIndex].value[0] = menu[menuIndex].max;
			}
		}

		else if( IsKeyPressed(VK_RIGHT) ) //rightarrow || rightbutton
		{
		if( menu[menuIndex].value )
		{
			menu[menuIndex].value[0] += menu[menuIndex].step;
			if( menu[menuIndex].value[0] > menu[menuIndex].max )
				menu[menuIndex].value[0] = menu[menuIndex].min;
		}
		
		}
		
}