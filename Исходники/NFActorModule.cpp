bool NFActorModule::ExecuteEvent()
{
	NFIActorMessage xMsg;
	bool bRet = false;
	bRet = mxQueue.TryPop(xMsg);
	while (bRet)
	{
		if (xMsg.msgType != NFIActorMessage::ACTOR_MSG_TYPE_COMPONENT && xMsg.xEndFuncptr != nullptr)
		{
			//Actor can be reused in ActorPool mode, so we don't release it.
			//>ReleaseActor(xMsg.nFormActor);
			ACTOR_PROCESS_FUNCTOR* pFun = xMsg.xEndFuncptr.get();
			pFun->operator()(xMsg.nFormActor, xMsg.nMsgID, xMsg.data);


			NF_SHARE_PTR<NFIActor> xActor = mxActorMap.GetElement(xMsg.nFormActor);
			if (xActor)
			{
				if (xActor->GetNumQueuedMessages() <= 0)
				{
					int nActorID = xActor->GetAddress().AsInteger();
					if (mxActorPool.find(nActorID) == mxActorPool.end())
					{
						mxActorPool.insert(std::pair<int, int>(nActorID, 0));
					}
				}
			}
		}

		bRet = mxQueue.TryPop(xMsg);
	}

	return true;
}