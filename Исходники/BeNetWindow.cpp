void
BeNetWindow::LaunchHelp()
{
	Output::Instance()->UI("BeNetWindow::LaunchHelp\n");
//	entry_ref ref;
	
// OliverESP: I though do something like this
// I saw code from SampleStudio and they make the same
// it doesn´t look pretty. All this just to know your current path

		BPath path;
		
		app_info ai;
		be_app->GetAppInfo(&ai);	
		BEntry entry(&ai.ref);
		
		entry.GetPath(&path);
		path.GetParent(&path);
		path.Append("help/gettingstarted.htm");
		
		char *help = new char[strlen(path.Path())+1];
		sprintf(help, path.Path());
		be_roster->Launch("text/html",1, &help);
		delete help;	

//	if (get_ref_for_path("help/help.htm", &ref) == B_OK)
//		be_roster->Launch(&ref);

}