STDMETHODIMP CLogFormView::PreTranslateMessage(MSG *pMsg, BOOL *pbResult)
{
	CHECK_E_POINTER(pMsg);
	CHECK_E_POINTER(pbResult);

	if(pMsg->message == WM_KEYDOWN && pMsg->hwnd == GetDlgItem(IDC_EDIT2) && pMsg->wParam == VK_ESCAPE)
	{
		if (!m_editCmd.SetWindowText(L""))
			return HRESULT_FROM_WIN32(GetLastError());
	}

	if(pMsg->message == WM_KEYDOWN && pMsg->hwnd == GetDlgItem(IDC_EDIT2) && pMsg->wParam == VK_RETURN)
	{
		if(m_bIsInProgress)
			return S_OK;

		CWaitCursor waitCursor;
		CComPtr<IDebugSession> pDebugSession;
		RETURN_IF_FAILED(GetDebugSession(&pDebugSession));
		CComPtr<IDebugCommand> pCommand;
		RETURN_IF_FAILED(pDebugSession->CreateCommand(&pCommand));
		CComBSTR bstrText;
		m_editCmd.GetWindowText(&bstrText);
		if(bstrText.Length() != 0)
		{
			RETURN_IF_FAILED(pCommand->SetCommandText(bstrText));
			RETURN_IF_FAILED(m_pViewDebugEngineService->ExecuteCommandAsync(pCommand));
			if (!m_editCmd.SetWindowText(L""))
				return HRESULT_FROM_WIN32(GetLastError());

			m_vCommandsHistory.push_back(CString(bstrText));
			m_commandHistoryIndex = static_cast<int>(m_vCommandsHistory.size() - 1);
		}
		*pbResult = TRUE;
	}

	if(pMsg->message == WM_KEYDOWN && pMsg->hwnd == GetDlgItem(IDC_EDIT2) && pMsg->wParam == VK_UP)
	{
		if(!m_vCommandsHistory.empty())
		{
			m_editCmd.SetWindowText(m_vCommandsHistory[m_commandHistoryIndex]);
		}

		if(m_commandHistoryIndex != 0)
			m_commandHistoryIndex--;
	}

	if(pMsg->message == WM_KEYDOWN && pMsg->hwnd == GetDlgItem(IDC_EDIT2) && pMsg->wParam == VK_DOWN)
	{
		if(!m_vCommandsHistory.empty())
		{
			m_editCmd.SetWindowText(m_vCommandsHistory[m_commandHistoryIndex]);
		}

		if(m_commandHistoryIndex != m_vCommandsHistory.size() - 1)
			m_commandHistoryIndex++;
	}

	return S_OK;
}