void aiBehaviorAttackTarget::Execute( Ogre::Any& owner )
{
	Unit* pUnit = Ogre::any_cast<Unit*>(owner);
	pUnit->GetPath()->StopAgent();
}