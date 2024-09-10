bool CBoulder::CheckCollision(IBaseInterface* pObject)
{
	RECT rectCollisionResult = { 0, 0, 0, 0 };
	CBaseObject* pBaseObject = (CBaseObject*)pObject;
	if(IntersectRect(&rectCollisionResult, &GetCollisionRect().GetWindowsRECT(), &pBaseObject->GetCollisionRect().GetWindowsRECT()))
	{
		if(pObject->GetType() == TYPE_CHAR_ENEMY)
		//	((CEnemy*)pObject)->SufferDamage(CPlayer::GetInstance()->GetAttackDamage());

		//if(pObject->GetType() != TYPE_CHAR_PLAYER && pObject->GetType() != TYPE_WEAPON_ARROW)
		//{
		//	CMessageSystem::GetInstance()->SendMsg(new CDestroyObjectMessage(this));
		//}
		return true;
	}
	return false;
}