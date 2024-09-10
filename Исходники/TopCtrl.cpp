bool TopCtrl::OnCreate (Win::CreateData const * create, bool & success) 
{
	Win::Dow::Handle win = GetWindow ();
	ResString caption (win.GetInstance (), ID_CAPTION);
	try
	{
		TheOutput.Init (caption);
		win.SetText (caption);
		_commander.reset (new Commander (win));
		_commander->SetModelessManager (&_modelessMan);
		_cmdVector.reset (new CmdVector (Cmd::Table, _commander.get ()));
		Accel::Maker accelMaker (Accel::Keys, *_cmdVector);
		_kbdAccel.reset (new Accel::Handler (win, accelMaker.Create ()));
		_msgPrepro.SetKbdAccelerator (_kbdAccel.get ());
		_menu.reset (new Menu::DropDown (Menu::barItems, *_cmdVector));
		_menu->AttachToWindow (win);
		_view.reset (new View (win));
		RegisterAsDropTarget(win);

		win.PostMsg (_initMsg);
		success = true;
	}
	catch (Win::Exception e)
	{
		TheOutput.Display (e);
		success = false;
	}
	catch (...)
	{
		Win::ClearError ();
		TheOutput.Display ("Initialization -- Unknown Error", Out::Error);
		success = false;
	}
	TheOutput.SetParent (win);
	_ready = true;
	return true;
}