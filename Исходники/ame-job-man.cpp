bool AmeJobMan::makeDirs(wxFileName f){
	wxFileName p = f.GetPath();
	if(f.DirExists())
		return true;
	if(!p.DirExists() && !makeDirs(p))
		return false;
	return f.Mkdir();
}