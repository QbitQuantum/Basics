void KinectStreamerApp::keyDown(KeyEvent event)
{
	if (event.getChar()==' ')
	{
		mSettings.reload();
	}
}