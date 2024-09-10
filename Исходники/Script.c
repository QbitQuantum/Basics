global func CreateAttackWave(int angle, int rockets, int anglespread)
{
	var radius = Min(LandscapeWidth()/2, LandscapeHeight()/2);
	var rocket_id = Boomattack;
	// boss
	if(rockets == -1)
	{
		rockets = 1;
		rocket_id = BigBoomattack;
	}
	
	for(var i=0; i<rockets; ++i)
	{
		var rocket_angle = angle + Random(anglespread) - anglespread/2;
		var rocket_radius = radius * RandomX(80,100) / 100;
		var x =  Sin(rocket_angle, rocket_radius)+LandscapeWidth()/2;
		var y = -Cos(rocket_angle, rocket_radius)+LandscapeHeight()/2;

		CreateObjectAbove(rocket_id, x, y)->Launch(rocket_angle + 180);
	}
	
	for(var i=0; i<GetPlayerCount(); ++i)
	{
		var owner = GetPlayerByIndex(i);
		var gui_arrow = FindObject(Find_ID(GUI_GoalArrow), Find_Owner(owner));
		if(!gui_arrow)
		{
			gui_arrow = CreateObjectAbove(GUI_GoalArrow,0,0,owner);
			gui_arrow->SetAction("Show", GetCursor(owner));
			gui_arrow->SetClrModulation(RGB(255,0,0));
			gui_arrow->SetObjectBlitMode(GFX_BLIT_Mod2);
		}
		gui_arrow->SetR(angle);
		gui_arrow.Plane = 500;
	}
}