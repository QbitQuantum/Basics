//Get a document from the container using the document name
void doGetDocument( XmlTransaction &txn, XmlContainer &container, const std::string docname)
{

	try {
		std::cout << "Getting document '" << docname << "' from the container." << std::endl;
		std::cout << "Return to continue: ";
		getc(stdin);
		std::cout << "\n";

		//Get the document from the container using the document name
		XmlDocument theDocument = container.getDocument(txn, docname);
		std::string content;
		std::cout << "Document name: " << theDocument.getName() << std::endl;
		std::cout << theDocument.getContent(content) << std::endl;

	}
	//Catches XmlException
	catch(std::exception &e) {
		std::cerr << "Get document from container failed.\n";
		std::cerr << e.what() << "\n";
		txn.abort();
		exit( -1 );
	}
}