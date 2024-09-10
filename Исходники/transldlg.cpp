void TranslDlg::OnCommand(wxCommandEvent& event)
{//=============================================
	#define N_PH_LIST  N_PHONEME_LIST

	void *vp;
	int translate_text = 0;
	char buf[1000];
	char phon_out[N_PH_LIST*2];
	int clause_tone;
	int clause_count;
	FILE *f;
	int  fd_temp;
	char fname_temp[100];
	static int n_ph_list;
	static PHONEME_LIST ph_list[N_PH_LIST+1];

	if(translator==NULL)
	{
		wxLogError(_T("Voice not set"));
		return;
	}

	option_phonemes = 0;

	switch(event.GetId())
	{
	case T_RULES:
	case MENU_SPEAK_RULES:
#ifdef PLATFORM_POSIX
		strcpy(fname_temp,"/tmp/espeakXXXXXX");
		if((fd_temp = mkstemp(fname_temp)) >= 0)
		{
			close(fd_temp);

			if((f = fopen(fname_temp,"w+")) != NULL)
			{
				f_trans = f;   // write translation rule trace to a temp file
			}
		}
#else
		strcpy(fname_temp,tmpnam(NULL));
		if((f = fopen(fname_temp,"w+")) != NULL)
		{
			f_trans = f;   // write translation rule trace to a temp file
		}
#endif
		t_phonetic->SetDefaultStyle(style_phonetic);
		translate_text = 2;
		break;

	case T_TRANSLATE:
	case MENU_SPEAK_TRANSLATE:
		t_phonetic->SetDefaultStyle(style_phonetic);
		translate_text = 1;
		break;

	case T_TRANSLATE_IPA:
	case MENU_SPEAK_IPA:
		t_phonetic->SetDefaultStyle(style_phonetic_large);

		translate_text = 3;
		break;

	case T_PROCESS:
	case MENU_SPEAK_TEXT:
		if(prosodycanvas == NULL)
		{
			myframe->OnProsody(event);
		}
		prosodycanvas->LayoutData(ph_list,n_ph_list);
		option_phoneme_events = 1;
		option_log_frames = 1;
		MakeWave2(ph_list,n_ph_list);
		option_log_frames = 0;
		break;
	}

	if(translate_text)
	{
		option_phonemes = translate_text;

		option_multibyte = espeakCHARS_AUTO;
		SpeakNextClause(NULL,NULL,2);  // stop speaking file

		strncpy0(buf,t_source->GetValue().mb_str(wxConvUTF8),sizeof(buf));
		phon_out[0] = 0;
		n_ph_list = 0;
		clause_count = 0;

		vp = buf;
		InitText(0);
		while((vp != NULL) && (n_ph_list < N_PH_LIST))
		{
			vp = TranslateClause(translator,NULL,vp,&clause_tone,NULL);
			CalcPitches(translator,clause_tone);
			CalcLengths(translator);

			GetTranslatedPhonemeString(translator->phon_out,sizeof(translator->phon_out));
			if(clause_count++ > 0)
				strcat(phon_out," ||");
			strcat(phon_out,translator->phon_out);
			t_phonetic->SetValue(wxString(translator->phon_out,wxConvUTF8));

			if((n_ph_list + n_phoneme_list) >= N_PH_LIST)
			{
				n_phoneme_list = N_PH_LIST - n_ph_list - n_phoneme_list;
			}

			memcpy(&ph_list[n_ph_list],phoneme_list,sizeof(PHONEME_LIST)*n_phoneme_list);
			n_ph_list += n_phoneme_list;
		}

		t_phonetic->Clear();
		if(option_phonemes == 2)
		{
			option_phonemes=0;
			rewind(f_trans);
			while(fgets(buf,sizeof(buf),f_trans) != NULL)
			{
				t_phonetic->AppendText(wxString(buf,wxConvUTF8));
			}
			t_phonetic->AppendText(_T("---\n"));
			if(f_trans != NULL)
				fclose(f_trans);
			remove(fname_temp);
		}
		t_phonetic->AppendText(wxString(phon_out,wxConvUTF8));
	}
}  // end of TranslDlg::OnCommand