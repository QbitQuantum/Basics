void dumpInfo( MObject fileNode, 
               MFnDependencyNode& nodeFn, 
			   MObjectArray& nodePath )
{
    MObject currentNode;
	MObject	fileAttr = nodeFn.attribute("fileTextureName");
	MPlug	plugToFile( fileNode, fileAttr ); 
    MFnDependencyNode  dgFn;
	MStatus stat;

    cerr << "Name:    " << nodeFn.name() << endl;

	MObject	fnameValue;
	stat = plugToFile.getValue( fnameValue );
	if ( !stat ) {
		stat.perror("error getting value from plug");
	} else {
		MFnStringData stringFn( fnameValue );
		cerr << "Texture: " << stringFn.string() << endl;
	}

    cerr << "Path:    ";
    for ( int i = nodePath.length()-1; i >= 0; i-- ) {
        currentNode = nodePath[i];
        dgFn.setObject( currentNode );
        cerr << dgFn.name() << "(" << dgFn.typeName() << ")";
		if ( i > 0)
			cerr << " ->\n         ";
    }
    cerr << endl;
}