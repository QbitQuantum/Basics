void NFCActor::Handler(const NFIActorMessage& message, const Theron::Address from)
{
    std::string strData = message.data;

	ACTOR_PROCESS_FUNCTOR_PTR ptrBegin = mxProcessFuntor.GetElement(message.nMsgID);
	if (ptrBegin != nullptr)
	{
		
		ACTOR_PROCESS_FUNCTOR* pFun = ptrBegin.get();
		pFun->operator()(message.self, message.nFormActor, message.nMsgID, strData);
	}
	else
	{
		for (NF_SHARE_PTR<NFIComponent> pComponent = mxComponent.First(); pComponent != nullptr; pComponent = mxComponent.Next())
		{
			if (pComponent->Enable())
			{
				pComponent->OnASyncEvent(message.self, message.nFormActor, message.nMsgID, strData);
			}
		}
	}
 
    ////////////////////////////////////////////////////////
	// must return message 
    NFIActorMessage xReturnMessage;

	xReturnMessage.msgType = NFIActorMessage::ACTOR_MSG_TYPE_END_FUNC;
	xReturnMessage.nMsgID = message.nMsgID;
    xReturnMessage.data = strData;
    xReturnMessage.self = message.self;
    xReturnMessage.nFormActor = this->GetAddress().AsInteger();

	ACTOR_PROCESS_FUNCTOR_PTR ptrEnd = mxEndProcessFuntor.GetElement(message.nMsgID);
	if (ptrEnd != nullptr)
	{
		xReturnMessage.xEndFuncptr = ptrEnd;
	}
	else
	{
		//default end function
		if (mxDefaultEndProcessFuntor != nullptr)
		{
			xReturnMessage.xEndFuncptr = mxDefaultEndProcessFuntor;
		}
	}

    Send(xReturnMessage, from);
}