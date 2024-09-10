/*---------------------------------------------------------------------*//**
	フレーム制御
**//*---------------------------------------------------------------------*/
void EventMovieFront::exec(ExecRes* res, const ExecCtx* ec)
{
	if(!_isEnableOut)	{	return;	}	// 外部からの無効化

	GameExecCtx* gec = (GameExecCtx*)ec;
	TouchPanel* ui = gec->getTouchPanel(); 
	GameSysMsgWindow* wndSysMsg = (GameSysMsgWindow*)Game::getGame()->getGui()->getSysMsgWindow(); ASSERT(wndSysMsg != 0L);

	if(wndSysMsg->isShowWindow() && _isAskYesNo)
	{
		// Yest / No ウインドウの制御
		const GameSysMsgWindow::Result* res = wndSysMsg->getResult();
		if(res->isClickYesButton() || res->isClickNoButton())
		{
			if(res->isClickYesButton())
			{
				// イベントスキップ
				operationToEvent(EOP_SKIP);
			}
			// イベントポーズの解除
			operationToEvent(EOP_PLAY);
			Game::getGame()->getSoundManager()->resumeBgm();	// BGM 再開
			// ウインドウを閉じる
			wndSysMsg->showWindow(false);
			_isAskYesNo = false;
		}
	}
	else
	{
		// パネルの制御
		{
			// ボタンの位置補正
			if(_btn[BTN_SKIP]._pnl->getRectangle()->left() != X_SKIP)
			{
				RectF32 rect(RECT_SKIP);
				_btn[BTN_SKIP]._pnl->setRectangle(&rect);
			}

			// スキップ可能か
			_btn[BTN_SKIP]._isEnable = operationToEvent(EOP_CHECKSKIP);

			// タッチをパネルに伝達
			PointF32 ptTouch(S32_MIN, S32_MIN);
			PointF32 ptClick(S32_MIN, S32_MIN);
			bool isTouch = !ui->isReacted() ? ui->getTouchPosition(&ptTouch) : false;
			bool isClick = !ui->isReacted() ? ui->isTapRelease(&ptClick, 0L) : false;
			for(int i = 0; i < NUM_BTN; i++)
			{
				if(!_btn[i]._isEnable)	{	continue;	}
				if(isClick)
				{
					if(_btn[i]._pnl->hit(&ptClick, true))
					{
						switch(i)
						{
						case BTN_SKIP:
							{
								// イベントスキップ確認のための一時停止
								if(operationToEvent(EOP_PAUSE))
								{
									ui->setReacted(true);	// UI 反応済み
								}
								Game::getGame()->getSoundManager()->pauseBgm();	// BGM も一時停止
								// イベントスキップの確認
								wndSysMsg->setKind(GameSysMsgWindow::KIND_YESNO);
								wndSysMsg->setReadingAnimation(false);
								wndSysMsg->showMessage(GameFixedStrTbl::getString(GameFixedStrTbl::SID_GUI_CONFIRM_SKIP), 0);
								_isAskYesNo = true;
								break;
							}
							break;
						}
						ui->setReacted(true);
					}
				}
				else
				{
					_btn[i]._pnl->hit(&ptTouch, isTouch);
				}
				_btn[i]._pnl->exec(res, ec);
			}
		}

		// 台詞待ちの終了操作
		if(!ui->isReacted())
		{
			if(ui->isClickRelease(0L))
			{
				// 台詞待ち終了
				if(operationToEvent(EOP_ENDWAIT))
				{
					ui->setReacted(true);	// UI 反応済み
				}
			}
		}
	}
}