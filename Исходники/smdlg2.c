static void
/*FCN*/OnGroupNew (
  ButtoN b
){
  Int2 i;
  Char newName[64];

  GetTitle ( groupDialog, &(newName[0]), 64 );
  if ( newName[0] == 0 ) return;
  newName[63] = 0;
  for ( i=1; i<=totalGroups; i++ ){
    if ( StringCmp ( (CharPtr)Nlm_GetMuskCParamEd(MSM_GROUPS,
                      i,MSM_STRING), &(newName[0]) ) == 0 ) return;
  }
  MemMove ( &(groupAr[1]), &(groupAr[0]), totalGroups*sizeof(Int2) );
  totalGroups++;
  nHideGroups++;
  groupAr[0] = totalGroups;
  Nlm_SetMuskCParamEd(MSM_GROUPS,MSM_NOSUBCLASS,MSM_NUM,(BigScalar)totalGroups);
  Nlm_SetMuskCParamEd(MSM_GROUPS,totalGroups,MSM_STRING,(BigScalar)&(newName[0]));
  curGroupInd = 0;
  FillGroupList(TRUE);
  SetGroupValue ( curGroupInd );
  FillFeatPopup(TRUE);
  LoadFeatureArray();
  FillFeatList(TRUE);
  if ( totalFeatures == 0 ){
    curFeatureInd = -1;
  } else {
    curFeatureInd = 0;
    SetFeatValue ( curFeatureInd );
  }
  UpdateDlgControls();
  SaveGroupArray();
}