/**
 * Print() 
 *
 * @param BMessage*
 * @return status_t, any result from the operation
 */
status_t MessagePrinter::Print(BMessage* msg)
{
	status_t status;
	BFile file;
	BPath settingsPath;
	// char settingsPath[B_PATH_NAME_LENGTH];
	char  *name; 
	uint32  type; 
	int32   count; 

	// open a file to print message on the desktop
	status = find_directory(B_DESKTOP_DIRECTORY, &settingsPath);
	if (status != B_OK) {
		(new BAlert("","find directory error", "Doh!"))->Go();
		return status;
	}

	settingsPath.Append(msgFileName);
	status = file.SetTo(settingsPath.Path(), B_WRITE_ONLY | B_CREATE_FILE);
	if (status != B_OK) {
		(new BAlert("","file write error", "Doh!"))->Go();
		return status;
	}	
	
	// print the contents of the message to file
	for ( int32 i = 0; 
    	msg->GetInfo(B_ANY_TYPE, i, &name, &type, &count) == B_OK; 
     	i++ ) 
	{ 
		BString out;
		// count
		out << i;
		if (file.Write(out.String(), out.Length()) < 0) {
			(new BAlert("","count write error", "Doh!"))->Go();
			return B_ERROR;
		}	
		// name
		out = " ";
		out << name;
		if (file.Write(out.String(), out.Length()) < 0) {
			(new BAlert("","name write error", "Doh!"))->Go();
			return B_ERROR;
		}	
		
		// type
		switch (type) {
			case B_INT32_TYPE:
				{
				int32 v;
				out = " B_INT32_TYPE ";
				msg->FindInt32(name, 0, &v);
				out << v << '\n';
				}
				break;
			case B_UINT32_TYPE:
				{
				int32 v;
				out = " B_UINT32_TYPE ";
				msg->FindInt32(name, 0, &v);
				out << v << '\n';
				}
				break;
			case B_INT64_TYPE:
				{
				int64 v;
				out = " B_INT64_TYPE ";
				msg->FindInt64(name, 0, &v);
				out << v << '\n';
				}
				break;
			case B_FLOAT_TYPE:
				{
				float f;
				out = " B_FLOAT_TYPE ";
				msg->FindFloat(name, 0, &f);
				out << f << '\n';
				}
				break;
			case B_BOOL_TYPE:
				{
				bool b;
				out = " B_BOOL_TYPE ";
				msg->FindBool(name, 0, &b);
				out << (int)b << '\n';
				}
				break;
			case B_MESSAGE_TYPE:
				{
				BMessage *m = new BMessage(); 
				MessagePrinter *mp = new MessagePrinter(name);
				msg->FindMessage(name, m);
				mp->Print(m);
				out = " B_MESSAGE_TYPE \n";
				delete m;
				delete mp;
				}
				break;
			case B_RECT_TYPE:
				{
				BRect r;
				out = " B_RECT_TYPE ";
				msg->FindRect(name, 0, &r);
				out << "{ " 
					<< r.left <<" " 
					<< r.top <<" " 
					<< r.right <<" " 
					<< r.bottom <<" " 
					<< " }"
					<< '\n';
				}
				break;
			case B_STRING_TYPE:
				{
				BString s;
				out = " B_STRING_TYPE ";
				msg->FindString(name, 0, &s);
				out << s.String() << '\n';
				}
				break;
			default:
				out = " UNKNOWN TYPE \n";
				break;
		}
	    if (file.Write(out.String(), out.Length()) < 0) {
			(new BAlert("","value write error", "Doh!"))->Go();
			return B_ERROR;
		}	
	}
	return status;
}