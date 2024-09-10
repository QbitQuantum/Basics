DWORD WINAPI ReadDILCANMsg(LPVOID pVoid)
{
    CPARAM_THREADPROC* pThreadParam = (CPARAM_THREADPROC*) pVoid;

    if (pThreadParam != NULL)
    {
        CReadCanMsg* pCurrObj = (CReadCanMsg*) pThreadParam->m_pBuffer;

        if (pCurrObj != NULL)
        {
            pThreadParam->m_unActionCode = INVOKE_FUNCTION; // Set default action
            // Create the action event. In this case this will be used solely for
            // thread exit procedure. The first entry will be used.
            pThreadParam->m_hActionEvent = pCurrObj->m_ahActionEvent[0];
            DWORD dwWaitRet;
            BYTE byHIndex;
            bool bLoopON = true;

            while (bLoopON)
            {
                dwWaitRet = WaitForMultipleObjects(pCurrObj->m_nEvents,
                                                   pCurrObj->m_ahActionEvent, FALSE, INFINITE);
                ///// TEMP : BEGIN
                DWORD dwLLimit = WAIT_OBJECT_0;
                DWORD dwULimit = WAIT_OBJECT_0 + pCurrObj->m_nEvents - 1;
                DWORD dwLLError = WAIT_ABANDONED_0;
                DWORD dwULError = WAIT_ABANDONED_0 + pCurrObj->m_nEvents - 1;

                if ((dwWaitRet >= dwLLimit) && (dwWaitRet <= dwULimit))
                {
                    switch (pThreadParam->m_unActionCode)
                    {
                        case INVOKE_FUNCTION:
                        {
                            //Get the handle's index and pass it
                            byHIndex = (BYTE)(dwWaitRet - WAIT_OBJECT_0);
                            HANDLE hHandleSet = pCurrObj->m_ahActionEvent[byHIndex];
                            BYTE byNodeIndex;

                            if( pCurrObj->m_omHandleToNodeMgrMap.Lookup(hHandleSet, byNodeIndex))
                            {
                                //vRetrieveDataFromBuffer to read from that buffer
                                pCurrObj->vRetrieveDataFromBuffer(byNodeIndex);
                            }

                            //BOOL Result = ResetEvent(hHandleSet);
                            ResetEvent(hHandleSet);
                        }
                        break;

                        case EXIT_THREAD:
                        {
                            bLoopON = false;
                        }
                        break;

                        case INACTION:
                        {
                            // Signal the owner
                            SetEvent(pThreadParam->m_hThread2Owner);
                            Sleep(0);
                            // Wait until owner signals back.
                            WaitForSingleObject(pThreadParam->m_hOwner2Thread, INFINITE);
                            // Signal the owner
                            SetEvent(pThreadParam->m_hThread2Owner);
                            Sleep(0);
                        }
                        break;

                        case CREATE_TIME_MAP:
                        default:
                            break;
                    }
                }
                else if ((dwWaitRet >= dwLLError) && (dwWaitRet <= dwULError))
                {
                    TRACE(_T("Abandoned... %X %d\n"), dwWaitRet, g_unCount++);
                }
                else if ( dwWaitRet == WAIT_TIMEOUT)
                {
                    TRACE(_T("ReadDILCANMsg->WAIT_TIMEOUT %d\n"), g_unCount++);
                }
                else if (dwWaitRet == WAIT_FAILED)
                {
                    TRACE(_T("WAIT_FAILED... %X %d\n"), GetLastError(), g_unCount++);
                }

                ///// TEMP : END
            }

            SetEvent(pThreadParam->hGetExitNotifyEvent());
        }
    }

    return 0;
}