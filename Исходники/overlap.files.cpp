// f2 are 0-based
int handlefile (char *filename, int f2, int files)
{
	CLineFields file;

	file.openFile(filename);
	file.readline();
	while (file.endofFile()==false) {

		if(f2 >= (int)file.field.size())
		{
			cerr << "file format error! make sure your files have enough columns seperated by Tabs" << endl;
			exit(-1);
		}
		int pos = atoi(file.field[f2].c_str());
		mark[pos]++;
		if (mark[pos]==files) {
		// this position is covered by all files.
			cout << file.line << endl;
		}

		file.readline();
	}
	file.closeFile();
	return 0;
}