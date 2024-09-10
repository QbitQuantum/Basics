void update(float time_increase)
{
	int newindex=-1;
	float x,y;
	getCursorPos(&x,&y);
	if (x >= 400 && y <= 300)
	{
		if      (x-400 < (300-y)/2) newindex=0;
		else if (x-400 > (300-y)*2) newindex=2;
		else                        newindex=1;
	}
	else if (x < 400 && y <= 300)
	{
		if      (400-x < (300-y)/2) newindex=0;
		else if (400-x > (300-y)*2) newindex=6;
		else                        newindex=7;
	}
	else if (x >= 400 && y > 300)
	{
		if      (x-400 < (y-300)/2) newindex=4;
		else if (x-400 > (y-300)*2) newindex=2;
		else                        newindex=3;
	}
	else if (x < 400 && y > 300)
	{
		if      (400-x < (y-300)/2) newindex=4;
		else if (400-x > (y-300)*2) newindex=6;
		else                        newindex=5;
	}
	if (newindex >= 0)
	{
		clips[cClip]->pause();
		cClip=newindex;
		clips[cClip]->play();
	}
	mgr->update(time_increase);
}