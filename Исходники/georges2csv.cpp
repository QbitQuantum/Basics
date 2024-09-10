void buildFileVector(std::vector<std::string> &filenames, const std::string &filespec)
{
	uint i,j;
	// split up the filespec into chains
	CSString filters = filespec;
	filters.strip();
	std::vector<std::string> in, out;

	while (!filters.empty())
	{
		CSString filter = filters.strtok(" \t");
		if (filter.empty())
			continue;

		switch (filter[0])
		{
		case '+':
			in.push_back(filter.leftCrop(1)); break;
			break;
		case '-':
			out.push_back(filter.leftCrop(1)); break;
			break;
		default:
			fprintf(stderr,"Error in '%s' : filter must start with '+' or '-'\n",
				filter.c_str());
			getchar(); 
			exit(1);
		}
	}

/*	for (i=0;i<filespec.size();)
	{
		for (j=i;j<filespec.size() && filespec[j]!=' ' && filespec[j]!='\t';j++) {}
		switch(filespec[i])
		{
		case '+': 
			in.push_back(filespec.substr(i+1,j-i-1)); break;
		case '-': 
			out.push_back(filespec.substr(i+1,j-i-1)); break;
		default: 
			fprintf(stderr,"Filter must start with '+' or '-'\n",&(filespec[i])); getchar(); exit(1);
		}
		i=j;
		while (i<filespec.size() && (filespec[i]==' ' || filespec[i]=='\t')) i++; // skip white space
	}
*/
	// use the filespec as a filter while we build the sheet file vector
	for (i=0;i<files.size();i++)
	{
		bool ok=true;

		// make sure the filename includes all of the include strings
		for (j=0;j<in.size() && ok;j++)
		{
			if (!testWildCard(CFile::getFilename(files[i]), in[j]))
			{
				ok=false;
			}
		}

		// make sure the filename includes none of the exclude strings
		for (j=0;j<out.size() && ok;j++)
		{
			if (testWildCard(CFile::getFilename(files[i]), out[j]))
			{
				ok=false;
			}
		}

		// if the filename matched all of the above criteria then add it to the list
		if (ok)
		{
			printf("Added: %s\n",CFile::getFilename(files[i]).c_str());
			filenames.push_back(files[i]);
		}
	}
	printf("Found: %zu matching files (from %zu)\n",filenames.size(),files.size());

}