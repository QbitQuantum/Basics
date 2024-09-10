void doQuery( XmlTransaction &txn, XmlManager &db, const XmlContainer &container, const std::string &query )
{
	////////////////////////////////////////////////////////////////////////
	//////  Performs a simple query (no context) against the   ///////
	//////  provided container.                                      ///////
	////////////////////////////////////////////////////////////////////////

	///// some defensive code eliminated for clarity //

	// Perform the query. Result type is by default Result Document
	std::string fullQuery = "collection('" + container.getName() + "')" + query;
	try {
		std::cout << "Exercising query '" << fullQuery << "' " << std::endl;
		std::cout << "Return to continue: ";
		getc(stdin);

		XmlQueryContext context = db.createQueryContext();

		XmlResults results( db.query( txn, fullQuery, context) );
		XmlValue value;
		while( results.next(value) ) {
			// Obtain the value as a string and print it to stdout
			std::cout << value.asString() << std::endl;
		}

		std::cout << (unsigned int) results.size()
			<< " objects returned for expression '"
			<< fullQuery << "'\n" << std::endl;

	}
	catch(XmlException &e) {
		std::cerr << "Query " << fullQuery << " failed\n";
		std::cerr << e.what() << "\n";
		txn.abort();
		exit( -1 );
	}
	catch(std::exception &e) {
		std::cerr << "Query " << fullQuery << " failed\n";
		std::cerr << e.what() << "\n";
		txn.abort();
		exit( -1 );
	}
}