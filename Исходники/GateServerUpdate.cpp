//
// 更新接收消息
//
void CGateServer::OnUpdateRecv(DWORD dwDeltaTime)
{
	CIOContext *pContext = m_pActiveContext;

	while (pContext) {
		CIOContext *pNextContext = pContext->pNextActive;

		if (pContext->IsAlive()) {
			pContext->SwitchRecvBuffer();
			pContext->dwHeartTime += dwDeltaTime;

			while (TRUE) {
				WORD msg;
				WORD fullSize;
				WORD bodySize;

				if (pContext->GetRecvBuffer().GetData((BYTE *)&fullSize, sizeof(fullSize)) != sizeof(fullSize)) break;
				if (pContext->GetRecvBuffer().GetActiveBufferSize() < sizeof(fullSize) + fullSize) break;

				if (pContext->GetRecvBuffer().PopData((BYTE *)&fullSize, sizeof(fullSize)) != sizeof(fullSize)) break;
				if (pContext->GetRecvBuffer().PopData((BYTE *)&msg, sizeof(msg)) != sizeof(msg))  break;

				bodySize = fullSize - sizeof(msg);
				m_dwRecvDataSize += sizeof(fullSize) + fullSize;

				ResponseFuncs::const_iterator itFunc = m_responses.find(msg);
				if (itFunc == m_responses.end()) continue;

				(this->*itFunc->second)(pContext, bodySize);
				OnHeartReset(pContext);
			}
		}

		if (pContext->Check((DWORD)(1000 * m_timeOut)) == FALSE) {
			ReleaseContext(pContext, FALSE);
		}

		pContext = pNextContext;
	}
}