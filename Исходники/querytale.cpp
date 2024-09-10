int main(int argc, char** argv)
{
	if(argc!=8)
	{
		cout<<"querytale [configuration file] [query file] [orthology file] [table Prefix] "
				"[approximate percentage] [percentage of important nodes] [TOP_K] "
				"\n";
		exit(-1);
	}

	Config cf;
    cf.readFile(argv[1]);
    string tablePrefix=string(argv[4]);
   // cf.printConfig();

	QueryParams p;
	p.p_miss=atof(argv[5]);
	if(p.p_miss>1 || p.p_miss<0)
	{
		cout<<"Error: Unrecognized parameter: "<<p.p_miss<<endl;
		exit(-1);
	}
	float p_imp=atof(argv[6]);
	if(p_imp>1 || p_imp<0)
	{
		cout<<"Error: Unrecognized parameter: "<<p_imp<<endl;
		exit(-1);
	}
	p.top_k=atoi(argv[7]);
	if(p.top_k<0)
	{
		cout<<"Error: Unrecognized parameter: "<<p.top_k<<endl;
		exit(-1);
	}

	FILE* fin=fopen(argv[2], "r");
	if(!fin)
	{
	   cout << "Error: Unable to open file |" << argv[2] << "|\n";
	   exit(-1);
	}

	string filePrefix=string(argv[2]);
	int i=filePrefix.find_last_of(".");
	if(i>0)
		filePrefix=filePrefix.substr(0, i);

	FILE* orthf=NULL;

	string orth_file_name=string(argv[3]);

	orthf=fopen(orth_file_name.c_str(), "r");
	if(!orthf)
	{
	   cout << "Error: Unable to open file |" << orth_file_name << "|\n";
	   exit(-1);
	}

	PGDB* db=new PGDB((char*)cf.dbname.c_str(), (char*)cf.dbuser.c_str(), (char*)cf.dbpwd.c_str());
	if(db==NULL)
	{
		cout<<"Error: Can not create db"<<endl;
		exit(-1);
	}
	debug(15, "db connected!\n");

	Ortholog orth;
	orth.buildOrthologMap(orthf);

	Query qry(db);
	qry.setTablePrefix(tablePrefix);

	HashGraph* Q;
	OrthologInfoList orthinfolist;

	MicroTimer timer;
    timer.reset();

//	Q=readGraphSAGAFormat(fin, orth, orthinfolist);
	Q=readGraphGDFFormat(fin, "query", orth, orthinfolist);
	if(Q==NULL)
	{
		cout<<"Error: Can not create graph\n";
		exit(-1);
	}
	p.n_imp=(int)(Q->n()*p_imp);
	qry.setQueryParams(p);
	debug(46, "successfully read input file\n");
	debug(47, "successfully read input file2\n");
	assert(Q!=NULL);
	qry.setGraph(Q, &orthinfolist);
	debug(46, "before match, everything is fine\n");
	debug(47, "before match, everything is fine2\n");
	qry.performQuery();
	cout<<"-- # of Matches: "<<qry.mlist.size()<<endl;
	for(unsigned int i=0; i<qry.mlist.size(); i++)
	{
		char filename[200];

		int dbgid=qry.mlist[i]->dbgid;
		OrthologInfoList orthinfolist_db;
		HashGraph* DBG=readGraphFromDB(db, tablePrefix, dbgid, orthinfolist_db);
		sprintf(filename, "%s_tale_%s_%d.gdf", filePrefix.c_str(), DBG->getGraphAttrs()->find("name")->second.value.c_str(), i+1);
		cout<<"   Match "<<i+1<<": "<<filename<<endl;
		ofstream of(filename);
		if(!of.is_open())
		{
			cout<<"Error: Can not open file "<<filename<<endl;
			exit(-1);
		}
		//writeMatch(cout, *(qry.mlist[i]));
		writeMatchGDF(of, Q, &orthinfolist, DBG, &orthinfolist_db, *(qry.mlist[i]), orth);
		of.close();
		delete qry.mlist[i];
		delete DBG;
	}
	cout<<"-- Execution Time (s): "<<fixed<<setprecision(2)<<timer.stop_seconds()<<endl;
	if(fin)
		fclose(fin);
	if(orthf!=NULL)
		fclose(orthf);

	delete Q;
	if(db!=NULL)
	{
		delete db;
		db=NULL;
	}
    return 0;
}