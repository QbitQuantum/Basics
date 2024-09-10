bool CPictureViewer::ShowImage(const std::string & filename, bool unscaled)
{
	dprintf(DEBUG_NORMAL, "CPictureViewer::Show Image: %s\n", filename.c_str());
	
  	if (m_CurrentPic_Buffer != NULL) 
	{
		free (m_CurrentPic_Buffer);
		m_CurrentPic_Buffer = NULL;
  	}

	// decode image
  	DecodeImage(filename, true, unscaled);
	
	// display next image
  	DisplayNextImage();
	
  	return true;
}