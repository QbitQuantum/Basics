BOOL OnNotify(HWND hDlg, LPNMHDR lpNMHdr)
{
    //DEBUGMESSAGE(("OnNotify"));

    UINT uiCode = lpNMHdr->code;
    switch (uiCode)
    {
    case PSN_APPLY:
        {
            DEBUGMESSAGE(("OnNotify - PSN_APPLY"));

            DocumentPropDialogData *data = 
                (DocumentPropDialogData *) GetWindowLongPtr(hDlg, DWL_USER);
            if (data == NULL) {
                DEBUGMESSAGE(("DocPropDlgProc - invalid internal data pointer"));
                return FALSE;
            }

            // which format combo should we use?
            LPTSTR format = NULL;
            if (IsDlgButtonChecked(hDlg, IDC_VECTOR_FORMAT_RADIOBOX) == BST_CHECKED)
            {
                INT sel = GetComboCurSel(GetDlgItem(hDlg, IDC_COMBO_VECTOR_FORMAT));
                format = strDuplicate(g_vectorFormats[sel].strName);
            }
            else if (IsDlgButtonChecked(hDlg, IDC_RASTER_FORMAT_RADIOBOX) == BST_CHECKED)
            {
                INT sel = GetComboCurSel(GetDlgItem(hDlg, IDC_COMBO_RASTER_FORMAT));
                format = strDuplicate(g_rasterFormats[sel].strName);
            }
            else
            {
                DEBUGMESSAGE(("DocPropDlgProc - unexpected condition"));
                return FALSE;
            }

            // get the output folder & validate it
            LPTSTR folder = NULL;
            if (!GetEditControlText(&folder, GetDlgItem(hDlg, IDC_OUTPUT_FOLDER))) {
                DEBUGMESSAGE(("DocPropDlgProc - could not get output folder text"));
                return FALSE;
            }
            if (!FolderExists(folder)) {
                ErrorMessage(hDlg, TEXT("Warning"),
                       TEXT("The given output directory does not exist!"));
                return FALSE;
            }

            // get the output filename & validate it
            LPTSTR filename = NULL;
            if (!GetEditControlText(&filename, GetDlgItem(hDlg, IDC_OUTPUT_FILENAME))) {
                DEBUGMESSAGE(("DocPropDlgProc - could not get output filename text"));
                return FALSE;
            }
            if (!IsValidFilename(filename)) {
                LPTSTR temp = strCat(TEXT("The given output filename is not valid!\n"),
                                     TEXT("It should not contain any of the '"),
                                     g_strFileNameForbiddenChars,
                                     TEXT("' characters."),
                                     NULL);
                ErrorMessage(hDlg, TEXT("Warning"), temp);
                strFree(temp);
                return FALSE;
            }

            // get the raster conv options
            LPTSTR rasteropt = NULL;
            if (!GetEditControlText(&rasteropt, GetDlgItem(hDlg, IDC_IMAGEMAGICK_OPTIONS))) {
                DEBUGMESSAGE(("DocPropDlgProc - could not get raster conv opt text"));
                return FALSE;
            }

            // get the postgen cmd
            LPTSTR postgen = NULL;
            if (!GetEditControlText(&postgen, GetDlgItem(hDlg, IDC_POSTGEN_CMD))) {
                DEBUGMESSAGE(("DocPropDlgProc - could not get postgen cmd text"));
                return FALSE;
            }

            // get override checkbox status
            BOOL override = 
                IsDlgButtonChecked(hDlg, IDC_OVERRIDE_CHECKBOX) == BST_CHECKED;

            // get crop checkbox
            BOOL crop = 
                IsDlgButtonChecked(hDlg, IDC_CROP_CHECKBOX) == BST_CHECKED;

            // get open-output checkbox
            BOOL openout = 
                IsDlgButtonChecked(hDlg, IDC_OPEN_VIEWER_CHECKBOX) == BST_CHECKED;

            // save all data in the EXTDEVMODE
            extdmSetPrivateData(data->m_pExtdmCurrent, 
                                format, filename, folder, rasteropt, postgen, 
                                override, openout, crop);

            // cleanup
            strFree(format);  
            strFree(filename);  
            strFree(folder);
            strFree(postgen);
            strFree(rasteropt);

            // call the _SET_RESULT callback
            PFNCOMPROPSHEET pfnComPropSheet = data->m_pfnComPropSheet;
            LONG lTemp = pfnComPropSheet(
                                        data->m_hComPropSheet, 
                                        CPSFUNC_SET_RESULT,
                                        (LPARAM) data->m_hPropSheetAdded,
                                        CPSUI_OK
                                        );

            return TRUE;
        }
        break;

    case PSN_RESET:
        break;

    case PSN_SETACTIVE:
        break;

    default:
        break;
    }

    return FALSE;
}