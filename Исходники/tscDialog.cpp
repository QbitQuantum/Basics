//############################### CODE ######################################
//write an RDP file with settings stored in Registry
void writeRDP() {
    FILE  *pFile=NULL;
    TCHAR *filename = L"\\Windows\\default.rdp";

    byte buffer[2];
    buffer[0]=0xFF;
    buffer[1]=0xFE;

    TCHAR szTemp[MAX_PATH*2];
    size_t str_length = 0;

    TCHAR sDesktopWidth[10];
    TCHAR sDesktopHeight[10];
    _ultow(iDesktopWidth, sDesktopWidth, 10);
    _ultow(iDesktopHeight, sDesktopHeight, 10);

    pFile = _wfopen(filename, L"w+b");
    if(pFile != NULL)
    {
        fwrite(buffer, 2, 1, pFile);
        int c=1;
        do {
            //extra processing
#if _WIN32_WCE == 0x420
            //PPC2003 does not support UserName etc...
            if(wcsstr(rdpLines[c].line, L"ServerName")!=NULL)
                wsprintf(szTemp, rdpLines[c].line, myDlgItems[0].szValue);	//at idx 0 we have the servername in myDlgItems[]
#else
            if(wcsstr(rdpLines[c].line, L"UserName")!=NULL)
                wsprintf(szTemp, rdpLines[c].line, myDlgItems[1].szValue);
            else if(wcsstr(rdpLines[c].line, L"Domain")!=NULL)
                wsprintf(szTemp, rdpLines[c].line, myDlgItems[3].szValue);
            else if(wcsstr(rdpLines[c].line, L"ServerName")!=NULL)
                wsprintf(szTemp, rdpLines[c].line, myDlgItems[0].szValue);
            else if(wcsstr(rdpLines[c].line, L"SavePassword")!=NULL)
                wsprintf(szTemp, rdpLines[c].line, myDlgItems[4].szValue);
#endif
            else if(wcsstr(rdpLines[c].line, L"EnableClipboardRedirection")!=NULL)
                if(g_bEnableClipboardRedirection)
                    wsprintf(szTemp, rdpLines[c].line, L"1");
                else
                    wsprintf(szTemp, rdpLines[c].line, L"0");

            else if(wcsstr(rdpLines[c].line, L"DesktopHeight")!=NULL)

                if(g_bUseFitToScreen)   //3=FullScreen or 1=normal
                    wsprintf(szTemp, rdpLines[c].line, sScreenHeight /* L"320" */);
                else
                    wsprintf(szTemp, rdpLines[c].line, sDesktopHeight);// L"640");

            else if(wcsstr(rdpLines[c].line, L"DesktopWidth")!=NULL)

                if(g_bUseFitToScreen)   //3=FullScreen or 1=normal
                    wsprintf(szTemp, rdpLines[c].line, sScreenWidth /* L"240" */);
                else
                    wsprintf(szTemp, rdpLines[c].line, sDesktopWidth);// L"480");

            else if(wcsstr(rdpLines[c].line, L"ScreenStyle")!=NULL) {
                //0=no fullscreen + no fit, 1= fit to screen+no fullscreen, 2=fullscreen+no fit, 3=fit+fullscreen
                if(g_bUseFullscreen && g_bUseFitToScreen)
                    wsprintf(szTemp, rdpLines[c].line, L"3");
                else if (!g_bUseFullscreen && !g_bUseFitToScreen)
                    wsprintf(szTemp, rdpLines[c].line, L"0");
                else if (!g_bUseFullscreen && g_bUseFitToScreen)
                    wsprintf(szTemp, rdpLines[c].line, L"1");
                else if (g_bUseFullscreen && !g_bUseFitToScreen)
                    wsprintf(szTemp, rdpLines[c].line, L"2");
                else
                    wsprintf(szTemp, rdpLines[c].line, L"0");
            }

            else if(wcsstr(rdpLines[c].line, L"ColorDepthID")!=NULL) {
                wsprintf(szTemp, rdpLines[c].line, dwColorDepth);  //3=HighColor(16Bit) or 1=(8Bit) color
            }

            else if(wcsstr(rdpLines[c].line, L"EnableDriveRedirection")!=NULL) {
                wsprintf(szTemp, rdpLines[c].line, dwEnableDriveRedirection);  //0=no redirection to host (default), 1=EnableDriveRedirection
            }

            else if(wcsstr(rdpLines[c].line, L"AudioRedirectionMode")!=NULL) {
                wsprintf(szTemp, rdpLines[c].line, dwAudioRedirectionMode);  //0=Redirect sounds to the client,
                //1=Play sounds at the remote computer,
                //2=Disable sound redirection; do not play sounds at the server
            }
            else
                wsprintf(szTemp, rdpLines[c].line, L"");

            //write line by line
            str_length = wcslen(szTemp) * sizeof(TCHAR); //unicode!

            fwrite(szTemp , str_length, 1, pFile);
            DEBUGMSG(1, (L"write: '%s'\n", szTemp));

            c++;
        } while( rdpLines[c].line != NULL );
        fclose(pFile);
        DEBUGMSG(1, (L"\nFile write complete\n"));
    }
    //CryptProtectData
}