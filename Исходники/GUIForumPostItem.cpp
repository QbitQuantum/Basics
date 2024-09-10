void GUIForumPostItem::setItemData(ForumThread* pThread)
{
	std::wstringstream ss;
	core::rect<s32> itemRect(5, 0, RelativeRect.getWidth()-5, RelativeRect.getHeight()), startRect;
	IGUIFont* pFont = Environment->getSkin()->getFont();

	startRect = itemRect;

	itemRect.LowerRightCorner.Y = itemRect.UpperLeftCorner.Y + FPI_AUTHOR_HEIGHT;
	if ( !m_pTxtAuthor )
	{
    ss << L"Author: " << pThread->getAuthorName().c_str();
		m_pTxtAuthor = Environment->addStaticText(ss.str().c_str(), itemRect, false, false, this);
		m_pTxtAuthor->setOverrideColor(m_colText);
		m_pTxtAuthor->setTextAlignment( EGUIA_UPPERLEFT, EGUIA_CENTER );
    ss.str(L"");
	}

	if ( pThread->getTitle().size() )
	{
 		offsetRect(itemRect, 0, itemRect.getHeight() + 5);
		if ( !m_pTxtSubject )
		{
			ss << L"Subject: " << pThread->getTitle().c_str();
			m_pTxtSubject = Environment->addStaticText(ss.str().c_str(), itemRect, false, false, this);
			m_pTxtSubject->setOverrideColor(m_colText);
			m_pTxtSubject->setTextAlignment( EGUIA_UPPERLEFT, EGUIA_CENTER );
			ss.str(L"");
		}
	}

	offsetRect(itemRect, 0, itemRect.getHeight() + 5);
	if ( !m_pTxtContent )
	{
		ss << pThread->getContent().c_str();
		m_pTxtContent = Environment->addStaticText(ss.str().c_str(), itemRect, true, true, this);
		m_pTxtContent->setBackgroundColor(m_colBkg);
		m_pTxtContent->setOverrideColor(m_colText);
	  itemRect.LowerRightCorner.Y = itemRect.UpperLeftCorner.Y + m_pTxtContent->getTextHeight();
		m_pTxtContent->setRelativePosition( itemRect );
		ss.str(L"");
	}

	// if this is a mission thread, then we need to create the button to accept the mission
	if ( pThread->getMissionID() )
	{
		// check which options should be shown
		MissionMgr& missionMgr = FCModel::instance().GetMissionMgr();
		bool bAccepted = missionMgr.isMissionAccepted(pThread->getMissionID());
		bool bCompleted = missionMgr.isMissionComplete(pThread->getMissionID());

		if ( !bAccepted && !bCompleted )
		{
			offsetRect(itemRect, 0, itemRect.getHeight() + 5);
			itemRect.LowerRightCorner.Y = itemRect.UpperLeftCorner.Y + 20;
			core::rect<s32> btnRect = itemRect;
			ss << "Accept";
			btnRect.LowerRightCorner.X = btnRect.UpperLeftCorner.X + pFont->getDimension(ss.str().c_str()).Width + 20;
			m_pBtnAccept = Environment->addButton(btnRect, this, BTN_ACCEPT, ss.str().c_str());
		}
	}

	core::rect<s32> myRect = getRelativePosition();
	myRect.LowerRightCorner.Y = myRect.UpperLeftCorner.Y + ( itemRect.LowerRightCorner.Y - startRect.UpperLeftCorner.Y ) + 5;
	setRelativePosition(myRect);

	m_pThread = pThread;
}