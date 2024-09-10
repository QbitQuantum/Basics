	void UIAliveRpg::UIShowGeneralInfo()
	{
		CPlayerCharacter*  myPlayerCharacter = CPlayer::getInstance().getMainGenreal();
		if (NULL == myPlayerCharacter)
		{
			return;
		}

		//名字
		{
			IText* name = getLayout()->getText("edt_name");
			DYNAMIC_ASSERT(name);
			name->getWidget()->setCaption(myPlayerCharacter->getNormalName());
		}

		//时间
		{
			ITimeText* time = getLayout()->getTimeText("edt_time");
			DYNAMIC_ASSERT(time);
			time->setCoolDownTime(30*1000);
		}
	}