/*---------------------------------------------------------------------*//**
	開始
**//*---------------------------------------------------------------------*/
bool ModelViewMode::notifyBegin(void* objParamRef)
{
	// パラメータ取得
	GameModeParam* gmparam = (GameModeParam*)objParamRef;
	if(TFW_IS_FLAG(gmparam->getFlags(), GameModeParam::F_DEBUG_MODEL_VIEW_FILE1))		{	_param = 1;	}
	else if(TFW_IS_FLAG(gmparam->getFlags(), GameModeParam::F_DEBUG_MODEL_VIEW_FILE2))	{	_param = 2;	}
	else if(TFW_IS_FLAG(gmparam->getFlags(), GameModeParam::F_DEBUG_MODEL_VIEW_FILE3))	{	_param = 3;	}
	if(gmparam != 0L)	{	gmparam->clearFlags();	}

	// 制御モード開始
	beginActMode(AMODE_MODEL, true);

	// クリアカラー設定
	Vector4F* colorClear = Game::getGame()->getTfw()->getRenderer()->clearColor();
	colorClear->set(0.5f, 0.5f, 0.5f, 1.0f);

	// 値の初期化
	_dispCnt = 0;

	return true;
}