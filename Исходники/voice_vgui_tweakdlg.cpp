void CVoiceVGUITweakDlg::Open()
{
	if(g_bTweakDlgOpen)
		return;
	
	g_bTweakDlgOpen = true;

	m_DlgWidth = ScreenWidth;
	m_DlgHeight = ScreenHeight;

	m_pVoiceTweak = gEngfuncs.pVoiceTweak;

	// Tell the engine to start voice tweak mode (pipe voice output right to speakers).
	m_pVoiceTweak->StartVoiceTweakMode();

	// Set our size.
	setPos((ScreenWidth - m_DlgWidth) / 2, (ScreenHeight - m_DlgHeight) / 2);
	setSize(m_DlgWidth, m_DlgHeight);

	int curY = ITEM_BORDER;
	m_MicVolume.Init(this, gHUD.m_TextMessage.BufferedLocaliseTextString("#Mic_Volume"), curY);
	m_MicVolume.SetValue(m_pVoiceTweak->GetControlFloat(MicrophoneVolume));
	curY = PanelBottom(&m_MicVolume.m_Label);

	m_SpeakerVolume.Init(this, gHUD.m_TextMessage.BufferedLocaliseTextString("#Speaker_Volume"), curY);
	m_SpeakerVolume.SetValue(m_pVoiceTweak->GetControlFloat(OtherSpeakerScale));
	curY = PanelBottom(&m_SpeakerVolume.m_Label);

	m_VoiceModEnable.setParent(this);
	m_VoiceModEnable.SetImages("gfx/vgui/checked.tga", "gfx/vgui/unchecked.tga");
	m_VoiceModEnable.SetText("Enable Voice In This Mod");
	m_VoiceModEnable.setPos(ITEM_BORDER, curY);
	m_VoiceModEnable.SetCheckboxLeft(false);
	m_VoiceModEnable.SetChecked(!!gEngfuncs.pfnGetCvarFloat("voice_modenable"));
	m_VoiceModEnable.SetHandler(this);

	// Setup the OK button.
	int buttonWidth, buttonHeight;
	m_Button_OK.setText(gHUD.m_TextMessage.BufferedLocaliseTextString("#Menu_OK"));
	m_Button_OK.getSize(buttonWidth, buttonHeight);
	m_Button_OK.setPos((m_DlgWidth - buttonWidth) / 2, m_DlgHeight - buttonHeight - 3);
	m_Button_OK.setParent(this);

	// Put the label on the top.
	m_Label.setBgColor(0, 0, 0, 255);
	m_Label.setFgColor(255,255,255,0);
	m_Label.setText(gHUD.m_TextMessage.BufferedLocaliseTextString("#Voice_Properties"));
	int labelWidth, labelHeight;
	m_Label.getSize(labelWidth, labelHeight);
	m_Label.setPos((m_DlgWidth - labelWidth) / 2, 5);
	m_Label.setParent(this);

	BaseClass::Open();
}