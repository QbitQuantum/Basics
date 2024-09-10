void deleteIndex( XmlContainer &container, const std::string &URI,
				 const std::string &nodeName, const std::string &indexType,
				 XmlTransaction &txn, XmlUpdateContext &uc )
{
	std::cout << "Deleting index type: '" << indexType << ""
		<< " from node: '" << nodeName << "'." << std::endl;
	try
	{
		//Retrieve the XmlIndexSpecification from the container
		XmlIndexSpecification idxSpec = container.getIndexSpecification( txn );

		std::cout << "Before the delete, the following indexes are maintained for the container:" << std::endl;
		std::string uri, name, index;
		while( idxSpec.next(uri, name, index) )
		{
			// Obtain the value as a string and print it to the console
			std::cout << "\tFor node '" << name << "', found index: '" << index << "'." << std::endl;
		}
		std::cout << "\n" << std::endl;

		//Delete the indexes from the specification.
		idxSpec.deleteIndex( URI, nodeName, indexType );

		//Set the specification back to the container
		container.setIndexSpecification( txn, idxSpec, uc );

		//Show the remaining indexes in the container, if any.
		std::cout << "After the delete, the following indexes exist for the container:" << std::endl;
		idxSpec.reset();
		while( idxSpec.next(uri, name, index) )
		{
			// Obtain the value as a string and print it to the console
			std::cout << "\tFor node '" << name << "', found index: '" << index << "'." << std::endl;
		}
		std::cout << "\n" << std::endl;
	}
	//Catches XmlException.
	catch(std::exception &e)
	{
		std::cerr << "Index delete failed: \n";
		std::cerr << e.what() << "\n";
		txn.abort();

		exit( -1 );
	}
	std::cout << "Index deleted successfully.\n" << std::endl;

}