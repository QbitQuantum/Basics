HelloWindow::HelloWindow(BRect theframe)
				: BWindow(theframe, "DynaMate",  B_TITLED_WINDOW, B_NOT_RESIZABLE)
{
/// /// /// /// SOUND /// /// /// /// LÄGG TILL FELKOLLAR !!
	error=0;
	snd = new SoundStuff;

	app_info ai;	
	if (be_app->GetAppInfo(&ai)){ error = B_ERROR; fputs("DynaMate: Error getting AppInfo.\n",stderr); return;}

	entry_ref mref, sref, eref;
	BEntry *ment, *sent, *eent;
	
	BDirectory dir;
	BEntry *exeEnt;
	
	exeEnt = new BEntry(&(ai.ref));
	if (exeEnt->InitCheck())	{ error = B_ERROR; fputs("DynaMate: Error converting ref to Entry.\n",stderr); return;}
	if (exeEnt->GetParent(&dir)){ error = B_ERROR; fputs("DynaMate: Error getting parent.\n",stderr); return;}
	
	ment = new BEntry(&dir, "sfx/move");
	if (ment->InitCheck())		{ error = B_ERROR; fputs("DynaMate: Problems with file 'sfx/move'.\n",stderr); return;}

	sent = new BEntry(&dir, "sfx/stop");
	if (sent->InitCheck())		{ error = B_ERROR; fputs("DynaMate: Problems with file 'sfx/stop'.\n",stderr); return;}

	eent = new BEntry(&dir, "sfx/explosion");
	if (eent->InitCheck())		{ error = B_ERROR; fputs("DynaMate: Problems with file 'sfx/explosion'.\n",stderr); return;}

	if (ment->GetRef(&mref))	{ error = B_ERROR; fputs("DynaMate: Error converting ref to Entry.(mref)\n",stderr); return;}
	if (sent->GetRef(&sref))	{ error = B_ERROR; fputs("DynaMate: Error converting ref to Entry.(sref)\n",stderr); return;}
	if (eent->GetRef(&eref))	{ error = B_ERROR; fputs("DynaMate: Error converting ref to Entry.(eref)\n",stderr); return;}

	delete ment;
	delete sent;
	delete eent;
	delete exeEnt;

	snd->moveblip = new BSound(&mref,true);
	snd->stopblip = new BSound(&sref,true);
	snd->explblip = new BSound(&eref,true);

	if (snd->moveblip->InitCheck()) { error = B_ERROR; fputs("DynaMate: Problems with file 'sfx/move'.\n",stderr); return;}
	if (snd->stopblip->InitCheck()) { error = B_ERROR; fputs("DynaMate: Problems with file 'sfx/stop'.\n",stderr); return;}
	if (snd->explblip->InitCheck()) { error = B_ERROR; fputs("DynaMate: Problems with file 'sfx/explosion'.\n",stderr); return;}

/// /// /// /// /// /// /// /// ///

	frame=theframe;
	totalmoves=0;
	stonesleft=65535;
	SIZE=16;
	file = NULL;		
// reservera banan
	level=(uint8 *)malloc(256+1);		// 256==en piece 1==rekordet
	
// Starta en view	
	frame.OffsetTo(B_ORIGIN);

	gameView = NULL;
	titleView = NULL;
	LaunchTitle();
}