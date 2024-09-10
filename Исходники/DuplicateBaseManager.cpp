void CDuplicateBaseManager::OnRecvMsg(const SMessage *pMsg)
{
	const SDuplicateMsg * prtMsg = static_cast<const SDuplicateMsg*>(pMsg);
	if (prtMsg == nullptr)
	{
		rfalse("副本消息转换失败");
		return;
	}

	const SQDuplicateEarningClear* clearMsg = nullptr;

	switch (prtMsg->_protocol)
	{
	case SDuplicateMsg::REQUEST_ENTER_SPECIFY_TOLLGATE:
		///请求挑战指定的副本关卡
		AskToEnterTollgate(prtMsg);
		break;
	case SDuplicateMsg::REQUEST_EARNING_CLEAR:
		clearMsg = static_cast<const SQDuplicateEarningClear*>(pMsg);
		if (clearMsg != nullptr)
			EarningClearProcess(clearMsg->duplicateID, clearMsg->tollgateID, clearMsg->combatGrade);
		break;
	case SDuplicateMsg::REQUEST_START_CHALLENGE:
		OnStartToChallenge();
		/// 记录战斗开始时间(由于子类有重载OnStartToChanllenge 故在此处记录 不管此次是否通过战斗申请 在结算前都应由此函数通知切换场景)
		_time64(&m_tBattleStartTime);
		break;
	case SDuplicateMsg::REREQUEST_TOLLGATE_DROPED_ITEM:
		ReRequestTollgateDropedItem(prtMsg);
		break;
	default:
		///子类的差异化的消息处理模块
		DispatchMsg(prtMsg);
		break;
	}
}