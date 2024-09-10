//---------------------------------------------------------
bool CSRTM30_Import::On_Execute(void)
{
	char	x_sTile[9][5]	= {	"W180", "W140", "W100", "W060", "W020", "E020", "E060", "E100", "E140"	},
			y_sTile[3][4]	= {	"S10", "N40", "N90"	};

	double	dSize			= 30.0 / (60.0 * 60.0);

	//-----------------------------------------------------
	int			xTile, yTile;
	double		xMin, xMax, yMin, yMax;
	TSG_Rect	rOut, rTile;
	CSG_String	sTile;
	CSG_Grid	*pOut;

	//-----------------------------------------------------
	xMin		= Parameters("XMIN")->asInt();
	xMax		= Parameters("XMAX")->asInt();
	yMin		= Parameters("YMIN")->asInt();
	yMax		= Parameters("YMAX")->asInt();

	rOut.xMin	= (180 + xMin) / 40.0 * X_WIDTH;
	rOut.xMax	= rOut.xMin + (int)((xMax - xMin) / dSize);
	rOut.yMin	= ( 60 + yMin) / 50.0 * Y_WIDTH;
	rOut.yMax	= rOut.yMin + (int)((yMax - yMin) / dSize);

	//-----------------------------------------------------
	pOut		= SG_Create_Grid(SG_DATATYPE_Short,
					(int)(rOut.xMax - rOut.xMin),
					(int)(rOut.yMax - rOut.yMin),
					dSize,
					xMin + 0.5 * dSize,
					yMin + 0.5 * dSize
				);

	pOut->Set_NoData_Value(-9999);
	pOut->Assign_NoData();
	pOut->Set_Name(SG_T("SRTM30"));
	pOut->Get_Projection().Create(SG_T("GEOGCS[\"WGS 84\",DATUM[\"WGS_1984\",SPHEROID[\"WGS 84\",6378137,298.257223563,AUTHORITY[\"EPSG\",\"7030\"]],TOWGS84[0,0,0,0,0,0,0],AUTHORITY[\"EPSG\",\"6326\"]],PRIMEM[\"Greenwich\",0,AUTHORITY[\"EPSG\",\"8901\"]],UNIT[\"degree\",0.01745329251994328,AUTHORITY[\"EPSG\",\"9122\"]],AUTHORITY[\"EPSG\",\"4326\"]]"));

	//-----------------------------------------------------
	for(yTile=0, rTile.yMin=0, rTile.yMax=Y_WIDTH; yTile<3; yTile++, rTile.yMin+=Y_WIDTH, rTile.yMax+=Y_WIDTH)
	{
		for(xTile=0, rTile.xMin=0, rTile.xMax=X_WIDTH; xTile<9; xTile++, rTile.xMin+=X_WIDTH, rTile.xMax+=X_WIDTH)
		{
			sTile.Printf(SG_T("Tile: %s%s"), x_sTile[xTile], y_sTile[yTile]);
			Process_Set_Text(sTile);

			sTile.Printf(SG_T("%s%s%s.dem"), Parameters("PATH")->asString(), x_sTile[xTile], y_sTile[yTile]);
			Tile_Load(sTile, rTile, pOut, rOut);
		}
	}

	//-----------------------------------------------------
	Parameters("GRID")->Set_Value(pOut);

	return( true );
}