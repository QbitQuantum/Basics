void GlobalLocalNode::setMyNodeNameIfNecessary() 
{

    // FIXME: should change Symbol for the name

    const char *suffix = NULL;
    if (this->isGlobalNode())
	suffix = "Global";	
    else if (this->isLocalNode())
	suffix = "Local";	

    if (suffix) {
	char newname[1024];
	Symbol nameSym = this->Node::getNameSymbol(); 
	const char *name = theSymbolManager->getSymbolString(nameSym); 
	SPRINTF(newname,"%s%s",name,suffix);	
	this->myNodeNameSymbol = theSymbolManager->registerSymbol(newname);

	//
	// This resets the text in the notation field in the cdb
	//
	this->setLabelString(newname);
    } else {
	this->clearMyNodeName();
    }

}