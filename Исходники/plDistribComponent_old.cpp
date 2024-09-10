    BOOL DlgProc(TimeValue t, IParamMap2 *map, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        HWND cbox = NULL;
        switch (msg)
        {

        case WM_INITDIALOG:
            cbox = GetDlgItem(hWnd, IDC_COMP_DISTRIB_PROBCOLORCHAN);
            int i;
            for( i = 0; i < kNumColorChanOptions; i++ )
            {
                SendMessage(cbox, CB_ADDSTRING, 0, (LPARAM)kProbColorChanStrings[i].fString);
            }
            SendMessage(cbox, CB_SETCURSEL, map->GetParamBlock()->GetInt(plDistribComponent_old::kProbColorChan), 0);

            ISetupScaleLock(map, true);

            return TRUE;
        case WM_COMMAND:
            if( (HIWORD(wParam) == BN_CLICKED) && (LOWORD(wParam) == IDC_DISTRIB_CLEAR) )
            {
                plDistribComponent_old* dc = (plDistribComponent_old*)map->GetParamBlock()->GetOwner();
                dc->Clear();

                return TRUE;
            }
            switch( LOWORD(wParam) )
            {
                case IDC_COMP_DISTRIB_PROBCOLORCHAN:
                {
                    map->GetParamBlock()->SetValue(plDistribComponent_old::kProbColorChan, t, SendMessage(GetDlgItem(hWnd, LOWORD(wParam)), CB_GETCURSEL, 0, 0));
                    return TRUE;
                }
                break;

                case IDC_COMP_DISTRIB_FADEINACTIVE:
                case IDC_COMP_DISTRIB_FADEINTRAN:
                case IDC_COMP_DISTRIB_FADEINOPAQ:
                case IDC_COMP_DISTRIB_FADEOUTTRAN:
                case IDC_COMP_DISTRIB_FADEOUTOPAQ:
                case IDC_COMP_DISTRIB_FADEINTRAN_SPIN:
                case IDC_COMP_DISTRIB_FADEINOPAQ_SPIN:
                case IDC_COMP_DISTRIB_FADEOUTTRAN_SPIN:
                case IDC_COMP_DISTRIB_FADEOUTOPAQ_SPIN:
                {
                    plDistribComponent_old* dc = (plDistribComponent_old*)map->GetParamBlock()->GetOwner();
                    Box3 fade;
                    if( !dc->IValidateFade(fade) )
                    {
                        map->GetParamBlock()->SetValue(plDistribComponent_old::kFadeInTran, t, fade.Min()[0]);
                        map->GetParamBlock()->SetValue(plDistribComponent_old::kFadeInOpaq, t, fade.Min()[1]);
                        map->GetParamBlock()->SetValue(plDistribComponent_old::kFadeOutTran, t, fade.Max()[0]);
                        map->GetParamBlock()->SetValue(plDistribComponent_old::kFadeOutOpaq, t, fade.Max()[1]);

                        map->Invalidate(plDistribComponent_old::kFadeInTran);
                        map->Invalidate(plDistribComponent_old::kFadeInOpaq);
                        map->Invalidate(plDistribComponent_old::kFadeOutTran);
                        map->Invalidate(plDistribComponent_old::kFadeOutOpaq);
                        ShowWindow(hWnd, SW_HIDE);
                        ShowWindow(hWnd, SW_SHOW);
                    }
                    return TRUE;
                }
                break;
#if 0 // Obsolete, now kRndPosRadius is percentage of kSpacing
                case IDC_COMP_DISTRIB_RNDPOSRADIUS:
                case IDC_COMP_DISTRIB_RNDPOSRADIUS_SPIN:
                {
                    IParamBlock2 *pb = map->GetParamBlock();

                    float maxRndPosRad = pb->GetFloat(plDistribComponent_old::kSpacing) * 0.5f;
                    if( pb->GetFloat(plDistribComponent_old::kRndPosRadius) > maxRndPosRad )
                    {
                        pb->SetValue(plDistribComponent_old::kRndPosRadius, t, maxRndPosRad);
                        map->Invalidate(plDistribComponent_old::kRndPosRadius);
                        ShowWindow(hWnd, SW_HIDE);
                        ShowWindow(hWnd, SW_SHOW);
                    }
                    
                    return TRUE;
                }
#endif // Obsolete, now kRndPosRadius is percentage of kSpacing
                case IDC_COMP_DISTRIB_LOCKSCALEXY:
                case IDC_COMP_DISTRIB_LOCKSCALEXYZ:
                    ISetupScaleLock(map, false);
                    return TRUE;

            }
            break;
        }

        return false;
    }