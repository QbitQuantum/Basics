//---------------------------------------------------------
bool CGrid_Volume::On_Execute(void)
{
	int			x, y, Method;
	double		Level, Volume, z;
	CSG_Grid		*pGrid;
	CSG_String	s;

	//-----------------------------------------------------
	pGrid	= Parameters("GRID")	->asGrid();
	Level	= Parameters("LEVEL")	->asDouble();
	Method	= Parameters("METHOD")	->asInt();

	//-----------------------------------------------------
	for(y=0, Volume=0.0; y<Get_NY() && Set_Progress(y); y++)
	{
		for(x=0; x<Get_NX(); x++)
		{
			if( !pGrid->is_NoData(x, y) )
			{
				z	= pGrid->asDouble(x, y) - Level;

				switch( Method )
				{
				case 0:	// Count Only Above Base Level
					if( z > 0.0 )
					{
						Volume	+= z;
					}
					break;

				case 1:	// Count Only Below Base Level
					if( z < 0.0 )
					{
						Volume	-= z;
					}
					break;

				case 2:	// Subtract Volumes Below Base Level
					Volume	+= z;
					break;

				case 3:	// Add Volumes Below Base Level
					Volume	+= fabs(z);
					break;
				}
			}
		}
	}

	//-----------------------------------------------------
	Volume	*= pGrid->Get_Cellarea();

	s.Printf(_TL("Volume: %f"), Volume);

	Message_Add(s);
	Message_Dlg(s, _TL("Grid Volume"));

	//-----------------------------------------------------
	return( true );
}