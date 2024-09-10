bool PPToken::readInitList(const wxString &in, int from, wxString& initList, wxArrayString& initListArr)
{
	if((int)in.Length() < from) {
		return false;
	}

	wxString tmpString = in.Mid(from);
	int start = tmpString.Find(wxT("("));
	if(start == wxNOT_FOUND ) {
		return false;
	}
	tmpString = tmpString.Mid(start+1);

	for(size_t i=0; i<(size_t)start; i++) {
		initList << wxT(" ");
	}

	initList << wxT("(");
	wxString word;
	int depth(1);

	for(size_t i=0; i<tmpString.Length(); i++) {
		wxChar ch = tmpString[i];
		initList << ch;
		switch(ch) {
		case wxT(')'):
			depth --;
			if(depth == 0) {
				initListArr.Add(word);
				return true;
			} else {
				word << ch;
			}
			break;
		case wxT('('):
			depth++;
			word << ch;
			break;
		case wxT(','):
			if(depth == 1) {
				initListArr.Add(word);
				word.Clear();
			} else {
				word << ch;
			}
			break;
		default:
			word << ch;
			break;
		}
	}
	return false;
}