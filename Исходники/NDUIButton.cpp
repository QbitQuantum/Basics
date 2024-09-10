void NDUIButton::draw()
{
	//cocos2d::CCLog("Entry NDUIButton::draw()");

	if (!isDrawEnabled()) return;

	NDUINode::draw();

	if (!this->IsVisibled()) return;
	
	if (m_bNeedSetTitle)
	{
		SetTitle();
		m_bNeedSetTitle = false;
	}

	if (m_bNeedSetTwoTitle)
	{
		SetTwoTitle();
		m_bNeedSetTwoTitle = false;
	}

	// check parent as uiLayer
	NDNode* parentNode = this->GetParent();
	if (!parentNode) return;
	if (!parentNode->IsKindOfClass(RUNTIME_CLASS(NDUILayer))) return;
	NDUILayer* uiLayer = (NDUILayer*) parentNode;

	// draw gray image
	CCRect scrRect = this->GetScreenRect();
	if(m_bGray && m_disImage)
	{
		m_disImage->DrawInRect(scrRect);
		return;
	}

	//draw back ground
	if (m_picBG && !m_longTouched)
	{
		if (m_useBackgroundCustomRect)
		{
			m_picBG->DrawInRect(
					CCRectMake(
							scrRect.origin.x
									+ m_backgroundCustomRect.origin.x,
							scrRect.origin.y
									+ m_backgroundCustomRect.origin.y,
							m_backgroundCustomRect.size.width,
							m_backgroundCustomRect.size.height));
		}
		else
		{
			m_picBG->DrawInRect(scrRect);
		}
	}
	else if (m_combinePicBG)
	{
		m_combinePicBG->DrawInRect(scrRect);
	}
	else
	{
		DrawRecttangle(scrRect, m_backgroundColor);
	}

	// scroll title
	if (m_bScrollTitle && m_scrtTitle
			&& m_scrtTitle->GetParent() == this)
	{
		if (uiLayer->GetFocus() == this)
		{
			// !run -> start
			if (!m_scrtTitle->isRunning())
			{
				m_scrtTitle->Run();
			}

			m_scrtTitle->SetFontColor(m_colorFocusTitle);
		}
		else
		{
			// run -> stop -> resetpos
			if (m_scrtTitle->isRunning())
			{
				m_scrtTitle->Stop();
				m_scrtTitle->SetTextPos(CCPointMake(5.0f, 0.0f));
			}

			m_scrtTitle->SetFontColor(m_colorTitle);
		}
	}

	//draw focus 
	if (uiLayer->GetFocus() == this || IsTabSel())
	{
		drawFocus();
	}
	else
	{
		if (m_title)
		{
			m_title->SetFontColor(m_colorTitle);
		}
	}

	//draw touch down status
	if (m_bChecked || (m_touched && !m_longTouched))
	{
		drawTouchDown();
	}

	//button image
	if (m_image || m_combinepicImg)
	{
		drawButtonImage();
	}
	else
	{
		if (m_framed)
		{
			drawButtonFrame();
		}
	}

	if (m_pSprite)
	{
		m_pSprite->SetPosition(ccpAdd(scrRect.origin, m_posSprite));
		m_pSprite->Run( CCDirector::sharedDirector()->getWinSizeInPixels() );
	}

	if (m_longTouched)
	{
		drawLongTouch();
	}
}