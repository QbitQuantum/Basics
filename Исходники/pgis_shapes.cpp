//---------------------------------------------------------
bool CShapes_SRID_Update::On_Execute(void)
{
	if( !Get_Connection()->has_PostGIS() )	{	Error_Set(_TL("no PostGIS layer"));	return( false );	}

	//-----------------------------------------------------
	CSG_String	Select;
	CSG_Table	Table;

	Select.Printf(SG_T("f_table_name='%s'"), Parameters("TABLES")->asString());

	if( !Get_Connection()->Table_Load(Table, "geometry_columns", "*", Select) || Table.Get_Count() != 1 )
	{
		return( false );
	}

	Select.Printf(SG_T("SELECT UpdateGeometrySRID('%s', '%s', %d)"),
		Parameters("TABLES")->asString(),
		Table[0].asString("f_geometry_column"),
		Get_SRID()
	);

	//-----------------------------------------------------
	if( !Get_Connection()->Execute(Select) )
	{
		return( false );
	}

	return( true );
}