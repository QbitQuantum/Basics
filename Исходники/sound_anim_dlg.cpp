void CSoundAnimDlg::updateScroll(uint pos, uint min, uint max)
{
	CScrollBar* scroll = (CScrollBar*) GetDlgItem(IDC_SOUND_ANIM_SCROLLBAR);

	scroll->SetScrollRange(min, max, FALSE);
	scroll->SetScrollPos(pos, TRUE);
}