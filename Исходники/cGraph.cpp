void cGraph::LoadFromDB()
{
	myGraph.clear();

	int row_count = theDB.Query(L"SELECT * FROM vertex;");

	vertex_iter_t vi;
	for( int k = 0; k < row_count; k++ ) {
		boost::add_vertex(  myGraph );
		vi = boost::vertices( myGraph ).second - 1;
		myGraph[*vi].myName = theDB.myResult[k*5+1];
		myGraph[*vi].myFixedLocation = _wtoi(theDB.myResult[k*5+4].c_str()) != 0;
		//if( myGraph[*vi].myFixedLocation ) {
			myGraph[*vi].myPoint[0] = _wtof(theDB.myResult[k*5+2].c_str());
			myGraph[*vi].myPoint[1] = _wtof(theDB.myResult[k*5+3].c_str());
		//}
	}

	row_count = theDB.Query(L"SELECT * FROM edge;");

	for( int k = 0; k < row_count; k++ ) {
		int a,b;
		a = _wtoi( theDB.myResult[k*3+1].c_str());
		b = _wtoi( theDB.myResult[k*3+2].c_str());
		boost::add_edge( a, b, myGraph );
	}
}