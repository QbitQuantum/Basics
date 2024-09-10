//---------------------------------------------------------
CSG_String CLine_Dissolve::Statistics_Get_Name(const CSG_String &Type, const CSG_String &Name)
{
	CSG_String	s;

	switch( Parameters("STAT_NAMING")->asInt() )
	{
	default: s.Printf("%s_%s", Type.c_str(), Name.c_str());	break;
	case  1: s.Printf("%s_%s", Name.c_str(), Type.c_str());	break;
	case  2: s.Printf("%s"   , Name.c_str()              );	break;
	case  3: s.Printf("%s"   , Type.c_str()              );	break;
	}

	return( s );
}