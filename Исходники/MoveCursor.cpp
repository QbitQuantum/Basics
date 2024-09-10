/*---------------------------------------------------------------------*//**
	フレーム制御
**//*---------------------------------------------------------------------*/
void MoveCursor::exec(ExecRes* res, const ExecCtx* ec)
{
	if(TFW_IS_FLAG(_edchFlags, EDCH_EXT_MASK))	{	return;	}	// 外部からの無効化

	// 歩行処理
	GameExecCtx* gec = (GameExecCtx*)ec;
	TouchPanel* ui = gec->getTouchPanel(); 

	bool isEnableSelf = (!gec->isOpenedLockGui()) && (!gec->isLockOperating());
	TFW_SET_FLAG(_edchFlags, EDCH_SELF, !isEnableSelf);
	if(isEnableSelf && !ui->isReacted())
	{
		// 差分を求める
		Vector2F vDiff;
		do
		{
			// 最初にクリックしたとこからの差分で移動
			bool isTouched = _isTouching;
			_isTouching = (ui->getTouchingNum() == 1);
			// タッチ時のポイントを得る
			if(!isTouched && _isTouching)		// タッチした
			{
				ui->getTouchPosition(_ptTouchStart);	// 開始のタッチ位置を得る
				ui->setDragOperating(true);
				_ext->onTapStart(_ptTouchStart);
			}
			else if(isTouched && !_isTouching)	// 離した
			{
				// UI 反応済みフラグを立てるかどうかの判定
				Vector2F vDiff( (f32)(_ptTouchLast->x() - _ptTouchStart->x()), (f32)(_ptTouchLast->y() - _ptTouchStart->y()) );
				f32 lenDiffSq = vDiff.lengthSq();
				if(lenDiffSq >= LEN_MIN_SQ)	// 最小長さを超えている
				{
					ui->setReacted(true);	// 反応済みフラグを立てる
				}

				_ptTouchStart->set(F32_PMAX, F32_PMAX);
				_ptTouchLast->set(F32_PMAX, F32_PMAX);
				_xDiff = 0;
				_yDiff = 0;
				_ext->onTapEnd();
				break;	// 差分計算から抜ける
			}
			if(_isTouching)
			{
				ui->getTouchPosition(_ptTouchLast);		// 現在のタッチ位置を得る
			}

			// 差分を計算する
			vDiff.set( (f32)(_ptTouchLast->x() - _ptTouchStart->x()), (f32)(_ptTouchLast->y() - _ptTouchStart->y()) );
			f32 lenDiffPw = vDiff.lengthSq();
			if(lenDiffPw > LEN_MAX_SQ)	// 最大長さを超えている
			{
				// 最大長さに収める
				vDiff.normalize();
				vDiff *= LEN_MAX;
				// タッチ位置の補正
				_ptTouchLast->x() = _ptTouchStart->x() + (s32)vDiff.x(); 
				_ptTouchLast->y() = _ptTouchStart->y() + (s32)vDiff.y(); 
				ui->setReacted(true);	// 反応済みフラグを立てる
			}
			else if(lenDiffPw < LEN_MIN_SQ)	// 最小長さ未満
			{
				vDiff.set(0.0f, 0.0f);
				_xDiff = 0;
				_yDiff = 0;
				break;	// 差分計算から抜ける
			}
			else
			{
				ui->setReacted(true);	// 反応済みフラグを立てる
			}
			_xDiff = (s32)vDiff.x();
			_yDiff = (s32)vDiff.y();
		}
		while(false);

		// 描画用に角度を得ておく
		Calc::calcAngle(&_angle, vDiff.x(), vDiff.y());
	}
	else if(_isTouching)
	{
		_xDiff = 0;
		_yDiff = 0;
		_isTouching = false;
		_ext->onTapEnd();
	}

	// ２点間の距離を求める
	f32 lenPw = (f32)((_xDiff * _xDiff) + (_yDiff * _yDiff));
	_length = ::sqrtf(lenPw);
	_rateLength = _length / LEN_MAX;

	// 状態を更新する
	if(_length < LEN_WALK)
	{
		_state = STATE_STOP;
	}
	else if(_length < LEN_RUN)
	{
		_state = STATE_WALK;
	}
	else
	{
		_state = STATE_RUN;
	}
}