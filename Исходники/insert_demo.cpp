int main() {
    try {
        cout << "connecting to localhost..." << endl;
        DBClientConnection c;
        c.connect("localhost");
        cout << "connected ok" << endl;

        bo o = BSON( "hello" << "world" );

	cout << "inserting..." << endl;

	time_t start = time(0);
	for( unsigned i = 0; i < 1000000; i++ ) {
	  c.insert("test.foo", o);
	}

	// wait until all operations applied
	cout << "getlasterror returns: \"" << c.getLastError() << '"' << endl;

	time_t done = time(0);
	time_t dt = done-start;
	cout << dt << " seconds " << 1000000/dt << " per second" << endl;
    } 
    catch(DBException& e) { 
        cout << "caught DBException " << e.toString() << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}