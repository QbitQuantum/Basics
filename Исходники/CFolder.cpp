void CFolder::mf_CFolder_0010(AnsiString arg_0)
{
	char local_00[1024];
	char local_01[16];
	m__unknown_003=arg_0;
	if (arg_0.Length()==0) {
		m__unknown_002="";
		return;
	}
	strcpy(local_00,arg_0.c_str());
	ny_htmlproc_5(local_00,local_01);
	m__unknown_002=local_01;
}