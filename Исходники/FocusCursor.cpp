/*---------------------------------------------------------------------*//**
	フレーム制御
**//*---------------------------------------------------------------------*/
void FocusCursor::exec(ExecRes* res, const ExecCtx* ec)
{
	if(!_isEnableOut)	{	return;	}	// 外部からの無効化

	GameExecCtx* gec = (GameExecCtx*)ec;
	TouchPanel* ui = gec->getTouchPanel(); 

	// フォーカスの有効性更新
	_focusarr->updateValidity();
	// フォーカスの座標値をリセット
	for(s32 i = 0; i < NUM_FOCUS_MAX; i++)
	{
		_focusarr->invalidateScreenPos(i);
	}

	// 有効性判定
	_isEnableSelf = !gec->isLockOperating();
	bool isEnableUiReact = _isEnableSelf && !gec->isOpenedLockGui() && !ui->isReacted() && (_fcntPreventTap == 0.0f);

	// タッチ操作による処理
	if(isEnableUiReact) 
	{
		PointF32 ptTouch, ptStart;
		bool isTap = false;
		bool isDblTapRel = false;
		if(!ui->isReacted())
		{
			const f32 DIFF_TAP_RANGE = 20.0f;
			if(ui->isTapRelease(&ptTouch, &ptStart)) { isTap = ptTouch.isNear(&ptStart, DIFF_TAP_RANGE, DIFF_TAP_RANGE); }	// 面積が狭いので、isClickRelease だとストレスに感じる
			if(ui->isDoubleClickRelease(&ptTouch)) { isDblTapRel = true; }
		}
		if(isTap || isDblTapRel)
		{
			Tfw* tfw = Game::getGame()->getTfw();						ASSERT(tfw != 0L);
			View* view = tfw->getView();								ASSERT(view != 0L);
			SorSgm* sgm = (SorSgm*)tfw->getSgManager();					ASSERT(sgm != 0L);
			Camera* cam = sgm->getVisibleCamera();						ASSERT(cam != 0L);

			UnitManager* unitmng = Game::getGame()->getUnitManager();	ASSERT(unitmng != 0L);
			for(int i = 0; i < unitmng->getUnitNum(); i++)
			{
				Unit* unit = unitmng->getUnitFromIndex(i);				ASSERT(unit != 0L);
				if(!unit->isEnable())		{	continue;	}	// 無効なユニットは除外
				if(!unit->isEnableFocus())	{	continue;	}	// フォーカスされないユニットは除外
				if(unit->isHidden())		{	continue;	}	// 隠し属性ユニットは除外
				if(unit->getUnitType() == UNITTYPE_EQUIPMENT_ITEM)	{	continue;	}	// 所持品は除外
				if(unit->getCenterPos()->z() >= cam->getLoc()->z())	{	continue;	}	// カメラより手前は除外

				// スクリーン座標に変換
				Vector2F vScr;
				Gcalc::conv3dPosToScreenPos(&vScr, unit->getCenterPos(), cam, view);

				if(isDblTapRel)	// ダブルクリック時は直接フォーカスをセットする
				{
					// 一度フォーカスをリセット
					for(int j = 0; j < NUM_FOCUS_MAX; j++)
					{
						setFocus(j, 0L, 0L);
					}
					// 範囲内かどうか判定して、範囲内だったらフォーカス設定する
					if(TFW_IS_NEAR(vScr.x(), ptTouch.x(), RANGE_TOTRG) && TFW_IS_NEAR(vScr.y(), ptTouch.y(), RANGE_TOTRG))
					{
						// フォーカスをセット（上部でリセットしているので、[0] 決めうち）
						setFocus(0, unit, &vScr);
						// UI に反応済みフラグを立てる
						ui->setReacted(true);
						break;
					}
				}
				else if(isTap)	// タップ時はメニューを表示
				{
					// 範囲内かどうか判定して、範囲内だったらメニューを表示する
					TRACELN("{FocusCursor::exec} unit touch?; scr_x=%f, scr_y=%f, click_x=%d, click_y=%d", vScr.x(), vScr.y(), ptTouch.x(), ptTouch.y());
					if(TFW_IS_NEAR(vScr.x(), ptTouch.x(), RANGE_TOTRG) && TFW_IS_NEAR(vScr.y(), ptTouch.y(), RANGE_TOTRG))
					{
						showFocusMenu(unit, &vScr);		// フォーカスメニュー表示
						ui->setReacted(true);	// UI に反応済みフラグを立てる
					}
				}
			}
		}
	}

	// フォーカスカーソルの画面位置を計算
	for(s32 i = 0; i < NUM_FOCUS_MAX; i++)
	{
		// 無効になったユニットは外す
		const Unit* unitFocused = _focusarr->getUnit(i);
		if(unitFocused == 0L)	{	continue;	}
		if(!unitFocused->isEnable())
		{
			setFocus(i, 0L, 0L);
		}

		// スクリーン座標値が未計算の場合、計算する
		if(!_focusarr->isValidScreenPos(i))
		{
			_focusarr->calcScreenPos(i);
		}
	}

	// マジッククラスターのフォーカスの画面位置を計算
	MagicSys* mgsys = Game::getGame()->getMagicSys();
	for(int i = 0; i < mgsys->getMaxClusterNum(); i++)
	{
		MagicCluster* mc = mgsys->getClusterFromIndex(i);
		if(mc == 0L)		{	continue;	}
		if(!mc->isValid())	{	continue;	}
		mc->focusArray()->calcScreenPosAll();
	}

	// タップ防止カウンタの更新
	if(_fcntPreventTap > 0.0f)
	{
		_fcntPreventTap -= ec->getDeltaFrame();
		if(_fcntPreventTap < 0.0f)	{	_fcntPreventTap = 0.0f;	}
	}

	// カーソル回転角度の更新
	_dangFocus += DANG_FOCUS_DELTA;
	if(_dangFocus > 180.0f)		{	_dangFocus -= 360.0f;		}
	_dangFocusable += DANG_FOCUSABLE_DELTA;
	if(_dangFocusable > 180.0f)	{	_dangFocusable -= 360.0f;	}
}