	void testListingFiles(){
		RuntimeErrorValidator * validator = buildErrorSuccessValidator();
		List l = getAllFiles("VDA1", validator);
		if(hasError(validator)){
			error(validator->errorDescription);
			return ;
		}

		Iterator * ite = buildIterator(l);

		char * element = NULL;
		while( hasMoreElements(ite)){
			element = next(ite);
			info( concatAll(4, "Archivo: " , element , " con tamaño: " , ltoa(getCurrentFileSize("VDA1" , element , validator))));
		}

	}