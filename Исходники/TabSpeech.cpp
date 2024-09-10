void CTabSpeech::UpdateVoiceFromCombo()
{
#if FS2_SPEECH
    ISpObjectToken* pToken = SpGetCurSelComboBoxToken( GetDlgItem(IDC_VOICE_COMBO )->GetSafeHwnd() );
	if(	pToken )
	{
		speech_set_voice(pToken);
	}
#endif
}