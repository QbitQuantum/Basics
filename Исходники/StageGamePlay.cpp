void CStageGamePlay::Run()
{
    CUIManager* pUIManager = CUIManager::getSingleton();

    if (_pGameState->IsRestartGame() && m_bSendRestart == false)
    {
        DWORD	tmpTime			= _pTimer->GetHighPrecisionTimer().GetMilliseconds();
        DWORD	IntervalTime	= 0;
        int		iShowTime		= 0;
        CTString strtime;

        IntervalTime = tmpTime - pUIManager->GetSystemMenu()->GetRestartTime();
        iShowTime = m_dwRemainTime - (IntervalTime / 1000);

        strtime.PrintF(_S(4201,"%d 초 후에 접속종료됩니다."), iShowTime);

        if (m_dwRemainTime > 0)
            _UIAutoHelp->SetGMNotice(strtime);

        if (IntervalTime >= (m_dwRemainTime * 1000)) // 15초  15000 -> 10초로 수정
        {   // 재시작
            _UIAutoHelp->ClearGMNNotice();
            pUIManager->GetSystemMenu()->ResetRestartTime();
            pUIManager->GetSystemMenu()->ReStartNow();
            m_bSendRestart = true;
        }
    }
}