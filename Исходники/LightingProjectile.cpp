CLightingProjectile::CLightingProjectile(const float3& pos,const float3& end,CUnit* owner,const float3& color, WeaponDef *weaponDef,int ttl,CWeapon* weap)
:	CWeaponProjectile(pos,ZeroVector, owner, 0, ZeroVector, weaponDef,0), //CProjectile(pos,ZeroVector,owner),
	ttl(ttl),
	color(color),
	endPos(end),
	weapon(weap)
{
	checkCol=false;
	drawRadius=pos.distance(endPos);

	displacements[0]=0;
	for(int a=1;a<10;++a)
		displacements[a]=(gs->randFloat()-0.5f)*drawRadius*0.05f;

	displacements2[0]=0;
	for(int a=1;a<10;++a)
		displacements2[a]=(gs->randFloat()-0.5f)*drawRadius*0.05f;

	if(weapon)
		AddDeathDependence(weapon);

#ifdef TRACE_SYNC
	tracefile << "New lighting: ";
	tracefile << pos.x << " " << pos.y << " " << pos.z << " " << end.x << " " << end.y << " " << end.z << "\n";
#endif
}