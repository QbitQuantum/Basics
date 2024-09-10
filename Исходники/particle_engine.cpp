/*
====================
MsgCreateSystem

====================
*/
int CParticleEngine::MsgCreateSystem( const char *pszName, int iSize, void *pbuf ) 
{
	BEGIN_READ(pbuf, iSize);

	vec3_t pos;
	pos.x = READ_COORD();
	pos.y = READ_COORD();
	pos.z = READ_COORD();

	vec3_t ang;
	ang.x = READ_COORD();
	ang.y = READ_COORD();
	ang.z = READ_COORD();

	int iType = READ_BYTE();
	char *szPath = READ_STRING();
	int iId = READ_SHORT();

	if(iType == 2)
		RemoveSystem(iId);
	else if(iType == 1)
		CreateCluster(szPath, pos, ang, iId);
	else
		CreateSystem(szPath, pos, ang, iId);

	return 1;
}