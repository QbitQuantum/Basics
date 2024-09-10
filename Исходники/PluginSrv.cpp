BOOL WINAPI PlugServerCommand(LPVOID pInst, CESERVER_REQ* pIn, CESERVER_REQ* &ppReply, DWORD &pcbReplySize, DWORD &pcbMaxReplySize, LPARAM lParam)
{
    BOOL lbRc = FALSE;
    BOOL fSuccess = FALSE;
    MSectionThread SCT(csTabs);

    if (pIn->hdr.cbSize < sizeof(CESERVER_REQ_HDR) || /*in.nSize < cbRead ||*/ pIn->hdr.nVersion != CESERVER_REQ_VER)
    {
        gpPlugServer->BreakConnection(pInst);
        return FALSE;
    }

    UINT nDataSize = pIn->hdr.cbSize - sizeof(CESERVER_REQ_HDR);

    // Все данные из пайпа получены, обрабатываем команду и возвращаем (если нужно) результат
    switch (pIn->hdr.nCmd)
    {
    case CMD_LANGCHANGE:
    {
        _ASSERTE(nDataSize>=4); //-V112
        // LayoutName: "00000409", "00010409", ...
        // А HKL от него отличается, так что передаем DWORD
        // HKL в x64 выглядит как: "0x0000000000020409", "0xFFFFFFFFF0010409"
        DWORD hkl = pIn->dwData[0];
        DWORD dwLastError = 0;
        HKL hkl1 = NULL, hkl2 = NULL;

        if (hkl)
        {
            WCHAR szLoc[10];
            _wsprintf(szLoc, SKIPLEN(countof(szLoc)) L"%08x", hkl);
            hkl1 = LoadKeyboardLayout(szLoc, KLF_ACTIVATE|KLF_REORDER|KLF_SUBSTITUTE_OK|KLF_SETFORPROCESS);
            hkl2 = ActivateKeyboardLayout(hkl1, KLF_SETFORPROCESS|KLF_REORDER);

            if (!hkl2)
                dwLastError = GetLastError();
            else
                fSuccess = TRUE;
        }

        pcbReplySize = sizeof(CESERVER_REQ_HDR) + sizeof(DWORD)*2;
        if (ExecuteNewCmd(ppReply, pcbMaxReplySize, pIn->hdr.nCmd, pcbReplySize))
        {
            lbRc = TRUE;
            ppReply->dwData[0] = fSuccess;
            ppReply->dwData[1] = fSuccess ? ((DWORD)(LONG)(LONG_PTR)hkl2) : dwLastError;
        }

        break;
    } // CMD_LANGCHANGE

#if 0
    case CMD_DEFFONT:
    {
        // исключение - асинхронный, результат не требуется
        SetConsoleFontSizeTo(FarHwnd, 4, 6);
        MoveWindow(FarHwnd, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), 1); // чтобы убрать возможные полосы прокрутки...
        break;
    }
    CMD_DEFFONT
#endif

    case CMD_REQTABS:
    case CMD_SETWINDOW:
    {
        MSectionLock SC;
        SC.Lock(csTabs, FALSE, 1000);
        DWORD nSetWindowWait = (DWORD)-1;

        if (pIn->hdr.nCmd == CMD_SETWINDOW)
        {
            ResetEvent(ghSetWndSendTabsEvent);

            // Для FAR2 - сброс QSearch выполняется в том же макро, в котором актирируется окно
            if (gFarVersion.dwVerMajor == 1 && pIn->dwData[1])
            {
                // А вот для FAR1 - нужно шаманить
                Plugin()->ProcessCommand(CMD_CLOSEQSEARCH, TRUE/*bReqMainThread*/, pIn->dwData/*хоть и не нужно?*/);
            }

            // Пересылается 2 DWORD
            BOOL bCmdRc = Plugin()->ProcessCommand(pIn->hdr.nCmd, TRUE/*bReqMainThread*/, pIn->dwData);

            DEBUGSTRCMD(L"Plugin: PlugServerThreadCommand: CMD_SETWINDOW waiting...\n");

            WARNING("Почему для FAR1 не ждем? Есть возможность заблокироваться в 1.7 или что?");
            if ((gFarVersion.dwVerMajor >= 2) && bCmdRc)
            {
                DWORD nTimeout = 2000;
#ifdef _DEBUG
                if (IsDebuggerPresent()) nTimeout = 120000;
#endif

                nSetWindowWait = WaitForSingleObject(ghSetWndSendTabsEvent, nTimeout);
            }

            if (nSetWindowWait == WAIT_TIMEOUT)
            {
                gbForceSendTabs = TRUE;
                DEBUGSTRCMD(L"Plugin: PlugServerThreadCommand: CMD_SETWINDOW timeout !!!\n");
            }
            else
            {
                DEBUGSTRCMD(L"Plugin: PlugServerThreadCommand: CMD_SETWINDOW finished\n");
            }
        }

        if (gpTabs && (nSetWindowWait != WAIT_TIMEOUT))
        {
            //fSuccess = WriteFile(hPipe, gpTabs, gpTabs->hdr.cbSize, &cbWritten, NULL);
            pcbReplySize = gpTabs->hdr.cbSize;
            if (ExecuteNewCmd(ppReply, pcbMaxReplySize, pIn->hdr.nCmd, pcbReplySize))
            {
                memmove(ppReply->Data, gpTabs->Data, pcbReplySize - sizeof(ppReply->hdr));
                lbRc = TRUE;
            }
        }

        SC.Unlock();
        break;
    } // CMD_REQTABS, CMD_SETWINDOW

    case CMD_FARSETCHANGED:
    {
        // Установить переменные окружения
        // Плагин это получает в ответ на CECMD_RESOURCES, посланное в GUI при загрузке плагина
        _ASSERTE(nDataSize>=8);
        FAR_REQ_FARSETCHANGED *pFarSet = (FAR_REQ_FARSETCHANGED*)pIn->Data;

        cmd_FarSetChanged(pFarSet);

        pcbReplySize = sizeof(CESERVER_REQ_HDR) + sizeof(DWORD);
        if (ExecuteNewCmd(ppReply, pcbMaxReplySize, pIn->hdr.nCmd, pcbReplySize))
        {
            lbRc = TRUE;
            ppReply->dwData[0] = TRUE;
        }

        //_ASSERTE(nDataSize<sizeof(gsMonitorEnvVar));
        //gbMonitorEnvVar = false;
        //// Плагин FarCall "нарушает" COMSPEC (копирует содержимое запускаемого процесса)
        //bool lbOk = false;

        //if (nDataSize<sizeof(gsMonitorEnvVar))
        //{
        //	memcpy(gsMonitorEnvVar, pszName, nDataSize);
        //	lbOk = true;
        //}

        //UpdateEnvVar(pszName);
        ////while (*pszName && *pszValue) {
        ////	const wchar_t* pszChanged = pszValue;
        ////	// Для ConEmuOutput == AUTO выбирается по версии ФАРа
        ////	if (!lstrcmpi(pszName, L"ConEmuOutput") && !lstrcmp(pszChanged, L"AUTO")) {
        ////		if (gFarVersion.dwVerMajor==1)
        ////			pszChanged = L"ANSI";
        ////		else
        ////			pszChanged = L"UNICODE";
        ////	}
        ////	// Если в pszValue пустая строка - удаление переменной
        ////	SetEnvironmentVariableW(pszName, (*pszChanged != 0) ? pszChanged : NULL);
        ////	//
        ////	pszName = pszValue + lstrlenW(pszValue) + 1;
        ////	if (*pszName == 0) break;
        ////	pszValue = pszName + lstrlenW(pszName) + 1;
        ////}
        //gbMonitorEnvVar = lbOk;

        break;
    } // CMD_FARSETCHANGED

    case CMD_DRAGFROM:
    {
#ifdef _DEBUG
        BOOL  *pbClickNeed = (BOOL*)pIn->Data;
        COORD *crMouse = (COORD *)(pbClickNeed+1);
#endif

        Plugin()->ProcessCommand(CMD_LEFTCLKSYNC, TRUE/*bReqMainThread*/, pIn->Data);
        CESERVER_REQ* pCmdRet = NULL;
        Plugin()->ProcessCommand(pIn->hdr.nCmd, TRUE/*bReqMainThread*/, pIn->Data, &pCmdRet);

        if (pCmdRet)
        {
            //fSuccess = WriteFile(hPipe, pCmdRet, pCmdRet->hdr.cbSize, &cbWritten, NULL);
            pcbReplySize = pCmdRet->hdr.cbSize;
            if (ExecuteNewCmd(ppReply, pcbMaxReplySize, pIn->hdr.nCmd, pcbReplySize))
            {
                lbRc = TRUE;
                memmove(ppReply->Data, pCmdRet->Data, pCmdRet->hdr.cbSize - sizeof(ppReply->hdr));
            }
            Free(pCmdRet);
        }

        break;
    } // CMD_DRAGFROM

    case CMD_EMENU:
    {
        COORD *crMouse = (COORD *)pIn->Data;
#ifdef _DEBUG
        const wchar_t *pszUserMacro = (wchar_t*)(crMouse+1);
#endif
        DWORD ClickArg[2] = {(DWORD)TRUE, (DWORD)MAKELONG(crMouse->X, crMouse->Y)};

        // Выделить файл под курсором
        DEBUGSTRMENU(L"\n*** ServerThreadCommand->ProcessCommand(CMD_LEFTCLKSYNC) begin\n");
        BOOL lb1 = Plugin()->ProcessCommand(CMD_LEFTCLKSYNC, TRUE/*bReqMainThread*/, ClickArg/*pIn->Data*/);
        DEBUGSTRMENU(L"\n*** ServerThreadCommand->ProcessCommand(CMD_LEFTCLKSYNC) done\n");

        // А теперь, собственно вызовем меню
        DEBUGSTRMENU(L"\n*** ServerThreadCommand->ProcessCommand(CMD_EMENU) begin\n");
        BOOL lb2 = Plugin()->ProcessCommand(pIn->hdr.nCmd, TRUE/*bReqMainThread*/, pIn->Data);
        DEBUGSTRMENU(L"\n*** ServerThreadCommand->ProcessCommand(CMD_EMENU) done\n");

        pcbReplySize = sizeof(CESERVER_REQ_HDR) + sizeof(DWORD)*2;
        if (ExecuteNewCmd(ppReply, pcbMaxReplySize, pIn->hdr.nCmd, pcbReplySize))
        {
            lbRc = TRUE;
            ppReply->dwData[0] = lb1;
            ppReply->dwData[1] = lb1;
        }

        break;
    } // CMD_EMENU

    case CMD_ACTIVEWNDTYPE:
    {
        int nWindowType = -1;
        //CESERVER_REQ Out;
        //ExecutePrepareCmd(&Out, CMD_ACTIVEWNDTYPE, sizeof(CESERVER_REQ_HDR)+sizeof(DWORD));

        if (gFarVersion.dwVerMajor>=2)
            nWindowType = Plugin()->GetActiveWindowType();

        //fSuccess = WriteFile(hPipe, &Out, Out.hdr.cbSize, &cbWritten, NULL);

        pcbReplySize = sizeof(CESERVER_REQ_HDR) + sizeof(DWORD);
        if (ExecuteNewCmd(ppReply, pcbMaxReplySize, pIn->hdr.nCmd, pcbReplySize))
        {
            lbRc = TRUE;
            ppReply->dwData[0] = nDataSize;
        }

        break;
    } // CMD_ACTIVEWNDTYPE

    case CECMD_ATTACH2GUI:
    {
        BOOL bAttached = Plugin()->Attach2Gui();
        pcbReplySize = sizeof(CESERVER_REQ_HDR) + sizeof(DWORD);
        if (ExecuteNewCmd(ppReply, pcbMaxReplySize, pIn->hdr.nCmd, pcbReplySize))
        {
            lbRc = TRUE;
            ppReply->dwData[0] = bAttached;
        }
        break;
    } // CECMD_ATTACH2GUI

    default:
    {
        CESERVER_REQ* pCmdRet = NULL;
        BOOL lbCmd = Plugin()->ProcessCommand(pIn->hdr.nCmd, TRUE/*bReqMainThread*/, pIn->Data, &pCmdRet);

        if (pCmdRet)
        {
            //fSuccess = WriteFile(hPipe, pCmdRet, pCmdRet->hdr.cbSize, &cbWritten, NULL);
            pcbReplySize = pCmdRet->hdr.cbSize;
            if (ExecuteNewCmd(ppReply, pcbMaxReplySize, pIn->hdr.nCmd, pcbReplySize))
            {
                lbRc = TRUE;
                memmove(ppReply->Data, pCmdRet->Data, pCmdRet->hdr.cbSize - sizeof(ppReply->hdr));
            }
            Free(pCmdRet);
        }

    } // default
    } // switch (pIn->hdr.nCmd)

    return lbRc;
}