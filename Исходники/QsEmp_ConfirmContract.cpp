/*---------------------------------------------------------------------*//**
	フレーム処理実装
**//*---------------------------------------------------------------------*/
void QsEmp_ConfirmContract::execImplement(ExecRes* res, const ExecCtx* ec, f32 frameBegun)
{
	GameGui* gui = Game::getGame()->getGui(); ASSERT(gui != 0L);
	GameSysMsgWindow* wndSysMsg = (GameSysMsgWindow*)gui->getSysMsgWindow(); ASSERT(wndSysMsg != 0L);
	ScreenEffect* screff = Game::getGame()->getSceneScreenEffect(); ASSERT(screff != 0L);

	switch(getStep())
	{
	case STEP_WAIT_BEGIN:		// 継続監視
		///STRACE("!!! WAIT...\n");
		if(!getOwner()->checkBegunOtherMatter(this, true))	// 自身以外のイベントが起動していない
		{
			// メッセージを得る
			EventData* evdat = getOwner()->getEventData(); ASSERT(evdat != 0L);
			const MsgDataSet* msgdatset = evdat->getMsgDataSet(); ASSERT(msgdatset != 0L);
			// YES / NO メッセージウインドウを表示する
			wndSysMsg->setKind(MessageWindow::KIND_YESNO);
			wndSysMsg->showMessage(GameFixedStrTbl::getString(GameFixedStrTbl::SID_QUEST_CONFIRM_CONTRACT), MSGWND_CTRL_HINT);

			// 次のステップへ
			advanceStep();
		}
		break;
	case STEP_WAIT_YESNO:
		{
			const GameSysMsgWindow::Result* res = wndSysMsg->getResult();
			if(res->isClickYesButton())
			{
				// ウインドウを閉じる
				wndSysMsg->showWindow(false);

				// スプライトを読み込む
				_sprite->create(FILEID_CONV_LANG(QUESTEVENT_SPRITE_QUESTACCEPT_EN_PNG), 0, true, 0x000000ff, true);

				// SE 再生
				Game::getGame()->getSoundManager()->playUiSe(GameSoundDef::SE_QUEST_ADV, false);

				// 次のステップへ
				advanceStep();
			}
			else if(res->isClickNoButton())
			{
				// ウインドウを閉じる
				wndSysMsg->showWindow(false);

				// 終了
				end();

				// 親マターも終了してイベントを閉じる
				EventData* evdat = getOwner()->getEventData(); ASSERT(evdat != 0L);
				EvMatter* matter = evdat->getMatterFromEvid(getParentEvId());
				if(matter != 0L) { matter->end(); }
			}
		}
		break;
	case STEP_WAIT_EFFECT:
		if(_sprite->isEnd())
		{
			// フェードアウト
			ColorU8 colBlack(0, 0, 0, 255);
			screff->setColor1(&colBlack);
			screff->setMaxFrame(60);
			screff->start(ScreenEffect::MODE_FADE_OUT);

			// 次のステップへ
			advanceStep();
		}
		_sprite->exec(ec);
		break;
	case STEP_WAIT_FOUT:
		if(!screff->isWorking())
		{
			// クエスト受託
			contractQuest();

			// フェードインへ
			ColorU8 colBlack(0, 0, 0, 255);
			screff->setColor1(&colBlack);
			screff->setMaxFrame(30);
			screff->start(ScreenEffect::MODE_FADE_IN);
			// 次のステップへ
			advanceStep();
		}
		break;
	case STEP_WAIT_FIN:
		if(!screff->isWorking())
		{
			screff->end(0);
			end();
		}
		break;
	}
}