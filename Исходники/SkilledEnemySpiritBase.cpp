/*---------------------------------------------------------------------*//**
	スキルフレーム処理 - 距離チェック
**//*---------------------------------------------------------------------*/
bool SkilledEnemySpiritBase::execCheckReach(ExecRes* res, const ExecCtx* ec, s32 step, s32 cntStep, f32 frmcntStep)
{
	if(_reachSq > 0.0f)
	{
		const Unit* unitTrg = getFocusUnit();
		if(unitTrg == 0L) { return true; }
		Vector3F posTrg = *unitTrg->getPosition();
		Vector3F diffSelfToEne = posTrg - *getThisUnit()->getPosition();
		if(diffSelfToEne.lengthSq() > _reachSq)
		{
			return true;
		}
	}

	return false;	// 継続
}