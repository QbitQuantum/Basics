//---------------------------------------------------------
CSG_String CSG_Module_Library::Get_Summary(bool bHTML)
{
	CSG_String	s;

	if( bHTML )
	{
		s.Printf(
			SG_T("%s: <b>%s</b><br>%s: <i>%s</i><br>%s: <i>%s</i><br>%s: <i>%s</i><hr>%s"),
			LNG("[CAP] Module Library")	, Get_Info(MLB_INFO_Name),
			LNG("[CAP] Author")			, Get_Info(MLB_INFO_Author),
			LNG("[CAP] Version")		, Get_Info(MLB_INFO_Version),
			LNG("[CAP] File")			, Get_File_Name().c_str(),
			Get_Info(MLB_INFO_Description)
		);

		s.Append(CSG_String::Format(SG_T("<hr><b>%s:<ul>"), LNG("[CAP] Modules")));

		for(int i=0; i<Get_Count(); i++)
		{
			s.Append(CSG_String::Format(SG_T("<li>%s</li>"), Get_Module(i)->Get_Name()));
		}

		s.Append(SG_T("</ul>"));

		s.Replace(SG_T("\n"), SG_T("<br>"));
	}
	else
	{
		s.Printf(
			SG_T("%s: %s\n%s: %s\n%s: %s\n%s: %s\n\n%s"),
			LNG("[CAP] Module Library")	, Get_Info(MLB_INFO_Name),
			LNG("[CAP] Author")			, Get_Info(MLB_INFO_Author),
			LNG("[CAP] Version")		, Get_Info(MLB_INFO_Version),
			LNG("[CAP] File")			, Get_File_Name().c_str(),
			Get_Info(MLB_INFO_Description)
		);

		s.Append(CSG_String::Format(SG_T("\n\n%s:\n"), LNG("[CAP] Modules")));

		for(int i=0; i<Get_Count(); i++)
		{
			s.Append(CSG_String::Format(SG_T("- %s\n"), Get_Module(i)->Get_Name()));
		}
	}

	return( s );
}