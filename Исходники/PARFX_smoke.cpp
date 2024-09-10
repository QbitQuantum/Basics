//returns true if ready to be removed
PRIVATE bool _fxSmokeUpdate(fxSmoke *mainDat, fxSmoke_par *theSmoke)
{
	double t = TimeGetTime(&theSmoke->delayTimer)/TimeGetDelay(&theSmoke->delayTimer);

	//moving
	if(!theSmoke->bFading)
	{
		if(t <= 1)
		{
			theSmoke->loc[eX] = theSmoke->sLoc[eX] + t*(theSmoke->eLoc[eX]-theSmoke->sLoc[eX]);
			theSmoke->loc[eY] = theSmoke->sLoc[eY] + t*(theSmoke->eLoc[eY]-theSmoke->sLoc[eY]);
			theSmoke->loc[eZ] = theSmoke->sLoc[eZ] + t*(theSmoke->eLoc[eZ]-theSmoke->sLoc[eZ]);

			theSmoke->clr[eA] = t;
		}
		else
		{
			//initialize fading
			theSmoke->bFading = true;

			TimeInit(&theSmoke->delayTimer, mainDat->fadeDelay);
			TimeReset(&theSmoke->delayTimer);
		}
	}
	//fading
	else
	{
		if(t <= 1)
			theSmoke->clr[eA] = 1.0f - t;
		else //we are done
			return true;
	}

	return false;
}