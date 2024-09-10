// Load preference.
void loadPreference() {
  FILE *fp;
  int i, j;
  int version;
#ifdef MACOSX
  if ( NULL == (fp = fopen(pathToPrefFile,"rb")) ) {
#else
  if ( NULL == (fp = fopen(PREF_FILE,"rb")) ) {
#endif
    initHiScore();
    return;
  }
  version = getw(fp);
  if ( version != VERSION_NUM ) {
    initHiScore();
    return;
  }
  for ( i=0 ; i<STAGE_NUM ; i++ ) {
    hiScore.stageScore[i] = getw(fp);
    for ( j=0 ; j<SCENE_NUM ; j++ ) {
      hiScore.sceneScore[i][j] = getw(fp);
    }
  }
  for ( i=0 ; i<ENDLESS_STAGE_NUM ; i++ ) {
    hiScore.stageScore[i+STAGE_NUM] = getw(fp);
  }
  hiScore.stage = getw(fp);
  fclose(fp);
}

// Save preference.
void savePreference() {
  FILE *fp;
  int i, j;
#ifdef MACOSX
  if ( NULL == (fp = fopen(pathToPrefFile,"wb")) ) return;
#else
  if ( NULL == (fp = fopen(PREF_FILE,"wb")) ) return;
#endif
  putw(VERSION_NUM, fp);
  for ( i=0 ; i<STAGE_NUM ; i++ ) {
    putw(hiScore.stageScore[i], fp);
    for ( j=0 ; j<SCENE_NUM ; j++ ) {
      putw(hiScore.sceneScore[i][j], fp);
    }
  }
  for ( i=0 ; i<ENDLESS_STAGE_NUM ; i++ ) {
    putw(hiScore.stageScore[i+STAGE_NUM], fp);
  }
  putw(hiScore.stage, fp);
  fclose(fp);
}