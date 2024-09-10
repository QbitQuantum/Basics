bool FSOExecutable::IsRootFolderValid(const wxFileName& path, bool quiet) {
	if ( !path.IsOk() ) {
		if (!quiet) {
			wxLogError(_T(" New root folder %s is not OK"), path.GetFullPath().c_str());			
		}
		return false;
	}
	if ( path.GetPath().IsEmpty() ) {
		if (!quiet) {
			wxLogError(_T(" Root folder %s is empty"), path.GetFullPath().c_str());
		}
		return false;
	}
	return HasFSOExecutables(path);
}