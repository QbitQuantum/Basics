bool
GetPdhCounterValue(LPTSTR	pszInstanceName,	// インスタンス名
	LPTSTR	pszCounterName,		// カウンター名
	DWORD	dwFormat,			// 受け取る値の型の種類
	void*	pValue,				// 値受け取りバッファー
	DWORD	dwValueSize,		// 値受け取りバッファーのサイズ（byte）
	DWORD	dwSleepMilliSecond = 0)	// [in]値受け取り時にスリープをするか
{
	// 入力チェック
	if (NULL == pszInstanceName
		|| NULL == pszCounterName
		|| NULL == pValue
		|| 0 == dwValueSize)
	{
		//assert( !"入力エラー" );
		return false;
	}

	bool		bResult = false;		// 結果

	HQUERY		hQuery = NULL;		// 要求ハンドル
	HCOUNTER	hCounter = NULL;	// カウンターハンドル

									// カウンターパスの作成
	TCHAR szCounterPath[1024];
	if (1 != MakeCounterPath(pszInstanceName, pszCounterName, szCounterPath, 1024))
	{
		goto LABEL_END;
	}

	// 要求ハンドルの作成
	if (ERROR_SUCCESS != PdhOpenQuery(NULL,
		0,
		&hQuery))	// 要求ハンドル
	{
		goto LABEL_END;
	}

	// 作成したカウンターパスを要求ハンドルに登録。カウンターハンドルを得ておく。
	if (ERROR_SUCCESS != PdhAddCounter(hQuery,			// 要求ハンドル
		szCounterPath,
		0,
		&hCounter))	// カウンターハンドル
	{
		goto LABEL_END;
	}

	// 要求データの取得
	if (ERROR_SUCCESS != PdhCollectQueryData(hQuery))
	{
		goto LABEL_END;
	}
	if (0 < dwSleepMilliSecond)
	{
		Sleep(dwSleepMilliSecond);
		if (ERROR_SUCCESS != PdhCollectQueryData(hQuery))
		{
			goto LABEL_END;
		}
	}

LABEL_END:
	PDH_FMT_COUNTERVALUE	fmtValue;

	PdhGetFormattedCounterValue(hCounter, dwFormat, NULL, &fmtValue);

	bResult = true;

	PdhRemoveCounter(hCounter);
	PdhCloseQuery(hQuery);
	if (false == bResult)
	{	// 失敗
		//assert( !"失敗" );
		return false;
	}

	// 成功
	switch (dwFormat)
	{
	case PDH_FMT_LONG:
		if (dwValueSize != sizeof(LONG))
		{
			//assert( !"受け取る値の型の種類に対して値受け取りバッファーのサイズが不正" );
			return false;
		}
		else
		{
			LONG* plValue = (LONG*)pValue;
			*plValue = fmtValue.longValue;
		}
		break;
	case PDH_FMT_DOUBLE:
		if (dwValueSize != sizeof(double))
		{
			//assert( !"受け取る値の型の種類に対して値受け取りバッファーのサイズが不正" );
			return false;
		}
		else
		{
			double* pdValue = (double*)pValue;
			*pdValue = fmtValue.doubleValue;

		}
		break;
	case PDH_FMT_ANSI:
	case PDH_FMT_UNICODE:
	case PDH_FMT_LARGE:
	default:
		//assert( !"未対応" );
		return false;
	}
	return true;
}