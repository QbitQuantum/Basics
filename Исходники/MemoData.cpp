CMemoData::CMemoData() : CObject()
{
	// 基本設定
	{
		m_cStrTitle.Empty();			// タイトル
		m_cStrMemo.Empty();				// 表示内容

		m_pstLogFont	= NULL;			// 表示フォント
		m_clrForeColor	= CLR_INVALID;	// 文字色
		m_clrBackColor	= CLR_INVALID;	// 背景色

		m_nIconIndex	= -1;			// アイコン種別
	}

	// 拡張設定
	{
		m_blLink			= FALSE;	// 関連付け有功無効
		m_cStrFile.Empty();				// ファイル
		m_cStrParameters.Empty();		// パラメータ
		m_blTimerExec		= FALSE;	// タイマで起動

		m_blPassWordLock	= FALSE;	// パスワードの有功無効
		m_cStrPassWord.Empty();			// パスワード

		// 描画拡張
		m_unDxlID			= 0;		// Dxl-ID
		m_unDxlExtDataSize	= 0;		// Dxl 拡張データサイズ
		m_pabyDxlExtData	= NULL;		// Dxl 拡張データ
	}

	// タイマ
	{
		SYSTEMTIME	stSysTime;
		GetLocalTime( &stSysTime);
		COleDateTime cTime( stSysTime);// = COleDateTime::GetCurrentTime();

		m_blTimer		= FALSE;				// タイマ通知有功
		m_nTimerType	= TIMERTYPE_EVERYDAY;	// タイマ種別
		m_nNotifyShift	= NOTIFYSHIFT_NOMOVE;	// 通知日の移動処理
		m_nMonth		= cTime.GetMonth();		// 通知月
		m_nDay			= cTime.GetDay();		// 通知日
		m_nHour			= 0;					// 通知時
		m_nMin			= 0;					// 通知分
		m_nWeek			= WEEK_DISABLE;			// 通知曜日

		m_nBeforeNotify	= 0;					// 事前通知
		m_blAfterNotify	= FALSE;				// 経過通知

		m_cStrNotifySound.Empty();				// 通知サウンドファイル
	}

	// Window関係
	{
		m_cRctNormal.SetRectEmpty();
		m_cRctTitle.SetRectEmpty();
		m_cRctIcon.SetRectEmpty();

		m_nWindowType = WINDOW_TYPE_NORMAL;	// 形状
		m_blPosLock = FALSE;

		m_blShow = TRUE;
		m_nZOrder = ZORDER_NORMAL;

		m_blSeeThrough = FALSE;

		m_byAlphaBlend = ALPHABLEND_000;
	}

	// 作成日付記憶
	SetCreateDate();

	// 結果受信用ＩＤ
	m_pcStrContextID = NULL;
}