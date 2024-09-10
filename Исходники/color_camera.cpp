	~CobColorCameraNode()
	{
		image_poll_server_.shutdown();
		color_camera_->Close();
	} 