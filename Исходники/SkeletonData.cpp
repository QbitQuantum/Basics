void SkeletonData::validateDirectory(std::string & directory) {
	if( PathFileExistsA(directory.c_str()) == TRUE)  { 
		if ( directory.back() != (char)"/") {
			directory += "/";
		}
		//this->directory = directory;
		// directory ok!
	}else{
		app::console() << "Directory does not exist!" << std::endl;
		throw std::exception("Directory does not exist!");
	}
}