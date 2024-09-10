/*---------------------------------------------------------------------*//**
	フレーム処理実装
**//*---------------------------------------------------------------------*/
void MapEmp_10242_1701_RestAtHome::execImplement(ExecRes* res, const ExecCtx* ec, f32 frameBegun)
{
    enum Step
    {
        STEP_NULL,
        STEP_WAIT_BEGIN,
        STEP_CHECK_MOTEHR,
        STEP_TALK,
        STEP_WAIT_TALK,
        STEP_WAIT_YESNO,
        STEP_WAIT_FOUT,
        STEP_WAIT_FIN,
    };

    GameGui* gui = Game::getGame()->getGui();
    ASSERT(gui != 0L);
    SubtitlesWindow* wndSbt = gui->getSubtitlesWindow();
    ASSERT(wndSbt != 0L);
    GameSysMsgWindow* wndSysMsg = (GameSysMsgWindow*)gui->getSysMsgWindow();
    ASSERT(wndSysMsg != 0L);
    ScreenEffect* screff = Game::getGame()->getSceneScreenEffect();
    ASSERT(screff != 0L);

    switch(getStep())
    {
    case STEP_WAIT_BEGIN:		// 継続監視
        ///STRACE("!!! WAIT...\n");
        if(!getOwner()->checkBegunOtherMatter(this, true))
        {
            // 自身以外のイベントが起動していないならば次のステップへ
            advanceStep();
        }
        break;
    case STEP_CHECK_MOTEHR:
    {
        UnitManager* unitmng = Game::getGame()->getUnitManager();
        ASSERT(unitmng != 0L);
        // アサの母親在宅チェック
        Unit* unitYu = unitmng->findCharUnitFromCharId(CharIdDef::CHARID_NPC_MOTHER);
        _isShowMotherMsg = (unitYu != 0L);

        // 次のステップへ
        advanceStep();
    }
    break;
    case STEP_TALK:
    {
        if(_isShowMotherMsg)
        {
            // メッセージを得る
            EventData* evdat = getOwner()->getEventData();
            ASSERT(evdat != 0L);
            const MsgDataSet* msgdatset = evdat->getMsgDataSet();
            ASSERT(msgdatset != 0L);
            const MsgData::Msg* msg = msgdatset->findMessageFromMsgid(MSGID_TALK_MSG);
            const VcString strMsg = (msg != 0L) ? msgdatset->getString(msg) : "";
            // 会話メッセージウインドウを表示する
            wndSbt->setKind(SubtitlesWindow::KIND_TALK);
            wndSbt->showMessage(&strMsg, MSGWND_CTRL_HINT);

            // 次のステップへ
            advanceStep();
        }
        else
        {
            if(frameBegun > (1.0f * FRAMERATE))	// ちょっと待って
            {
                // 次のステップへ
                advanceStep();
            }
        }
    }
    break;
    case STEP_WAIT_TALK:
        if(wndSbt->isDone() || (!_isShowMotherMsg))
        {
            // ウインドウを閉じる
            wndSbt->showWindow(false);

            // メッセージを得る
            EventData* evdat = getOwner()->getEventData();
            ASSERT(evdat != 0L);
            const MsgDataSet* msgdatset = evdat->getMsgDataSet();
            ASSERT(msgdatset != 0L);
            const MsgData::Msg* msg = msgdatset->findMessageFromMsgid(MSGID_INQURE);
            const VcString strMsg = (msg != 0L) ? msgdatset->getString(msg) : "";
            // YES / NO メッセージウインドウを表示する
            wndSysMsg->setKind(MessageWindow::KIND_YESNO);
            wndSysMsg->showMessage(&strMsg, MSGWND_CTRL_HINT);

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
            // フェードアウト
            ColorU8 col1(0, 0, 0, 255);
            screff->setColor1(&col1);
            screff->setMaxFrame(120);
            screff->start(ScreenEffect::MODE_FADE_OUT);
            // 次のステップへ
            advanceStep();
        }
        else if(res->isClickNoButton())
        {
            // ウインドウを閉じる
            wndSysMsg->showWindow(false);
            // 終了
            end();
        }
    }
    break;
    case STEP_WAIT_FOUT:
        if(!screff->isWorking())
        {
            // 家での休息処理
            restAtHome();
            StoryManager* strymng = Game::getGame()->getStoryManager();
            ASSERT(strymng != 0L);
            strymng->notifyRestAtHome();

            // PSNS にスコア送信
            ScoreBase* score = Game::getGame()->getScore();
            ASSERT(score != 0L);
            score->updatePsnsScore();

            // 休息時イベント起動（たいていは何も起動しない）
            EventSys* evsys = Game::getGame()->getEventSys();
            ASSERT(evsys != 0L);
            EvCause evcause(EventCause::CID_EVENT);
            ///evsys->beginCase(StDepEvDef::ECID_V01_MAP_REST_AT_HOME, 0, &evcause);
            evsys->begin(StDepEvDef::EVID_EP01_MAP_AFTER_REST_AT_HOME, 0, &evcause);

            // フェードインへ
            ColorU8 col1(0, 0, 0, 255);
            screff->setColor1(&col1);
            screff->setMaxFrame(60);
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