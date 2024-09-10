/*---------------------------------------------------------------------*//**
	終了
**//*---------------------------------------------------------------------*/
void PrpzlPlayMode::notifyEnd(void* objParamRef)
{
	// カメラを破棄
	if(_camRef != 0L)
	{
		SorSgm* sgm = Game::getGame()->getSceneGraph();
		sgm->removeNode(_camRef);
		_camRef = 0L;
	}

	// クリアカラー設定を戻す
	Vector4F* colorClear = Game::getGame()->getTfw()->getRenderer()->clearColor();
	colorClear->set(0.0f, 0.0f, 0.0f, 0.0f);

	// パズルモジュールの終了と削除
	if(_pzl != 0L)
	{
		_pzl->end();
		delete _pzl;
		_pzl = 0L;
		delete _perf;
		_perf = 0L;
	}
}