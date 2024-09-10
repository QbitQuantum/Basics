//*************************************************************************
void BeatDetectorApp::keyDown(KeyEvent event)
{
	switch(event.getChar())
	{
		case 'n':
			NextFile();
			break;
		case 'f':
			setFullScreen(!isFullScreen());
			break;
		case 'p':
			if(mTrack)
			{
				if(mTrack->isPlaying())
				{
					mTrack->stop();
				}
				else
				{
					mTrack->play();
				}
			}
			break;
	}
}