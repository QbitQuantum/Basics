int main(int argc, char *argv[]) {

    try {
        cout << "mongoperf" << endl;

        if( argc > 1 ) { 
cout <<

"\n"
"usage:\n"
"\n"
"  mongoperf < myjsonconfigfile\n"
"\n"
"  {\n"
"    nThreads:<n>,     // number of threads\n"
"    fileSizeMB:<n>,   // test file size\n"
"    sleepMicros:<n>,  // pause for sleepMicros/nThreads between each operation\n"
"    mmf:<bool>,       // if true do i/o's via memory mapped files\n"
"    r:<bool>,         // do reads\n"
"    w:<bool>          // do writes\n"
"  }\n"
"\n"
"most fields are optional.\n"
"non-mmf io is direct io (no caching). use a large file size to test making the heads\n"
"  move significantly and to avoid i/o coalescing\n"
"mmf io uses caching (the file system cache).\n"
"\n"

<< endl;
            return 0;
        }

        cout << "use -h for help" << endl;

        char input[1024];
        memset(input, 0, sizeof(input));
        cin.read(input, 1000);
        if( *input == 0 ) { 
            cout << "error no options found on stdin for mongoperf" << endl;
            return 2;
        }

        string s = input;
        str::stripTrailing(s, "\n\r\0x1a");
        try { 
            options = fromjson(s);
        }
        catch(...) { 
            cout << s << endl;
            cout << "couldn't parse json options" << endl;
            return -1;
        }
        cout << "options:\n" << options.toString() << endl;

        go();
#if 0
        cout << "connecting to localhost..." << endl;
        DBClientConnection c;
        c.connect("localhost");
        cout << "connected ok" << endl;
        unsigned long long count = c.count("test.foo");
        cout << "count of exiting documents in collection test.foo : " << count << endl;

        bo o = BSON( "hello" << "world" );
        c.insert("test.foo", o);

        string e = c.getLastError();
        if( !e.empty() ) { 
            cout << "insert #1 failed: " << e << endl;
        }

        // make an index with a unique key constraint
        c.ensureIndex("test.foo", BSON("hello"<<1), /*unique*/true);

        c.insert("test.foo", o); // will cause a dup key error on "hello" field
        cout << "we expect a dup key error here:" << endl;
        cout << "  " << c.getLastErrorDetailed().toString() << endl;
#endif
    } 
    catch(DBException& e) { 
        cout << "caught DBException " << e.toString() << endl;
        return 1;
    }

    return 0;
}