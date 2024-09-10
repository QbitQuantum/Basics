//---------------------------------------------------------
bool CXYZ_Import::On_Execute(void)
{
	CSG_File	Stream;

	if( !Stream.Open(Parameters("FILENAME")->asString(), SG_FILE_R) )
	{
		Error_Set(_TL("file could not be opened"));

		return( false );
	}

	//-----------------------------------------------------
	CSG_Shapes	*pPoints	= Parameters("POINTS")->asShapes();

	pPoints->Create(SHAPE_TYPE_Point, SG_File_Get_Name(Parameters("FILENAME")->asString(), false));

	pPoints->Add_Field("Z", SG_DATATYPE_Double);

	//-----------------------------------------------------
	if( Parameters("HEADLINE")->asBool() )
	{
		CSG_String	sLine;

		if( !Stream.Read_Line(sLine) )
		{
			Error_Set(_TL("could not read headline"));

			return( false );
		}
	}

	//-----------------------------------------------------
	sLong	Length	= Stream.Length();

	double	x, y, z;

	while( Stream.Scan(x) && Stream.Scan(y) && Stream.Scan(z) && Set_Progress((double)Stream.Tell(), (double)Length) )
	{
		CSG_Shape	*pPoint	= pPoints->Add_Shape();

		pPoint->Add_Point(x, y);

		pPoint->Set_Value(0, z);
	}

	return( pPoints->Get_Count() > 0 );
}