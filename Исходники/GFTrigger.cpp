int stateMatchValue(char *name, char *value) {
	GFSprite *sp;
	char *svalue;
	sp = getCurrentSprite();		 	
	if (sp!=NULL) {
		svalue = (char *) sp->getStateValue(name);		
	}
	if ( (svalue==NULL) || (value==NULL) ) 
		return 0;
	string a(value), b(svalue);
	transform (a.begin(), a.end(), a.begin(), tolower);
	transform (b.begin(), b.end(), b.begin(), tolower);
	cout << "Comparing '" << value << "' with '" << svalue << "'\n";
	cout << "Returning '";
	cout << ((a==b) ? "TRUE" : "FALSE") ;
	cout << "'\n\n";
	return (a==b);
}