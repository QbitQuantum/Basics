void
CamStatusView::MessageReceived(BMessage *message)
{
	switch (message->what) {
		case B_OBSERVER_NOTICE_CHANGE:
		{
			int32 what;
			message->FindInt32("be:observe_change_what", &what);
			switch (what) {
				case kMsgControllerCaptureStarted:
					SetRecording(true);
					break;
				case kMsgControllerCaptureStopped:
					if (fPaused)
						fPaused = false;
					SetRecording(false);
					break;
				case kMsgControllerCapturePaused:
				case kMsgControllerCaptureResumed:
					TogglePause(what == kMsgControllerCapturePaused);
					break;
				case kMsgControllerEncodeStarted:
					fEncodingStringView->SetText(kEncodingString);
					((BCardLayout*)GetLayout())->SetVisibleItem(1);		
					break;
				case kMsgControllerEncodeProgress:
				{
					int32 totalFrames = 0;
					if (message->FindInt32("frames_total", &totalFrames) == B_OK) {
						fStatusBar->SetMaxValue(float(totalFrames));
					}
					int32 remainingFrames = 0;
					if (message->FindInt32("frames_remaining", &remainingFrames) == B_OK) {
						BString string = kEncodingString;
						string << " (" << remainingFrames << " frames)";
						fEncodingStringView->SetText(string);
					}
					fStatusBar->Update(1);
					break;
				}
				case kMsgControllerEncodeFinished:
				{
					((BCardLayout*)GetLayout())->SetVisibleItem((int32)0);
					break;
				}
				default:
					break;
			}
			break;
		}
		
		default:
			BView::MessageReceived(message);
			break;
	}
}