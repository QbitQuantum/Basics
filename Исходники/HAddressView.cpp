/***********************************************************
 * ChangeAccount
 ***********************************************************/
void
HAddressView::ChangeAccount(const char* name)
{
	BPath path;
	::find_directory(B_USER_SETTINGS_DIRECTORY,&path);
	path.Append(APP_NAME);
	path.Append("Accounts");
	path.Append(name);
	
	BFile file(path.Path(),B_READ_ONLY);
	if(file.InitCheck() == B_OK)
	{
		BMessage msg;
		msg.Unflatten(&file);
		BString name,from,address;
		
		if(msg.FindString("real_name",&name) != B_OK)
			name = "";
		if(msg.FindString("address",&address) != B_OK)
		{
			address = "";
			(new BAlert("",_("Cound not find your email address!\nPlease check your account"),_("OK")))->Go();
			return;
		}
		if(name.Length() > 0)
			from << "\"" <<name << "\" <";
		from += address;
		
		if(name.Length() > 0)
			from << ">";
		fFrom->SetText(from.String());
		// Insert signature.
		BTextView *view = cast_as(Window()->FindView("HMailView"),BTextView);
		if(view)
		{	
			const char* sig_path;
			if(msg.FindString("signature",&sig_path) == B_OK)
			{
				BFile sigfile(sig_path,B_READ_ONLY);
				if(sigfile.InitCheck() == B_OK)
				{
					BString str;
					str << "\n" << sigfile;
					view->Insert(view->TextLength(),str.String(),str.Length());
					view->Select(0,0);
				}
			}
		}
	}
}