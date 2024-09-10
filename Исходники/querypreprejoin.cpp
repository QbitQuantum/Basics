int main()
{
	const int buffsize = 1 << 4;
	const int threads = THREADS;

	vector<string> tmpfileint;
	vector<string> tmpfiledouble;

	for (int i=0; i<threads; ++i)
	{
		ostringstream oss;
		oss << "testfileinttoint" << setfill('0') << setw(2) << i << ".tmp";
		tmpfileint.push_back(oss.str());
		createfileint(oss.str().c_str(), i, TUPLES);
	}
	for (int i=0; i<threads; ++i)
	{
		ostringstream oss;
		oss << "testfileinttodouble" << setfill('0') << setw(2) << i << ".tmp";
		tmpfiledouble.push_back(oss.str());
		createfiledouble(oss.str().c_str(), i, TUPLES);
	}

	Config cfg;

	cfg.getRoot().add("path", Setting::TypeString) = "./";
	cfg.getRoot().add("buffsize", Setting::TypeInt) = buffsize;

	// Init node1a
	Setting& scannode1 = cfg.getRoot().add("scan1", Setting::TypeGroup);
	scannode1.add("filetype", Setting::TypeString) = "text";
	Setting& files1 = scannode1.add("files", Setting::TypeList);
	Setting& mapping1 = scannode1.add("mapping", Setting::TypeList);
	for (int i=0; i<threads; ++i)
	{
		files1.add(Setting::TypeString) = tmpfileint.at(i);
		Setting& mapping1group = mapping1.add(Setting::TypeList);
		mapping1group.add(Setting::TypeInt) = i;
	}
	Setting& schemanode1 = scannode1.add("schema", Setting::TypeList);
	schemanode1.add(Setting::TypeString) = "long";
	schemanode1.add(Setting::TypeString) = "long";

	// Init node1b
	Setting& scannode2 = cfg.getRoot().add("scan2", Setting::TypeGroup);
	scannode2.add("filetype", Setting::TypeString) = "text";
	Setting& files2 = scannode2.add("files", Setting::TypeList);
	Setting& mapping2 = scannode2.add("mapping", Setting::TypeList);
	for (int i=0; i<threads; ++i)
	{
		files2.add(Setting::TypeString) = tmpfiledouble.at(i);
		Setting& mapping2group = mapping2.add(Setting::TypeList);
		mapping2group.add(Setting::TypeInt) = i;
	}
	Setting& schemanode2 = scannode2.add("schema", Setting::TypeList);
	schemanode2.add(Setting::TypeString) = "long";
	schemanode2.add(Setting::TypeString) = "dec";

	// Init node2
	Setting& joinnode = cfg.getRoot().add("join", Setting::TypeGroup);

	joinnode.add("mostfreqbuildkeyoccurances", Setting::TypeInt) = 1;

	// Partition group tree.
	Setting& pgnode = joinnode.add("threadgroups", Setting::TypeList);
	for (int i=0; i<threads; ++i)
	{
		Setting& singlepart = pgnode.add(Setting::TypeArray);
		singlepart.add(Setting::TypeInt) = i;
	}

	// Join attribute and projection tree.
	joinnode.add("buildjattr", Setting::TypeInt) = 0;
	joinnode.add("probejattr", Setting::TypeInt) = 0;

	Setting& projectnode = joinnode.add("projection", Setting::TypeList);
	projectnode.add(Setting::TypeString) = "B$1";
	projectnode.add(Setting::TypeString) = "P$1";

	// Init node3
	Setting& mergenode = cfg.getRoot().add("merge", Setting::TypeGroup);
	mergenode.add("threads", Setting::TypeInt) = threads;

//	cfg.write(stdout);

	// build plan tree
	q.tree = &node3;
	node3.nextOp = &node2;
	node2.buildOp = &node1a;
	node2.probeOp = &node1b;

	// initialize each node
	node1a.init(cfg, scannode1);
	node1b.init(cfg, scannode2);
	node2.init(cfg, joinnode);
	node3.init(cfg, mergenode);

#ifdef VERBOSE
	cout << "---------- QUERY PLAN START ----------" << endl;
	PrettyPrinterVisitor ppv;
	q.accept(&ppv);
	cout << "----------- QUERY PLAN END -----------" << endl;
#endif

	compute();

	for (int i=0; i<TUPLES*THREADS; ++i) 
	{
		const int correctcount = 1;
		if (verify[i] < correctcount)
			fail("Tuples are missing from output.");
		if (verify[i] > correctcount)
			fail("Extra tuples are in output.");
	}

	q.destroynofree();

	for (int i=0; i<threads; ++i)
	{
		deletefile(tmpfileint.at(i).c_str());
		deletefile(tmpfiledouble.at(i).c_str());
	}

	return 0;
}