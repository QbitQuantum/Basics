void SoFileSubgraph::readFile(const char *fileName){

    // open the input file
    SoInput sceneInput;
    if (!sceneInput.openFile(fileName)) {
		SoDebugError::post("SoFileSubgraph::readFile()",
				"Cannot open file '%s'",
				fileName);
        return;
    }
    if (!sceneInput.isValidFile()){
		SoDebugError::post("SoFileSubgraph::readFile()",
				"file '%s' is not a valid Inventor file",
				fileName);
       return;
    }
    else{
		SoDebugError::postInfo("SoFileSubgraph::readFile()",
				"file '%s' read successfully",
				fileName);
    }

    // read the whole file into the database
    SoSeparator *subgraph=SoDB::readAll(&sceneInput);
    subgraph->ref();
    if (subgraph ==NULL) {
		SoDebugError::post("SoFileSubgraph::readFile()",
				"problem reading contents of file '%s'",
				fileName);
        return;
    }
    SoSeparator *graphRoot=SO_GET_ANY_PART(this,"root",SoSeparator);
    graphRoot->addChild(subgraph);

    sceneInput.closeFile();
}