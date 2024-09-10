//-------------------------------------------------------------
// test
//-------------------------------------------------------------
Status test(int t)
{
	char		outfile[10];
	int		Rarray[] = { 0, 1, 0, 3, 4, 4, 4 };
	int		Sarray[] = { 1, 0, 2, 2, 2, 3, 0 };
	int 		R = Rarray[t-1];
	int 		S = Sarray[t-1];
	Status		s;

	sprintf(outfile,"test%d", t);

	// Perform sort-merge on R and S
	sortMerge	sm(files[R],NUM_COLS,attrType,attrSize,JOIN_COL,files[S],NUM_COLS,attrType,attrSize,JOIN_COL,outfile,SORTPGNUM,Ascending,s);
	if (s != OK)
	{
		cout << "Test " << t << " -- sortMerge failed" << endl;
		return s;
	}

	// Write merged results to stdout
	HeapFile*	outf = new HeapFile (outfile,s);
	if (s != OK)
	{
		cout << "Test " << t << " -- result file not created " << endl;
		return s;
	}
        Scan*	scan = outf->openScan(s);
	assert(s == OK);
	int len;
	RID	rid;
	char	rec[sizeof(struct _rec)*2];
	cout << endl;
	cout << "------------ Test " << t << " ---------------" << endl;
	for (s = scan->getNext(rid, rec, len); s == OK; s = scan->getNext(rid, rec, len)) 
	{
	  cout << (*((struct _rec*)&rec)).key << "\t" << (*((struct _rec*)&rec[8])).key << endl;
	}
	cout << "-------- Test " << t << " completed --------" << endl;
	delete scan;
	s=outf->deleteFile();
	if(s!=OK) MINIBASE_CHAIN_ERROR(JOINS,s);
	delete outf;
	return s;
}