void DBVLineIF::Vertexes (DBObjRecord *lineRec,DBCoordinate *coord,DBInt vertexNum)

	{
	DBInt vertex;
	DBFloat length = 0;
	DBCoordinate *vertexes, prevCoord;
	DBObjRecord *dataRec = (DBObjRecord *) NULL;
	DBObjectLIST<DBObjRecord> *dataArrays = Data ()->Arrays ();
	DBRegion lineExtent, dataExtent = Data ()->Extent ();
	DBMathDistanceFunction distFunc = DBMathGetDistanceFunction (Data ());

	prevCoord = NodeCoordFLD->Coordinate (FromNodeFLD->Record (lineRec));
	lineExtent.Expand (prevCoord);
	if (vertexNum > 0)
		{
		if ((dataRec = dataArrays->Item (lineRec->RowID ())) == (DBObjRecord *) NULL)
			{
			if ((dataRec = new DBObjRecord (lineRec->Name (),((size_t) vertexNum) * sizeof (DBCoordinate),sizeof (DBFloat))) == (DBObjRecord *) NULL) return;
			dataArrays->Add (dataRec);
			}
		else	dataRec->Realloc (vertexNum * sizeof (DBCoordinate));
		if ((vertexes = (DBCoordinate *) dataRec->Data ()) == NULL)
			{ CMmsgPrint (CMmsgSysError, "Memory Allocation Error in: %s %d",__FILE__,__LINE__); return; }
		for (vertex = 0;vertex < vertexNum;vertex++)
			{
			lineExtent.Expand (vertexes [vertex] = coord [vertex]);
			length += DBMathCoordinateDistance (distFunc,prevCoord,coord [vertex]);
			prevCoord = coord [vertex];
			}
		}
	VertexesFLD->Record (lineRec,dataRec);
	VertexNumFLD->Int (lineRec,vertexNum);
	length += DBMathCoordinateDistance (distFunc,prevCoord,NodeCoordFLD->Coordinate (ToNodeFLD->Record (lineRec)));
	PerimeterFLD->Float (lineRec,length);
	lineExtent.Expand (NodeCoordFLD->Coordinate (ToNodeFLD->Record (lineRec)));
	ExtentFLD->Region (lineRec,lineExtent);
	dataExtent.Expand (lineExtent);
	Data ()->Extent (dataExtent);
	}