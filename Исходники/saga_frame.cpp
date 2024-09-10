//---------------------------------------------------------
void CSAGA_Frame::Set_Project_Name(wxString Project_Name)
{
	if( Project_Name.Length() > 0 )
	{
		SetTitle(wxString::Format(wxT("%s [%s]"), SAGA_CAPTION, Project_Name.c_str()));
	}
	else
	{
		SetTitle(SAGA_CAPTION);
	}
}