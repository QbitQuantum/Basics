int main(int argc, char** argv) 
{
	//cout<<"distrec size: "<<sizeof(DistRec)<<endl;
	HashGraph* G;
	OrthologInfoList orthinfolist;

	if (argc != 9) {
	cout << "Usage: loadonegraph <configuration file> <graph file name> <orthology file> <table Prefix>"
			"<index choice:0(no index), 1(saga index), 2(tale index), 3(both index)> "
			"<the absolute Unix path name of the temporary directory> <db user> <db user password>\n";
	exit(-1);
	}
	
	string dbuser=string(argv[7]);
	string dbpwd=string(argv[8]);

	cout<<"-- Load Graph: "<<argv[2]<<endl;
	FILE* fin=fopen(argv[2], "r");
	if(!fin)
	{
		cout<<"Unable to open file "<<argv[2]<<endl;
		exit(-1);
	}
	Config cf;
	cf.readFile(argv[1]);
	//cf.printConfig();
	cf.orth_file_name=string(argv[3]);
	cf.tablePrefix=string(argv[4]);
	FILE* orthf=fopen(cf.orth_file_name.c_str(), "r");
	
	if(!orthf)
	{
		cout<<"Unable to open file "<<cf.orth_file_name<<endl;
		exit(-1);
	}
	
	int choice=atoi(argv[5]);
	bool forsaga=false, fortale=false;
	
	forsaga=(choice%2);
	fortale=(choice/2);

	string path=string(argv[6]);
	if(path[path.size()-1]!='/')
		path=path+"/";
	
	string name=path+"node.bin";
	remove(name.c_str());
	FILE* nfile=fopen(name.c_str(),"w");
	
	name=path+"edge.bin";
    remove(name.c_str());
    FILE* efile=fopen(name.c_str(),"w");
    
    name=path+"orth.bin";
    remove(name.c_str());
    FILE* ofile=fopen(name.c_str(),"w");
    
    name=path+"dist.bin";
    remove(name.c_str());
    FILE* dfile=fopen(name.c_str(),"w");
    
    name=path+"frag.bin";
    remove(name.c_str());
    FILE* ffile=fopen(name.c_str(),"w");
    
    name=path+"neig.bin";
    remove(name.c_str());
    FILE* nbfile=fopen(name.c_str(),"w");
    
    if( !nfile || !efile || !ofile || !dfile || !ffile || !nbfile)
	{
	   cout << "Do not have enouph space to create temporary files\n";
	   exit(-1);
	}
	
	PGDB* db=new PGDB((char*)cf.dbname.c_str(), (char*)dbuser.c_str(), (char*)dbpwd.c_str());
	WriteToFile* wtf=new WriteToFile(nfile, efile, ofile, dfile, ffile, nbfile);
	//make headers
	char buff[19];
    memcpy(buff, "PGCOPY\n\377\r\n\0\0\0\0\0\0\0\0\0", sizeof(buff));
                                                                                
    fwrite(buff, sizeof(buff), 1, nfile);
    fwrite(buff, sizeof(buff), 1, efile);
	fwrite(buff, sizeof(buff), 1, ofile);
    fwrite(buff, sizeof(buff), 1, dfile);
    fwrite(buff, sizeof(buff), 1, ffile);
    fwrite(buff, sizeof(buff), 1, nbfile);
	
	//debug(16, "before loading ecmap\n");
	Ortholog orth;
	orth.buildOrthologMap(orthf);
	
	MicroTimer loadTimer;

	LoadGraph loadgrf(cf.frag_size, cf.dmax, db, wtf, cf.tablePrefix);
	
    loadgrf.createTables();	
	//cout<<"Created Tables\n";
	int gid=db->getMaxGraphID(cf.tablePrefix+"_graph");
    
	debug(33, "gid = "<<gid<<endl);
	
    gid++;
	loadTimer.reset();
	
	while((G=readGraphSAGAFormat(fin, orth, orthinfolist))!=NULL)
//	while((G=readGraphGDFFormat(fin, fname,orth, orthinfolist))!=NULL)
	{
		loadgrf.setGraph(gid, G, &orthinfolist, &orth);
		debug(33, "set graph succeeded!\n");
		loadgrf.load(forsaga, fortale);
		debug(33, "load graph succeeded\n");		
		delete G;
		gid++;
	
	}
	fclose(fin);
	

	fclose(orthf);
	fclose(nfile);
	fclose(efile);
	fclose(ofile);
	fclose(dfile);
	fclose(ffile);
	fclose(nbfile);

	loadgrf.copyData(path);
  //  cout<<"Copied Data\n";
	
	if(forsaga)
		cout<<"   Build Index for SAGA Query\n";
	if(fortale)
		cout<<"   Build Index for TALE Query\n";
	
	loadgrf.createIndices();
 //   cout<<"Created Indices\n";
    cout<<"-- Loading Time: "<<loadTimer.stop_seconds()<<endl;

	delete db; db=NULL;
	delete wtf; wtf=NULL;
	return 0;
}