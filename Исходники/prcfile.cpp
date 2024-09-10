//lib functions
int loadfiletopalm(std::string path){
	struct stat stat_buf;
	stat(path.c_str(), &stat_buf);
	if(stat_buf.st_size == 0)return LOCKEDFILE;
	size_t_68k size = stat_buf.st_size;
	UBYTE *mempool = new UBYTE[size];
	ifstream appfile (path,ios::in | ios::binary);
	if (appfile.is_open()){
		appfile.read((char*)mempool,size);
	}
	appfile.close();

	UWORD flags = (UWORD)mempool[0x20] << 8 | mempool[0x21];

	int pass;
	string ftype = getfiletype(path);
	//working area
	if(ftype == "prc" && (flags & dmHdrAttrResDB))pass = prcparse(mempool,size);
	else if(ftype == "pdb" && !(flags & dmHdrAttrResDB))pass = pdbparse(mempool,size);
	else if(ftype == "prc" && !(flags & dmHdrAttrResDB)){
		dbgprintf("Conflicting filetypes: name is .prc but db says it is a record database\n");
		pass = pdbparse(mempool,size);
	}
	else if(ftype == "pdb" && (flags & dmHdrAttrResDB)){
		dbgprintf("Conflicting filetypes: name is .pdb but db says it is a resource database\n");
		pass = prcparse(mempool,size);
	}
	else{
		TEMPHACK;
		//display some where other then the console
		if(ftype == "pqa")dbgprintf("PQA is just a web page.(This is not a web browser.)\n");
		else dbgprintf("Filetype:%s is not supported\n",ftype.c_str());
		pass = NOTPALMFILE;
	}

	delete[] mempool;
	return pass;
}