int cCombatManager::GetClosestThreat(float3 Pos, UnitInfo* U)
{
    sWeaponEfficiency* weTemp;
    float distance,fTemp;
    distance=0.0f;
    float3 fE;
    set<int> deletion;
    for( map<int,EnemyInfo*>::iterator E=G->EThreat.begin(); E!=G->EThreat.end(); ++E )
    {
        fE=GetEnemyPosition(E->first,E->second);
        if( E->second->baseThreatFrame > cb->GetCurrentFrame()+3600 ||
                (E->second->baseThreatFrame > cb->GetCurrentFrame()+1200 && G->UImmobile.find(E->second->baseThreatID) == G->UImmobile.end() ) ||
                (E->second->ud != 0 && G->UImmobile.find(E->second->baseThreatID) != G->UImmobile.end() && 1.3*E->second->ud->maxWeaponRange < fE.distance(cb->GetUnitPos(E->second->baseThreatID)) ) )
        {
            E->second->baseThreatID = -1;
            E->second->baseThreatFrame = -1;
            deletion.insert(E->first);
        }
        else if( (weTemp = CanAttack(U,E->second,fE)) != 0 )
        {
            fTemp=Pos.distance(fE);
            if( U->enemyID == -1 || fTemp < distance )
            {
                U->enemyID=E->first;
                U->E = E->second;
                U->enemyEff = weTemp;
                distance=fTemp;
            }
        }
    }
    while( int(deletion.size()) > 0 )
    {
        if( !G->UM->ActiveAttackOrders() )
        {
            EnemyInfo* E = G->EThreat.find(*deletion.begin())->second;
            while( int(E->attackGroups.size()) > 0 )
                G->UM->GroupRemoveEnemy(*deletion.begin(),E,*E->attackGroups.begin());
        }
        G->EThreat.erase(*deletion.begin());
        deletion.erase(*deletion.begin());
    }
    if( U->enemyID != -1 && U->group != 0 )
        G->UM->GroupAddEnemy(U->enemyID,U->E,U->group);
    return U->enemyID;
}