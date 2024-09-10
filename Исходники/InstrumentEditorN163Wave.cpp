void CInstrumentEditorN163Wave::PopulateWaveBox()		// // //
{
	int Width = m_pInstrument->GetWaveSize();

	CBitmap Waveforms;
	char WaveBits[CInstrumentN163::MAX_WAVE_COUNT][CInstrumentN163::MAX_WAVE_SIZE * 2];
	for (int i = 0; i < CInstrumentN163::MAX_WAVE_COUNT; i++)
		CreateWaveImage(WaveBits[i], i);
	Waveforms.CreateBitmap(Width, 16, 1, 1, NULL);

	m_WaveImage.DeleteImageList();
	m_WaveImage.Create(Width, 16, ILC_COLOR8, 0, CInstrumentN163::MAX_WAVE_COUNT);
	if (Width & 16) Width += 16 - Width % 16; // padding
	for (int i = 0; i < CInstrumentN163::MAX_WAVE_COUNT; i++) {
		Waveforms.SetBitmapBits(Width * 2, WaveBits[i]);
		m_WaveImage.Add(&Waveforms, &Waveforms);
	}
	Waveforms.DeleteObject();
	m_pWaveListCtrl->SetImageList(&m_WaveImage, LVSIL_SMALL);

	m_pWaveListCtrl->DeleteAllItems();
	for (int i = 0; i < m_pInstrument->GetWaveCount(); /*CInstrumentN163::MAX_WAVE_COUNT;*/ i++) {
		CString hex;
		hex.Format(_T("%X"), i);
		m_pWaveListCtrl->InsertItem(i, _T(""), i);
		m_pWaveListCtrl->SetItemText(i, 1, hex);
	}
	SelectWave(m_iWaveIndex);
}