void EventMgr::RefreshCursor(int idx)
{
	Video *video = core->GetVideoDriver();
	if (idx&IE_CURSOR_GRAY) {
		video->SetMouseGrayed(true);
	} else {
		video->SetMouseGrayed(false);
	}
	idx &= IE_CURSOR_MASK;
	video->SetCursor( core->Cursors[idx], core->Cursors[idx ^ 1] );
}