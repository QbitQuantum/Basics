int CMD_EQFace(int argc, char *argv[])
{
//VOID Face(PSPAWNINFO pChar, PCHAR szLine)
//{
    if (!ppSpawnManager) return 0;
    if (!pSpawnList) return 0;
    PSPAWNINFO pSpawnClosest = NULL;
    PSPAWNINFO psTarget = NULL;
    SPAWNINFO LocSpawn = {0};
   PSPAWNINFO pChar = (PSPAWNINFO)pLocalPlayer;
    SEARCHSPAWN SearchSpawn;
    ClearSearchSpawn(&SearchSpawn);
    CHAR szMsg[MAX_STRING] = {0};
    CHAR szName[MAX_STRING] = {0};
    CHAR szArg[MAX_STRING] = {0};
   PCHAR pszArg = NULL;
    BOOL bArg = TRUE;
    BOOL bOtherArgs = FALSE;
    BOOL Away = FALSE;
    BOOL Predict = FALSE;
    BOOL Fast = FALSE;
    BOOL Look = TRUE;
    BOOL Parsing = TRUE;
    DOUBLE Distance;

   for(int qq=1; qq<argc; qq++)
   {
      if (!strcmp(argv[qq],"predict")) {
         Predict=TRUE;
      } else if (!strcmp(argv[qq],"fast")) {
         Fast = TRUE;
      } else if (!strcmp(argv[qq],"away")) {
         Away = TRUE;
      } else if (!strcmp(argv[qq],"nolook")) {
         Look = FALSE;
      } else if (!strnicmp(argv[qq], "loc", 3)) {
         pSpawnClosest = &LocSpawn;
         strcpy(LocSpawn.Name,"location");
         if (((++qq)<argc) && strstr(argv[qq],","))
         {
             pSpawnClosest->Y = (FLOAT)atof(argv[qq]);
            pszArg = strstr(argv[qq],",")+1;
              pSpawnClosest->X = (FLOAT)atof(pszArg);
         }
      } else if (!stricmp(argv[qq], "item")) {
         if (EnviroTarget.Name[0]==0) {
            printf("%s: item specified but no item targetted.", argv[0]);
            return 0;
         }
         pSpawnClosest = &EnviroTarget;
      }
	  else if (!stricmp(argv[qq], "door")) {
		  if (DoorEnviroTarget.Name[0] == 0) {
			  printf("%s: door specified but no door targetted.", argv[0]);
			  return 0;
		  }
		  pSpawnClosest = &DoorEnviroTarget;
      } else if (!strcmp(szArg,"help")) {
         printf("Usage: %s [spawn] [item] [door] [id #] [heading <ang>] [loc <y>,<x>] [away] [alert #]",argv[0]);
         return 0;
      } else {
         bOtherArgs = TRUE;
         qq+=ParseSearchSpawnArg(qq,argc,argv,SearchSpawn);
//         szFilter = ParseSearchSpawnArgs(szArg,szFilter,&SearchSpawn);
      }
   }

   if (!pSpawnClosest) {
      if (!bOtherArgs) {
         if (ppTarget && pTarget) {
            pSpawnClosest = (PSPAWNINFO)pTarget;
         }
      } else {
         pSpawnClosest = SearchThroughSpawns(&SearchSpawn,pChar);
      }
   }

   szMsg[0]=0;

   if (!pSpawnClosest) {
	   printf("There were no matches for: %s", FormatSearchSpawn(szArg, sizeof(szArg), &SearchSpawn));
   } else {
      if (Predict) {
         Distance = DistanceToSpawn(pChar, pSpawnClosest);
         gFaceAngle = (
            atan2((pSpawnClosest->X + (pSpawnClosest->SpeedX * Distance)) - pChar->X,
            (pSpawnClosest->Y + (pSpawnClosest->SpeedY * Distance)) - pChar->Y)
            * 256.0f / PI);
      } else {
         gFaceAngle = (
            atan2(pSpawnClosest->X - pChar->X,
            pSpawnClosest->Y - pChar->Y)
            * 256.0f / PI);
      }
      if (Look) {
         Distance = DistanceToSpawn(pChar, pSpawnClosest);
         gLookAngle = (
            atan2(pSpawnClosest->Z + pSpawnClosest->AvatarHeight*StateHeightMultiplier(pSpawnClosest->StandState) - pChar->Z - pChar->AvatarHeight*StateHeightMultiplier(pChar->StandState),
            (FLOAT)Distance)
            * 256.0f / PI);
         if (Away) gLookAngle = -gLookAngle;
         if (Fast) {
            pChar->CameraAngle = (FLOAT)gLookAngle;
            gLookAngle=10000.0f;
         }
      }
      if (Away) {
         gFaceAngle += 256.0f;
      }
      if (gFaceAngle>=512.0f) gFaceAngle -= 512.0f;
      if (gFaceAngle<0.0f) gFaceAngle += 512.0f;
      if (Fast) {
         ((PSPAWNINFO)pCharSpawn)->Heading = (FLOAT)gFaceAngle;
         gFaceAngle=10000.0f;
      }
      sprintf(szMsg,"Facing %s'%s'...",(Away)?"away from ":"", CleanupName(strcpy(szName,pSpawnClosest->Name),FALSE));
   }
   if (ppTarget && pTarget) {
      psTarget = (PSPAWNINFO)pTarget;
   }
   if (szMsg[0] && ((pSpawnClosest != &LocSpawn) && ((Away) || (pSpawnClosest != psTarget)))) WriteChatColor(szMsg,USERCOLOR_WHO);
   DebugSpew("Face - %s",szMsg);
   return 0;
}