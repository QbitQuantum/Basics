//-------------------------------------------------------------------------------------
bool ForwardAnywhere_MessageBuffer::process()
{
	if(pBundles_.size() <= 0)
	{
		start_ = false;
		return false;
	}
	
	Components::COMPONENTS& cts = Components::getSingleton().getComponents(forwardComponentType_);
	size_t idx = 0;

	if(cts.size() > 0)
	{
		bool hasEnabled = (g_componentType != CELLAPPMGR_TYPE && g_componentType != BASEAPPMGR_TYPE);

		Components::COMPONENTS::iterator ctiter = cts.begin();
		for(; ctiter != cts.end(); ++ctiter)
		{
			// 必须所有的组件频道都被设置，如果不是则等待。
			if((*ctiter).pChannel == NULL)
				return true;

			if((*ctiter).state == COMPONENT_STATE_RUN)
				hasEnabled = true;
		}

		// 必须有可用的进程
		if(!hasEnabled)
			return true;

		// 最多每个tick处理5个
		int icount = 5;

		std::vector<ForwardItem*>::iterator iter = pBundles_.begin();
		for(; iter != pBundles_.end(); )
		{
			Network::Channel* pChannel = NULL;
			
			if(g_componentType != CELLAPPMGR_TYPE && g_componentType != BASEAPPMGR_TYPE)
			{
				pChannel = cts[idx++].pChannel;
				if(idx >= cts.size())
					idx = 0;
			}
			else
			{
				while(pChannel == NULL)
				{
					if(cts[idx].state != COMPONENT_STATE_RUN)
					{
						if(++idx >= cts.size())
							idx = 0;

						continue;
					}

					pChannel = cts[idx++].pChannel;
					if(idx >= cts.size())
						idx = 0;
				}
			}

			pChannel->send((*iter)->pBundle);
			(*iter)->pBundle = NULL;

			if((*iter)->pHandler != NULL)
			{
				(*iter)->pHandler->process();
				SAFE_RELEASE((*iter)->pHandler);
			}
			
			SAFE_RELEASE((*iter));

			iter = pBundles_.erase(iter);

			if(--icount <= 0)
				return true;
		}
		
		DEBUG_MSG(fmt::format("ForwardAnywhere_MessageBuffer::process(): size:{}.\n", pBundles_.size()));
		start_ = false;
		return false;
	}

	return true;
}