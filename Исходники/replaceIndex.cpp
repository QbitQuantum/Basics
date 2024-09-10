void replaceIndex( XmlContainer &container, const std::string &URI,
				  const std::string &nodeName, const std::string &indexType,
				  XmlTransaction &txn, XmlUpdateContext &uc)
{
	std::cout << "Replacing index on node: " << nodeName << std::endl;
	try
	{
		//Retrieve the XmlIndexSpecification from the container
		XmlIndexSpecification idxSpec = container.getIndexSpecification( txn );

		//Lets see what indexes exist on this container
		std::string uri, name, index;
		int count = 0;
		std::cout << "Before index add." << std::endl;
		while( idxSpec.next(uri, name, index) )
		{
			// Obtain the value as a string and print it to the console
			std::cout << "\tFor node '" << name << "', found index: '" << index << "'." << std::endl;
			count ++;
		}

		std::cout << count << " indexes found." << std::endl;

		//Replace the indexes for the specified node
		idxSpec.replaceIndex( URI, nodeName, indexType );

		//Set the specification back to the container
		container.setIndexSpecification( txn, idxSpec, uc );

		//Look at the indexes again to make sure our replacement took.
		count = 0;
		idxSpec.reset();
		std::cout << "After index add." << std::endl;
		while( idxSpec.next(uri, name, index) )
		{
			// Obtain the value as a string and print it to the console
			std::cout << "\tFor node '" << name << "', found index: '" << index << "'." << std::endl;
			count ++;
		}

		std::cout << count << " indexes found." << std::endl;

	}
	//Catches XmlException
	catch(std::exception &e)
	{
		std::cerr << "Index replace failed: \n";
		std::cerr << e.what() << "\n";
		txn.abort();

		exit( -1 );
	}
	std::cout << "Index replaced successfully." << std::endl;

}