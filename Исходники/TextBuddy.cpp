//Helper function for sayHi(): strips a full path of the directory prefix.
//Input: character array of the directory path + filename
//Output: a string containing the filename
std::string TextBuddy::getFilenameFromPath(char* argv){
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];

	_splitpath_s(argv, drive, dir, fname, ext);
	std::stringstream ss;
	ss << fname << ext;
	std::string filename = "";
	ss >> filename;
	return filename;
}