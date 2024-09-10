LRESULT CMainWindow::OnCommand(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    switch (LOWORD(wParam))
    {
        case IDM_HELPINFO:
        {
            HICON paintIcon = LoadIcon(hProgInstance, MAKEINTRESOURCE(IDI_APPICON));
            TCHAR infotitle[100];
            TCHAR infotext[200];
            LoadString(hProgInstance, IDS_INFOTITLE, infotitle, SIZEOF(infotitle));
            LoadString(hProgInstance, IDS_INFOTEXT, infotext, SIZEOF(infotext));
            ShellAbout(m_hWnd, infotitle, infotext, paintIcon);
            DeleteObject(paintIcon);
            break;
        }
        case IDM_HELPHELPTOPICS:
            HtmlHelp(m_hWnd, _T("help\\Paint.chm"), 0, 0);
            break;
        case IDM_FILEEXIT:
            SendMessage(WM_CLOSE, wParam, lParam);
            break;
        case IDM_FILENEW:
        {
            BOOL reset = TRUE;
            if (!imageModel.IsImageSaved())
            {
                TCHAR programname[20];
                TCHAR saveprompttext[100];
                TCHAR temptext[500];
                LoadString(hProgInstance, IDS_PROGRAMNAME, programname, SIZEOF(programname));
                LoadString(hProgInstance, IDS_SAVEPROMPTTEXT, saveprompttext, SIZEOF(saveprompttext));
                _stprintf(temptext, saveprompttext, filename);
                switch (MessageBox(temptext, programname, MB_YESNOCANCEL | MB_ICONQUESTION))
                {
                    case IDNO:
                        imageModel.imageSaved = TRUE; //TODO: move to ImageModel
                        break;
                    case IDYES:
                        saveImage(FALSE);
                        break;
                    case IDCANCEL:
                        reset = FALSE;
                        break;
                }
            }
            if (reset && imageModel.IsImageSaved()) //TODO: move to ImageModel
            {
                imageModel.Clear();
                imageModel.ClearHistory();
            }
            break;
        }
        case IDM_FILEOPEN:
            if (GetOpenFileName(&ofn) != 0)
            {
                HBITMAP bmNew = NULL;
                LoadDIBFromFile(&bmNew, ofn.lpstrFile, &fileTime, &fileSize, &fileHPPM, &fileVPPM);
                if (bmNew != NULL)
                {
                    UpdateApplicationProperties(bmNew, ofn.lpstrFileTitle, ofn.lpstrFileTitle);
                }
            }
            break;
        case IDM_FILESAVE:
            saveImage(TRUE);
            break;
        case IDM_FILESAVEAS:
            saveImage(FALSE);
            break;
        case IDM_FILEPAGESETUP:
            // DUMMY: Shows the dialog only, no functionality
            PAGESETUPDLG psd;
            ZeroMemory(&psd, sizeof(psd));
            psd.lStructSize = sizeof(psd);
            psd.hwndOwner = m_hWnd;
            PageSetupDlg(&psd);
            break;
        case IDM_FILEPRINT:
            // TODO: Test whether it actually works
            PRINTDLG pd;
            ZeroMemory(&pd, sizeof(pd));
            pd.lStructSize = sizeof(pd);
            pd.hwndOwner = m_hWnd;
            pd.hDevMode = NULL;  // freed by user
            pd.hDevNames = NULL;  // freed by user
            pd.Flags = PD_USEDEVMODECOPIESANDCOLLATE | PD_RETURNDC;
            pd.nCopies = 1;
            pd.nFromPage = 0xffff;
            pd.nToPage = 0xffff;
            pd.nMinPage = 1;
            pd.nMaxPage = 0xffff;
            if (PrintDlg(&pd) == TRUE)
            {
                BitBlt(pd.hDC, 0, 0, imageModel.GetWidth(), imageModel.GetHeight(), imageModel.GetDC(), 0, 0, SRCCOPY);
                DeleteDC(pd.hDC);
            }
            if (pd.hDevMode)
                GlobalFree(pd.hDevMode);
            if (pd.hDevNames)
                GlobalFree(pd.hDevNames);
            break;
        case IDM_FILEASWALLPAPERPLANE:
            RegistrySettings::SetWallpaper(filepathname, 1, 1);
            break;
        case IDM_FILEASWALLPAPERCENTERED:
            RegistrySettings::SetWallpaper(filepathname, 1, 0);
            break;
        case IDM_FILEASWALLPAPERSTRETCHED:
            RegistrySettings::SetWallpaper(filepathname, 2, 0);
            break;
        case IDM_EDITUNDO:
            imageModel.Undo();
            imageArea.Invalidate(FALSE);
            break;
        case IDM_EDITREDO:
            imageModel.Redo();
            imageArea.Invalidate(FALSE);
            break;
        case IDM_EDITCOPY:
            OpenClipboard();
            EmptyClipboard();
            SetClipboardData(CF_BITMAP, CopyImage(selectionModel.GetBitmap(), IMAGE_BITMAP, 0, 0, LR_COPYRETURNORG));
            CloseClipboard();
            break;
        case IDM_EDITCUT:
            /* Copy */
            SendMessage(WM_COMMAND, IDM_EDITCOPY, 0);
            /* Delete selection */
            SendMessage(WM_COMMAND, IDM_EDITDELETESELECTION, 0);
            break;
        case IDM_EDITPASTE:
            OpenClipboard();
            if (GetClipboardData(CF_BITMAP) != NULL)
            {
                InsertSelectionFromHBITMAP((HBITMAP) GetClipboardData(CF_BITMAP), m_hWnd);
            }
            CloseClipboard();
            break;
        case IDM_EDITDELETESELECTION:
        {
            /* remove selection window and already painted content using undo */
            imageModel.Undo();
            break;
        }
        case IDM_EDITSELECTALL:
        {
            HWND hToolbar = FindWindowEx(toolBoxContainer.m_hWnd, NULL, TOOLBARCLASSNAME, NULL);
            SendMessage(hToolbar, TB_CHECKBUTTON, ID_RECTSEL, MAKELPARAM(TRUE, 0));
            toolBoxContainer.SendMessage(WM_COMMAND, ID_RECTSEL);
            //TODO: do this properly
            startPaintingL(imageModel.GetDC(), 0, 0, paletteModel.GetFgColor(), paletteModel.GetBgColor());
            whilePaintingL(imageModel.GetDC(), imageModel.GetWidth(), imageModel.GetHeight(), paletteModel.GetFgColor(), paletteModel.GetBgColor());
            endPaintingL(imageModel.GetDC(), imageModel.GetWidth(), imageModel.GetHeight(), paletteModel.GetFgColor(), paletteModel.GetBgColor());
            break;
        }
        case IDM_EDITCOPYTO:
            if (GetSaveFileName(&ofn) != 0)
                SaveDIBToFile(selectionModel.GetBitmap(), ofn.lpstrFile, imageModel.GetDC(), NULL, NULL, fileHPPM, fileVPPM);
            break;
        case IDM_EDITPASTEFROM:
            if (GetOpenFileName(&ofn) != 0)
            {
                HBITMAP bmNew = NULL;
                LoadDIBFromFile(&bmNew, ofn.lpstrFile, &fileTime, &fileSize, &fileHPPM, &fileVPPM);
                if (bmNew != NULL)
                {
                    InsertSelectionFromHBITMAP(bmNew, m_hWnd);
                    DeleteObject(bmNew);
                }
            }
            break;
        case IDM_COLORSEDITPALETTE:
            if (ChooseColor(&choosecolor))
                paletteModel.SetFgColor(choosecolor.rgbResult);
            break;
        case IDM_COLORSMODERNPALETTE:
            paletteModel.SelectPalette(1);
            break;
        case IDM_COLORSOLDPALETTE:
            paletteModel.SelectPalette(2);
            break;
        case IDM_IMAGEINVERTCOLORS:
        {
            imageModel.InvertColors();
            break;
        }
        case IDM_IMAGEDELETEIMAGE:
            imageModel.CopyPrevious();
            Rect(imageModel.GetDC(), 0, 0, imageModel.GetWidth(), imageModel.GetHeight(), paletteModel.GetBgColor(), paletteModel.GetBgColor(), 0, TRUE);
            imageArea.Invalidate(FALSE);
            break;
        case IDM_IMAGEROTATEMIRROR:
            switch (mirrorRotateDlg())
            {
                case 1: /* flip horizontally */
                    if (selectionWindow.IsWindowVisible())
                        selectionModel.FlipHorizontally();
                    else
                        imageModel.FlipHorizontally();
                    break;
                case 2: /* flip vertically */
                    if (selectionWindow.IsWindowVisible())
                        selectionModel.FlipVertically();
                    else
                        imageModel.FlipVertically();
                    break;
                case 3: /* rotate 90 degrees */
                    break;
                case 4: /* rotate 180 degrees */
                    if (selectionWindow.IsWindowVisible())
                        selectionModel.RotateNTimes90Degrees(2);
                    else
                        imageModel.RotateNTimes90Degrees(2);
                    break;
                case 5: /* rotate 270 degrees */
                    break;
            }
            break;
        case IDM_IMAGEATTRIBUTES:
        {
            if (attributesDlg())
            {
                imageModel.Crop(widthSetInDlg, heightSetInDlg, 0, 0);
            }
            break;
        }
        case IDM_IMAGESTRETCHSKEW:
        {
            if (changeSizeDlg())
            {
                imageModel.StretchSkew(stretchSkew.percentage.x, stretchSkew.percentage.y,
                                       stretchSkew.angle.x, stretchSkew.angle.y);
            }
            break;
        }
        case IDM_IMAGEDRAWOPAQUE:
            toolsModel.SetBackgroundTransparent(!toolsModel.IsBackgroundTransparent());
            break;
        case IDM_IMAGECROP:
            imageModel.Insert((HBITMAP) CopyImage(selectionModel.GetBitmap(), IMAGE_BITMAP, 0, 0, LR_COPYRETURNORG));
            break;

        case IDM_VIEWTOOLBOX:
            toolBoxContainer.ShowWindow(toolBoxContainer.IsWindowVisible() ? SW_HIDE : SW_SHOW);
            alignChildrenToMainWindow();
            break;
        case IDM_VIEWCOLORPALETTE:
            paletteWindow.ShowWindow(paletteWindow.IsWindowVisible() ? SW_HIDE : SW_SHOW);
            alignChildrenToMainWindow();
            break;
        case IDM_VIEWSTATUSBAR:
            ::ShowWindow(hStatusBar, ::IsWindowVisible(hStatusBar) ? SW_HIDE : SW_SHOW);
            alignChildrenToMainWindow();
            break;
        case IDM_FORMATICONBAR:
            textEditWindow.ShowWindow(textEditWindow.IsWindowVisible() ? SW_HIDE : SW_SHOW);

        case IDM_VIEWSHOWGRID:
            showGrid = !showGrid;
            imageArea.Invalidate(FALSE);
            break;
        case IDM_VIEWSHOWMINIATURE:
            showMiniature = !showMiniature;
            miniature.ShowWindow(showMiniature ? SW_SHOW : SW_HIDE);
            break;

        case IDM_VIEWZOOM125:
            zoomTo(125, 0, 0);
            break;
        case IDM_VIEWZOOM25:
            zoomTo(250, 0, 0);
            break;
        case IDM_VIEWZOOM50:
            zoomTo(500, 0, 0);
            break;
        case IDM_VIEWZOOM100:
            zoomTo(1000, 0, 0);
            break;
        case IDM_VIEWZOOM200:
            zoomTo(2000, 0, 0);
            break;
        case IDM_VIEWZOOM400:
            zoomTo(4000, 0, 0);
            break;
        case IDM_VIEWZOOM800:
            zoomTo(8000, 0, 0);
            break;

        case IDM_VIEWFULLSCREEN:
            fullscreenWindow.ShowWindow(SW_SHOW);
            ShowWindow(SW_HIDE);
            break;
    }
    return 0;
}