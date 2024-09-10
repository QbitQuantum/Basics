void panTaskLogo::OnFilectrlFilePickerChanged( wxFileDirPickerEvent& event )
{
	c_pgvVisionImage->gvIMG_LoadImage(event.GetPath());
}