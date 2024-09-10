//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void CNPC_EnemyFinderCombineCannon::UpdateOnRemove() 
{
	BaseClass::UpdateOnRemove();

	// See if I'm in the list of Combine enemyfinders
	int index = s_ListEnemyfinders.Find(this);
	if( index != -1 )
	{
		s_ListEnemyfinders.Remove(index);
	}
}