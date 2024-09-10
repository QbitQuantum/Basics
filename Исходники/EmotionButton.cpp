void CEmotionButton::DoEvent(TEventUI& event)
{
     switch( event.Type)
	 {
		 case UIEVENT_MOUSEMOVE:
		 {
				RECT rc1, rc2, invalidRect;
				int lastCol = -1, curCol = -1;

				unsigned char changetype = _PosChangeType::NoChange; //预览矩形是否需要改变

				POINT pt = event.ptMouse;
				int tmpSel = GetCellIndex(pt.x, pt.y);

				//是否超出了图片数量
				if((tmpSel + curPage * CELLCOUNT_PAGE) >= m_ImageCount)
					tmpSel = -1;

				if(tmpSel != curSel)
				{
					//两个cell 索引行进
					lastSel = curSel;
					curSel = tmpSel;
					curFrame = 0;

					//预览矩形需要移动吗？
					lastCol = (lastSel % 15);
					curCol = (curSel % 15); //每行15个

					GetBlueRect(lastSel, &rc1);
					GetBlueRect(curSel, &rc2);
					UnionRect(&invalidRect, &rc1, &rc2);
					invalidRect.right++;
					invalidRect.bottom++;

					//判断缩略矩形是否发生位置改变？
					if(pvstatus == _PVStatus::Hide)
					{
						if(curSel >= 0)
						{
							if((curSel%15) > 7)
							{
								pvstatus = _PVStatus::Left;
								changetype = _PosChangeType::HideToLeft;
							}
							else
							{
								pvstatus = _PVStatus::Right;
								changetype = _PosChangeType::HideToRight;
							}
						}
					}
					else if(pvstatus == _PVStatus::Left)
					{					
						if(curSel < 0)
						{
							pvstatus = _PVStatus::Hide;
							changetype = _PosChangeType::LeftToHide;
						}
						else if(curCol < 4 || (curCol == 4 && lastCol == 4))
						{
							pvstatus = _PVStatus::Right;
							changetype = _PosChangeType::LeftToRight;
						}
					}
					else if(pvstatus == _PVStatus::Right)
					{
						if(curSel < 0)
						{
							pvstatus = _PVStatus::Hide;
							changetype = _PosChangeType::RightToHide;
						}
						else if(curCol > 10 || (curCol == 10 && lastCol == 10))
						{
							pvstatus = _PVStatus::Left;
							changetype = _PosChangeType::RightToLeft;
						}
					}

					//刷新蓝色矩形框
					UpdateSelectedFace(curPage, curSel, curFrame, pvstatus);
					this->Invalidate();
					 
					
					if(changetype == _PosChangeType::NoChange)
					{
						//刷新预览图片
						if(pvstatus == _PVStatus::Left)
						{
							this->Invalidate();
							//InvalidateRect(hDlg, &rcLeft, FALSE);
						}
						else if(pvstatus == _PVStatus::Right)
						{
							this->Invalidate();
							//InvalidateRect(hDlg, &rcRight, FALSE);
						}

					}
					else
					{
						CopyRect(&rc1, &rcLeft);
						CopyRect(&rc2, &rcRight);
						rc1.right++;
						rc1.bottom++;
						rc2.right++;
						rc2.bottom++; 

						//擦除原位置的缩略图
						switch(changetype & 0xf0)
						{
						case 0x00:
							break;
						case 0x10:
							this->Invalidate();
							//InvalidateRect(hDlg, &rc1, FALSE);
							break;
						case 0x20:
							this->Invalidate();
							//InvalidateRect(hDlg, &rc2, FALSE);
							break;
						}
						//显示新位置上的缩略图
						switch(changetype & 0x0f)
						{
						case 0x00:
							pvstatus == _PVStatus::Hide;
							break;
						case 0x01:
							this->Invalidate();
							//InvalidateRect(hDlg, &rc1, FALSE);
							break;
						case 0x02:
							this->Invalidate();
							//InvalidateRect(hDlg, &rc2, FALSE);
							break;
						}
					}

					//安装定时器（显示动画）
					if(curSel >= 0)
					{
						UINT frameDelay = 200;
						CxImage* pImg = GetSelectedImage(curPage, curSel);
						CxImage* pFrame = pImg->GetFrame(curFrame);

						//QQ表情的帧延时通常是10毫秒，显示速度过快，因此增大到50毫秒
						if(pFrame != NULL) frameDelay = max(frameDelay, pFrame->GetFrameDelay());

						frameCount = pImg->GetNumFrames();
 
						this->m_pManager->SetTimer(this, TIMER_SHOWGIF, frameDelay);
					}
					else
					{ 
						this->m_pManager->KillTimer(this, TIMER_SHOWGIF);
					}
				}
				
				//使系统通知我们 WM_MOUSELEAVE ;
				TrackMouseEvent(&m_tme); //注意版本需求：_WIN32_WINNT 0x0510
		 }
		 break;
		 case UIEVENT_MOUSELEAVE:
		 {
				if(curSel >= 0)
				{
					RECT rc;
					GetBlueRect(curSel, &rc);
					lastSel = curSel;
					curSel = -1;
					curFrame = 0;
					pvstatus = _PVStatus::Hide;
					UpdateSelectedFace(curPage, curSel, curFrame, pvstatus);
					this->Invalidate();
					//InvalidateRect(hDlg, &rc, FALSE);
				}
		 }
		 break;
		 case UIEVENT_TIMER:
		 {
			  this->m_pManager->KillTimer(this, TIMER_SHOWGIF);

			if(curSel >= 0 && frameCount > 1)
			{
				CxImage *pImg = GetSelectedImage(curPage, curSel);
				CxImage *pFrame = NULL;
				UINT frameDelay = 200;

				LPRECT lpRect = (pvstatus == _PVStatus::Left)? &rcLeft:&rcRight;
				
				//移动到下一帧！
				curFrame = (curFrame + 1) % frameCount;

				//QQ表情的帧延时通常是10毫秒，显示速度过快，因此增大到100毫秒
				pFrame = pImg->GetFrame(curFrame);
				
				if(pFrame) frameDelay = max(frameDelay, pFrame->GetFrameDelay());
 
				UpdateSelectedFace(curPage, curSel, curFrame, pvstatus);
				this->Invalidate();
				//InvalidateRect(hDlg, lpRect, FALSE);

				//下一帧的定时时间
				this->m_pManager->SetTimer(this, TIMER_SHOWGIF, frameDelay);
			} 
		 }
		 break;
	 }
}