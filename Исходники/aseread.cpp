static int ASE_ReadSubModel (CFILE *cfP, tASEModel *pm)
{
	tASESubModelList	*pml;
	tASESubModel		*psm;

if (CharTok (" \t") != '{')
	return ASE_Error ("syntax error");
if (!(pml = (tASESubModelList *) D2_ALLOC (sizeof (tASESubModelList))))
	return ASE_Error ("out of memory");
memset (pml, 0, sizeof (*pml));
pml->pNextModel = pm->pSubModels;
pm->pSubModels = pml;
psm = &pm->pSubModels->sm;
psm->nId = pm->nSubModels++;
psm->nBomb = -1;
psm->nMissile = -1;
psm->nGun = -1;
psm->nGunPoint = -1;
psm->nBullets = -1;
psm->bRender = 1;
psm->nType = 0;
psm->bBarrel = 0;
while ((pszToken = ASE_ReadLine (cfP))) {
	if (*pszToken == '}')
		return 1;
	if (!strcmp (pszToken, "*NODE_NAME")) {
		strcpy (psm->szName, StrTok (" \t\""));
		if (strstr (psm->szName, "$GUNPNT"))
			psm->nGunPoint = atoi (psm->szName + 8);
		if (strstr (psm->szName, "$BULLETS"))
			psm->nBullets = 1;
		else if (strstr (psm->szName, "GLOW") != NULL) 
			psm->bGlow = 1;
		else if (strstr (psm->szName, "$DUMMY") != NULL)
			psm->bRender = 0;
		else if (strstr (psm->szName, "$THRUSTER") != NULL)
			psm->bThruster = 1;
		else if (strstr (psm->szName, "$WINGTIP") != NULL) {
			psm->bWeapon = 1;
			psm->nGun = 0;
			psm->nBomb =
			psm->nMissile = -1;
			psm->nType = atoi (psm->szName + 8) + 1;
			}
		else if (strstr (psm->szName, "$GUN") != NULL) {
			psm->bWeapon = 1;
			psm->nGun = atoi (psm->szName + 4) + 1;
			psm->nWeaponPos = atoi (psm->szName + 6) + 1;
			psm->nBomb =
			psm->nMissile = -1;
			}
		else if (strstr (psm->szName, "$BARREL") != NULL) {
			psm->bWeapon = 1;
			psm->nGun = atoi (psm->szName + 7) + 1;
			psm->nWeaponPos = atoi (psm->szName + 9) + 1;
			psm->nBomb =
			psm->nMissile = -1;
			psm->bBarrel = 1;
			}
		else if (strstr (psm->szName, "$MISSILE") != NULL) {
			psm->bWeapon = 1;
			psm->nMissile = atoi (psm->szName + 8) + 1;
			psm->nWeaponPos = atoi (psm->szName + 10) + 1;
			psm->nGun =
			psm->nBomb = -1;
			}
		else if (strstr (psm->szName, "$BOMB") != NULL) {
			psm->bWeapon = 1;
			psm->nBomb = atoi (psm->szName + 6) + 1;
			psm->nGun =
			psm->nMissile = -1;
			}
		}
	else if (!strcmp (pszToken, "*NODE_PARENT")) {
		strcpy (psm->szParent, StrTok (" \t\""));
		}
	if (!strcmp (pszToken, "*NODE_TM")) {
		if (!ASE_ReadNode (cfP, pm))
			return ASE_Error (NULL);
		}
	else if (!strcmp (pszToken, "*MESH")) {
		if (!ASE_ReadMesh (cfP, pm))
			return ASE_Error (NULL);
		}
	else if (!strcmp (pszToken, "*MATERIAL_REF")) {
		psm->nBitmap = IntTok (" \t");
		}
	}
return ASE_Error ("unexpected end of file");
}