int main()
{
    const int buffsize = 1 << 4;
    const int threads = 4;

    const char* tmpfileint = "testfileinttoint.tmp";
    const char* tmpfiledouble = "testfileinttodouble.tmp";

    Config cfg;

    createfile(tmpfileint, TUPLES);
    createfiledouble(tmpfiledouble, TUPLES);

    cfg.getRoot().add("path", Setting::TypeString) = "./";
    cfg.getRoot().add("buffsize", Setting::TypeInt) = buffsize;

    // Init node1a
    Setting& scannode1 = cfg.getRoot().add("scan1", Setting::TypeGroup);
    scannode1.add("filetype", Setting::TypeString) = "text";
    Setting& files1 = scannode1.add("files", Setting::TypeList);
    files1.add(Setting::TypeString) = tmpfileint;
    Setting& mapping1 = scannode1.add("mapping", Setting::TypeList);
    Setting& mapping1group0 = mapping1.add(Setting::TypeList);
    for (int i=0; i<threads; ++i)
        mapping1group0.add(Setting::TypeInt) = i;
    Setting& schemanode1 = scannode1.add("schema", Setting::TypeList);
    schemanode1.add(Setting::TypeString) = "long";
    schemanode1.add(Setting::TypeString) = "long";

    // Init node1b
    Setting& scannode2 = cfg.getRoot().add("scan2", Setting::TypeGroup);
    scannode2.add("filetype", Setting::TypeString) = "text";
    Setting& files2 = scannode2.add("files", Setting::TypeList);
    files2.add(Setting::TypeString) = tmpfiledouble;
    Setting& mapping2 = scannode2.add("mapping", Setting::TypeList);
    Setting& mapping2group0 = mapping2.add(Setting::TypeList);
    for (int i=0; i<threads; ++i)
        mapping2group0.add(Setting::TypeInt) = i;
    Setting& schemanode2 = scannode2.add("schema", Setting::TypeList);
    schemanode2.add(Setting::TypeString) = "long";
    schemanode2.add(Setting::TypeString) = "dec";

    // Init node2
    Setting& joinnode = cfg.getRoot().add("join", Setting::TypeGroup);

    joinnode.add("maxbuildtuples", Setting::TypeInt) = TUPLES * 2;
    joinnode.add("maxprobetuples", Setting::TypeInt) = TUPLES * 2;

    // Partition group tree.
    Setting& pgnode = joinnode.add("threadgroups", Setting::TypeList);
    Setting& singlepart = pgnode.add(Setting::TypeArray);
    for (int i=0; i<threads; ++i)
        singlepart.add(Setting::TypeInt) = i;

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

    for (int i=0; i<TUPLES; ++i) {
        if (verify[i] < 1)
            fail("Tuples are missing from output.");
        if (verify[i] > 1)
            fail("Extra tuples are in output.");
    }

    q.destroynofree();

    deletefile(tmpfileint);
    deletefile(tmpfiledouble);

    return 0;
}