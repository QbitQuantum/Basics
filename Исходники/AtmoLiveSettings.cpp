ATMO_BOOL CAtmoLiveSettings::InitDialog(WPARAM wParam) 
{
        CAtmoConfig *config = m_pDynData->getAtmoConfig();
        char buffer[256];
        HWND hwndCtrl;

        hwndCtrl = this->getDlgItem(IDC_GDI_CAPURE_RATE);
        sprintf(buffer,"%d",config->getLiveView_GDI_FrameRate());
        Edit_SetText(hwndCtrl, buffer);
        Edit_LimitText(hwndCtrl,2);

        LoadDisplayList();

        hwndCtrl = getDlgItem(IDC_FILTERMODE);
        ComboBox_AddString(hwndCtrl, "No Filter");
        ComboBox_AddString(hwndCtrl, "Combined");
        ComboBox_AddString(hwndCtrl, "Percent");
        ComboBox_SetCurSel(hwndCtrl, (int)config->getLiveViewFilterMode());

        hwndCtrl = getDlgItem(IDC_WIDESCREEN);
        Button_SetCheck(hwndCtrl, config->getLiveView_WidescreenMode());

        SetupSliderControl(IDC_EdgeWeighting,1,30,config->getLiveView_EdgeWeighting(),5);
        SendMessage(getDlgItem(IDC_EdgeWeighting),TBM_SETPAGESIZE,0,2);
        sprintf(buffer,"Edge weighting [%d]",config->getLiveView_EdgeWeighting());
        SetStaticText(IDC_TXT_EDGEWEIGHTNING, buffer);

        SetupSliderControl(IDC_BrightCorrect,50,300,config->getLiveView_BrightCorrect(),15);
        SendMessage(getDlgItem(IDC_BrightCorrect),TBM_SETPAGESIZE,0,10);
        sprintf(buffer,"Brightness [%d%%]",config->getLiveView_BrightCorrect());
        SetStaticText(IDC_TXT_BRIGHTCORRECT, buffer);

        SetupSliderControl(IDC_DarknessLimit,0,10,config->getLiveView_DarknessLimit(),1);
        SendMessage(getDlgItem(IDC_DarknessLimit),TBM_SETPAGESIZE,0,1);
        sprintf(buffer,"Darkness Limit [%d]",config->getLiveView_DarknessLimit());
        SetStaticText(IDC_TXT_DARKNESSLIMIT, buffer);

        SetupSliderControl(IDC_HueWinSize,0,5,config->getLiveView_HueWinSize(),1);
        SendMessage(getDlgItem(IDC_HueWinSize),TBM_SETPAGESIZE,0,1);
        sprintf(buffer,"Hue windowing [%d]",config->getLiveView_HueWinSize());
        SetStaticText(IDC_TXT_HUEWINSIZE, buffer);

        SetupSliderControl(IDC_SatWinSize,0,5,config->getLiveView_SatWinSize(),1);
        SendMessage(getDlgItem(IDC_SatWinSize),TBM_SETPAGESIZE,0,1);
        sprintf(buffer,"Sat windowing [%d]",config->getLiveView_SatWinSize());
        SetStaticText(IDC_TXT_SATWINSIZE, buffer);

        SetupSliderControl(IDC_Filter_MeanLength,300,5000,config->getLiveViewFilter_MeanLength(),0);
        SendMessage(getDlgItem(IDC_Filter_MeanLength),TBM_SETPAGESIZE,0,100);
        sprintf(buffer,"Filter length [%d ms]",config->getLiveViewFilter_MeanLength());
        SetStaticText(IDC_TXT_Filter_MeanLength, buffer);

        SetupSliderControl(IDC_Filter_MeanThreshold,1,100,config->getLiveViewFilter_MeanThreshold(),0);
        SendMessage(getDlgItem(IDC_Filter_MeanThreshold),TBM_SETPAGESIZE,0,5);
        sprintf(buffer,"Filter threshold [%d%%]",config->getLiveViewFilter_MeanThreshold());
        SetStaticText(IDC_TXT_Filter_MeanThreshold, buffer);

        SetupSliderControl(IDC_Filter_PercentNew,1,100,config->getLiveViewFilter_PercentNew(),0);
        SendMessage(getDlgItem(IDC_Filter_PercentNew),TBM_SETPAGESIZE,0,5);
        sprintf(buffer,"Filter smoothness [%d%%]",config->getLiveViewFilter_PercentNew());
        SetStaticText(IDC_TXT_Filter_PercentNew, buffer);

        return ATMO_FALSE;
}