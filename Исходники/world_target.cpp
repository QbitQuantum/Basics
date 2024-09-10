/////////////////////////////////////
// Name:	WorldTargetAddEnt
// Purpose:	add a target based on given
//			entity parse
// Output:	new target added
// Return:	none
/////////////////////////////////////
void WorldTargetAddEnt(const EntityParse & entityDat)
{
	const tCHAR * pName = entityDat.GetVal(L"targetname");
	wstring theName = pName ? pName : L"NULL";
	Vec3D theLoc(0,0,0);

	//bad target
	if(theName.c_str()[0] == 0)
		return;

	//get location
	if(entityDat.GetVal(L"origin"))
	{
		swscanf(entityDat.GetVal(L"origin"), L"%f %f %f", &theLoc.x, &theLoc.z, &theLoc.y);

		theLoc.z *= -1;
	}

	//add to list
	WorldTargetSet(theName.c_str(), theLoc);
}