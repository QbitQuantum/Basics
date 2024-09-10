void getDetails( XmlTransaction &txn, XmlManager &mgr, const XmlContainer &container, const std::string &query, XmlQueryContext &context )
{
	////////////////////////////////////////////////////////////////////////
	//////  Performs an query (in context) against the         ///////
	//////  provided container.                                      ///////
	////////////////////////////////////////////////////////////////////////

	///// some defensive code eliminated for clarity //

	// Perform the query. Result type is by default Result Document
	std::string fullQuery = "collection('" + container.getName() + "')" + query;
	try {
		std::cout << "Exercising query '" << fullQuery << "' " << std::endl;
		std::cout << "Return to continue: ";
		getc(stdin);

		XmlResults results( mgr.query( txn, fullQuery, context ) );
		XmlValue value;
		std::cout << "\n\tProduct : Price : Inventory Level\n";
		while( results.next(value) ) {
			/// Retrieve the value as a document
			XmlDocument theDocument = value.asDocument();

			/// Obtain information of interest from the document. Note that the
			//  wildcard in the query expression allows us to not worry about what
			//  namespace this document uses.
			std::string item = getValue( txn, mgr, theDocument, "fn:string(/*/product)", context);
			std::string price = getValue( txn, mgr, theDocument, "fn:string(/*/inventory/price)", context);
			std::string inventory = getValue( txn, mgr, theDocument, "fn:string(/*/inventory/inventory)", context);

			std::cout << "\t" << item << " : " << price << " : " << inventory << std::endl;

		}
		std::cout << "\n";
		std::cout << (unsigned int) results.size()
			<< " objects returned for expression '"
			<< fullQuery << "'\n" << std::endl;
	}
	//Catches XmlException
	catch(std::exception &e) {
		std::cerr << "Query " << fullQuery << " failed\n";
		std::cerr << e.what() << "\n";
		txn.abort();
		exit(-1);
	}
}