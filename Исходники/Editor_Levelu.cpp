BOOL CALLBACK MainDlgProcWeather(HWND hDlg, UINT msg, WPARAM wParam,
                                 LPARAM lParam)
{
    switch (msg) {
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDC_HUSTOTA:
        {
            char text[32];

            GetDlgItemText(hDlg, IDC_HUSTOTA, text, 32);
            p_LevelEnvironment->Weather[iIndex].uiDensity = atoi(text);
        }
        break;
        case IDC_INTEZITA:
        {
            char text[32];

            GetDlgItemText(hDlg, IDC_INTEZITA, text, 32);
            p_LevelEnvironment->Weather[iIndex].uiIntensity = atoi(text);
        }
        break;
        case IDC_ROZPTYL:
        {
            char text[32];

            GetDlgItemText(hDlg, IDC_ROZPTYL, text, 32);
            p_LevelEnvironment->Weather[iIndex].fmaxDivergence =
                (float) atof(text);
        }
        break;
        case IDC_VZDALENOST:
        {
            char text[32];

            GetDlgItemText(hDlg, IDC_VZDALENOST, text, 32);
            p_LevelEnvironment->Weather[iIndex].fDist = (float) atof(text);
        }
        break;
        case IDC_SKY:
        {
            char text[32];

            GetDlgItemText(hDlg, IDC_SKY, text, 32);
            p_LevelEnvironment->Weather[iIndex].fSky = (float) atof(text);
        }
        break;
        case IDC_WEATHER:
            if (HIWORD(wParam) == CBN_SELCHANGE)
                p_LevelEnvironment->Weather[iIndex].iWeather =
                    (char) SendMessage(GetDlgItem(hDlg, IDC_WEATHER), CB_GETCURSEL,
                                       0, 0);
            break;
        case IDCANCEL:
            EndDialog(hDlg, IDCANCEL);
            break;
        default:
            return FALSE;         // Neobslouzil message
        }
        break;
    case WM_NOTIFY:
    {
    }
    break;
    case WM_INITDIALOG:
        OnInitDialogWeather(hDlg);
        break;
    case WM_DESTROY:
        EndDialog(hDlg, IDCANCEL);
        break;
    default:
        return FALSE;             // Neobslouzil message
    }

    return TRUE;                  // Obslouzil message
}