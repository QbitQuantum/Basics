BOOL CALLBACK RecordingDlgProc(HWND hW, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
 switch(uMsg)
  {
   case WM_INITDIALOG:
    {
	 HWND hWC;
     CheckDlgButton(hW,IDC_REC_MODE1,RECORD_RECORDING_MODE==0);
     CheckDlgButton(hW,IDC_REC_MODE2,RECORD_RECORDING_MODE==1);
     hWC = GetDlgItem(hW,IDC_VIDEO_SIZE);
     ComboBox_ResetContent(hWC);
     ComboBox_AddString(hWC,"Full");
     ComboBox_AddString(hWC,"Half");
     ComboBox_AddString(hWC,"Quarter");
     ComboBox_SetCurSel(hWC,RECORD_VIDEO_SIZE);

     SetDlgItemInt(hW,IDC_REC_WIDTH,RECORD_RECORDING_WIDTH,FALSE);
     SetDlgItemInt(hW,IDC_REC_HEIGHT,RECORD_RECORDING_HEIGHT,FALSE);

     hWC = GetDlgItem(hW,IDC_FRAME_RATE);
     ComboBox_ResetContent(hWC);
     ComboBox_AddString(hWC,"1");
     ComboBox_AddString(hWC,"2");
     ComboBox_AddString(hWC,"3");
     ComboBox_AddString(hWC,"4");
     ComboBox_AddString(hWC,"5");
     ComboBox_AddString(hWC,"6");
     ComboBox_AddString(hWC,"7");
     ComboBox_AddString(hWC,"8");
     ComboBox_SetCurSel(hWC,RECORD_FRAME_RATE_SCALE);
     CheckDlgButton(hW,IDC_COMPRESSION1,RECORD_COMPRESSION_MODE==0);
     CheckDlgButton(hW,IDC_COMPRESSION2,RECORD_COMPRESSION_MODE==1);
     RefreshCodec(hW);
    }

   case WM_COMMAND:
    {
     switch(LOWORD(wParam))
      {
       case IDC_RECCFG:
	    {
		if(IsDlgButtonChecked(hW,IDC_COMPRESSION1))
			{
			BITMAPINFOHEADER bitmap = {40,640,480,1,16,0,640*480*2,2048,2048,0,0};
			if(!ICCompressorChoose(hW,ICMF_CHOOSE_DATARATE|ICMF_CHOOSE_KEYFRAME,&bitmap,NULL,&RECORD_COMPRESSION1,"16 bit Compression")) return TRUE;
			if(RECORD_COMPRESSION1.cbState>sizeof(RECORD_COMPRESSION_STATE1))
				{
				memset(&RECORD_COMPRESSION1,0,sizeof(RECORD_COMPRESSION1));
				memset(&RECORD_COMPRESSION_STATE1,0,sizeof(RECORD_COMPRESSION_STATE1));
				RECORD_COMPRESSION1.cbSize	= sizeof(RECORD_COMPRESSION1);
				}
			else
				{
				if(RECORD_COMPRESSION1.lpState!=RECORD_COMPRESSION_STATE1)
					memcpy(RECORD_COMPRESSION_STATE1,RECORD_COMPRESSION1.lpState,RECORD_COMPRESSION1.cbState);
				}
			RECORD_COMPRESSION1.lpState = RECORD_COMPRESSION_STATE1;
			}
		else
			{
			BITMAPINFOHEADER bitmap = {40,640,480,1,24,0,640*480*3,2048,2048,0,0};
			if(!ICCompressorChoose(hW,ICMF_CHOOSE_DATARATE|ICMF_CHOOSE_KEYFRAME,&bitmap,NULL,&RECORD_COMPRESSION2,"24 bit Compression")) return TRUE;
			if(RECORD_COMPRESSION2.cbState>sizeof(RECORD_COMPRESSION_STATE2))
				{
				memset(&RECORD_COMPRESSION2,0,sizeof(RECORD_COMPRESSION2));
				memset(&RECORD_COMPRESSION_STATE2,0,sizeof(RECORD_COMPRESSION_STATE2));
				RECORD_COMPRESSION2.cbSize	= sizeof(RECORD_COMPRESSION2);
				}
			else
				{
				if(RECORD_COMPRESSION2.lpState!=RECORD_COMPRESSION_STATE2)
					memcpy(RECORD_COMPRESSION_STATE2,RECORD_COMPRESSION2.lpState,RECORD_COMPRESSION2.cbState);
				}
			RECORD_COMPRESSION2.lpState = RECORD_COMPRESSION_STATE2;
			}
		RefreshCodec(hW);
		return TRUE;
		}
       case IDCANCEL: EndDialog(hW,FALSE);return TRUE;

       case IDOK:     
        {
		HWND hWC;
		if(IsDlgButtonChecked(hW,IDC_REC_MODE1))	RECORD_RECORDING_MODE = 0;
		else										RECORD_RECORDING_MODE = 1;
		hWC = GetDlgItem(hW,IDC_VIDEO_SIZE);
		RECORD_VIDEO_SIZE = ComboBox_GetCurSel(hWC);
		RECORD_RECORDING_WIDTH = GetDlgItemInt(hW,IDC_REC_WIDTH,NULL,FALSE);
		RECORD_RECORDING_HEIGHT = GetDlgItemInt(hW,IDC_REC_HEIGHT,NULL,FALSE);
		hWC = GetDlgItem(hW,IDC_FRAME_RATE);
		RECORD_FRAME_RATE_SCALE = ComboBox_GetCurSel(hWC);
		if(IsDlgButtonChecked(hW,IDC_COMPRESSION1))	RECORD_COMPRESSION_MODE = 0;
		else										RECORD_COMPRESSION_MODE = 1;
        EndDialog(hW,TRUE);
        return TRUE;
        }
      }
    }
  }
 return FALSE;
}