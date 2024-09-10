// f1, f2 are 0-based
int handlefile (char *filename, int f1, int f2)
{
	CLineFields file;

	file.openFile(filename);
	file.readline();
	while (file.endofFile()==false) {

		if( f1 >= (int)file.sect_num ||  f2 >= (int)file.sect_num)
		{
			cerr << "file format error! make sure your files have enough columns seperated by Tabs" << endl;
			exit(-1);
		}
		string f1f2 = string(file.sect[f1])+","+string(file.sect[f2]); //f1f2 is used as the index
		if  (results[f1f2] == "")
			results[f1f2] = string(filename)+"\t"+file.line;
		else
			results[f1f2] = results[f1f2]+"\t"+string(filename)+"\t"+file.line;
		file.readline();
	}
	file.closeFile();
	return 0;
}