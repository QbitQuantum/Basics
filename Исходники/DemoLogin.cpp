void imsdkDemoLogin::Notify(TNotifyUI& msg) {
    if (msg.sType == _T("click")) {
        if (msg.pSender == m_pCloseBtn) {
            PostQuitMessage(0);
            return;
        }
        if (msg.pSender == m_pLoginBtn) {
            CEditUI* pEditServer = static_cast<CEditUI*>(m_pm.FindControl(_T("editServer")));
            CEditUI* pEditAccount = static_cast<CEditUI*>(m_pm.FindControl(_T("editAccount")));
            CEditUI* pEditPassword = static_cast<CEditUI*>(m_pm.FindControl(_T("editPassword")));
            std::string server = getString(pEditServer->GetText().GetData());
            std::string account = getString(pEditAccount->GetText().GetData());
            std::string password = getString(pEditPassword->GetText().GetData());
            gClientDemo.login(server, account, password, std::bind(&imsdkDemoLogin::onLoginCb, this, std::placeholders::_1));
            //Close(7);
        }
        if (msg.pSender == m_pSignCodeBtn) {
            CEditUI* pEditServer = static_cast<CEditUI*>(m_pm.FindControl(_T("signServer")));
            CEditUI* pEditPhone = static_cast<CEditUI*>(m_pm.FindControl(_T("signPhone")));
            std::string server = getString(pEditServer->GetText().GetData());
            std::string phone = getString(pEditPhone->GetText().GetData());

            gClientDemo.getRegCode(server, phone);
            m_secGetSignCode = 30;
            m_pSignCodeBtn->SetEnabled(false);
            std::string strText = std::to_string(m_secGetSignCode) + "s后重试";
            auto strT = getWString(strText.c_str());
            m_pSignCodeBtn->SetText(strT.c_str());
            ::SetTimer(GetHWND(), 7, 1000, NULL);
        }
        if (msg.pSender == m_pSignUpBtn) {
            CEditUI* pEditAccount = static_cast<CEditUI*>(m_pm.FindControl(_T("signAccount")));
            CEditUI* pEditPassword = static_cast<CEditUI*>(m_pm.FindControl(_T("signPassword")));
            CEditUI* pEditSignCode = static_cast<CEditUI*>(m_pm.FindControl(_T("signCode")));
            std::string account = getString(pEditAccount->GetText().GetData());
            std::string password = getString(pEditPassword->GetText().GetData());
            std::string signcode = getString(pEditSignCode->GetText().GetData());
            gClientDemo.reg(account, password, signcode);
        }
    }
    else if (msg.sType == _T("selectchanged")) {
        CDuiString name = msg.pSender->GetName();
        CTabLayoutUI* pControl = static_cast<CTabLayoutUI*>(m_pm.FindControl(_T("login")));
        if (name == _T("optLogin")){
            CEditUI* pEditAccount = static_cast<CEditUI*>(m_pm.FindControl(_T("editAccount")));
            CEditUI* pEditPassword = static_cast<CEditUI*>(m_pm.FindControl(_T("editPassword")));
            pEditAccount->SetText(_T("手机号"));
            pEditPassword->SetText(_T("密码"));
            pControl->SelectItem(0);
        }
        else if (name == _T("optSignUp")) {
            CEditUI* pEditPhone = static_cast<CEditUI*>(m_pm.FindControl(_T("signPhone")));
            CEditUI* pEditAccount = static_cast<CEditUI*>(m_pm.FindControl(_T("signAccount")));
            CEditUI* pEditPassword = static_cast<CEditUI*>(m_pm.FindControl(_T("signPassword")));
            CEditUI* pEditSignCode = static_cast<CEditUI*>(m_pm.FindControl(_T("signCode")));
            pEditPhone->SetText(_T("手机号"));
            pEditAccount->SetText(_T("用户名"));
            pEditPassword->SetText(_T("密码"));
            pEditSignCode->SetText(_T("验证码"));

            pControl->SelectItem(1);
        }
    }
    else if (msg.sType == _T("return"))
    {
        // Enter键注册、登录
        CTabLayoutUI* pTab = static_cast<CTabLayoutUI*>(m_pm.FindControl(_T("login")));
        if (0 == pTab->GetCurSel()){
            //
            CEditUI* pEditServer = static_cast<CEditUI*>(m_pm.FindControl(_T("editServer")));
            CEditUI* pEditAccount = static_cast<CEditUI*>(m_pm.FindControl(_T("editAccount")));
            CEditUI* pEditPassword = static_cast<CEditUI*>(m_pm.FindControl(_T("editPassword")));
            if (pEditPassword->IsFocused())
            {
                std::string server = getString(pEditServer->GetText().GetData());
                std::string account = getString(pEditAccount->GetText().GetData());
                std::string password = getString(pEditPassword->GetText().GetData());
                gClientDemo.login(server, account, password, std::bind(&imsdkDemoLogin::onLoginCb, this, std::placeholders::_1));
            }
            if (pEditAccount->IsFocused())
            {
                pEditPassword->SetFocus();
            }
        }
        else
        {
            CEditUI* pEditAccount = static_cast<CEditUI*>(m_pm.FindControl(_T("signAccount")));
            CEditUI* pEditPassword = static_cast<CEditUI*>(m_pm.FindControl(_T("signPassword")));
            CEditUI* pEditSignCode = static_cast<CEditUI*>(m_pm.FindControl(_T("signCode")));
            std::string account = getString(pEditAccount->GetText().GetData());
            std::string password = getString(pEditPassword->GetText().GetData());
            std::string signcode = getString(pEditSignCode->GetText().GetData());
            gClientDemo.reg(account, password, signcode);
        }
    }
}