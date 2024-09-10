//---------------------------------------------------------
CSG_String CPolygonStatisticsFromPoints::Get_Field_Name(const CSG_String &Type, const CSG_String &Name)
{
	CSG_String	s;
	
	switch( Parameters("FIELD_NAME")->asInt() )
	{
	default:
	case 0:	s.Printf(SG_T("%s_%s"), Type.c_str(), Name.c_str());	break;
	case 1:	s.Printf(SG_T("%s_%s"), Name.c_str(), Type.c_str());	break;
	case 2:	s.Printf(SG_T("%s"   ), Name.c_str()              );	break;
	case 3:	s.Printf(SG_T("%s"   ), Type.c_str()              );	break;
	}

	return( s );
}