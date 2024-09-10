//---------------------------------------------------------
bool CCRU_Table_Import::On_Execute(void)
{
	//-----------------------------------------------------
	CSG_File	File;

	if( !File.Open(Parameters("FILE")->asString(), SG_FILE_R, false) )
	{
		Error_Fmt("%s [%s]", _TL("could not open file"), Parameters("FILE")->asString());

		return( false );
	}

	//-----------------------------------------------------
	CSG_String	sLine;

	if( !File.Read_Line(sLine) )
	{
		Error_Fmt("%s [%s]", _TL("failed to read header"), Parameters("FILE")->asString());

		return( false );
	}

	//-----------------------------------------------------
	int		nx, ny, nMonths;
	double	Cellsize, xMin, yMin, xMax, yMax;

	if( !File.Scan(Cellsize)
	||  !File.Scan(xMin    ) || !File.Scan(yMin    )
	||  !File.Scan(xMax    ) || !File.Scan(yMax    )
	||  !File.Scan(nx      ) || !File.Scan(ny      )
	||  !File.Scan(nMonths ) )
	{
		Error_Fmt("%s [%s]", _TL("failed to read header"), Parameters("FILE")->asString());

		return( false );
	}

	//-----------------------------------------------------
	CSG_Grid_System	System(Cellsize, xMin, yMin, nx, ny);

	if( !System.is_Valid() || System.Get_XMax() != xMax || System.Get_YMax() != yMax )
	{
		Error_Fmt("%s [%s]", _TL("failed to read header"), Parameters("FILE")->asString());

		return( false );
	}

	//-----------------------------------------------------
	bool	bShift	= Parameters("SHIFT")->asBool();

	if( bShift )
	{
		System.Assign(Cellsize, xMin - 180.0, yMin, nx, ny);
	}

	//-----------------------------------------------------
	CSG_String	Name	= SG_File_Get_Name(Parameters("FILE")->asString(), false);

	Parameters("GRIDS")->asGridList()->Del_Items();

	for(int iMonth=0; iMonth<nMonths && !File.is_EOF() && Process_Get_Okay(); iMonth++)
	{
		Process_Set_Text("%s %d", _TL("Band"), 1 + iMonth);

		CSG_Grid	*pGrid	= SG_Create_Grid(System, SG_DATATYPE_Short);

		pGrid->Fmt_Name("%s_%02d", Name.c_str(), 1 + iMonth);
		pGrid->Set_NoData_Value(-9999);
		pGrid->Get_Projection().Set_GCS_WGS84();

		Parameters("GRIDS")->asGridList()->Add_Item(pGrid);

		//-------------------------------------------------
		for(int y=0; y<ny && !File.is_EOF() && Set_Progress(y, ny); y++)
		{
			if( File.Read_Line(sLine) && sLine.Length() >= 5. * nx )
			{
				for(int x=0, xx=bShift?nx/2:x, yy=ny-1-y; x<nx; x++, xx++)
				{
					double	z;

					CSG_String	s	= sLine.Mid(x * 5, 5);

					if( s.asDouble(z) )
					{
						pGrid->Set_Value(xx % nx, yy, z);
					}
					else
					{
						pGrid->Set_NoData(xx % nx, yy);
					}
				}
			}
		}
	}

	//-----------------------------------------------------
	return( true );
}