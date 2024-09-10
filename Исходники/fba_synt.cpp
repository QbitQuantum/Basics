INT16 CGEN_PUBLIC CFBAproc::AdjustSpeechRate(CData *idPitch, CData *idNewPitch, CData* idFea, CData* idNewFea, FLOAT32 rate) {
  INT16  bVoiced    = FALSE;
  INT32   i          = 0;
  INT32   k          = 0;
  INT32   nCount     = 0;
  INT32   nStartL    = 0;
  FLOAT32  nMeanPeriodLengthL  = 0.0;
  FLOAT32  nMeanPeriodLength   = 0.0;
  CData* idVoiced   = NULL;
  CData* idAuxP     = NULL;
  CData* idAuxF     = NULL;

  // Validation
  if(idPitch == NULL)       return IERROR(this,ERR_NULLINST,0,0,0);
  if(idPitch->IsEmpty())    return IERROR(idPitch,DATA_EMPTY,idPitch->m_lpInstanceName,0,0);
  if
  (
    idPitch->GetNComps()!=2                            ||
    !dlp_is_numeric_type_code(idPitch->GetCompType(0)) ||
    !dlp_is_numeric_type_code(idPitch->GetCompType(1))
  )
  {
    return IERROR(this,FBA_BADARG,idPitch,"idPitch","contains invalid data.");
  }

  // Initialization
  CREATEVIRTUAL(CData,idPitch,idNewPitch);
  CREATEVIRTUAL(CData,idFea,idNewFea);
  ICREATEEX(CData,idVoiced,"~idVoiced",NULL);
  ICREATEEX(CData,idAuxP  ,"~idAuxP"  ,NULL);
  ICREATEEX(CData,idAuxF  ,"~idAuxF"  ,NULL);
  idNewPitch->Reset();
  idVoiced->AddComp("start",T_INT);
  idVoiced->AddComp("count",T_INT);
  idVoiced->AddComp("mplen",T_FLOAT);
  idVoiced->Alloc(10);

  AlignFramesToPitch(idPitch, idFea, idFea);

  // Determine start and length of voiced parts and mean of periods in samples
  for(i=0; i<idPitch->GetNRecs(); i++)
  {
    if(idPitch->Dfetch(i,1)>0)
    {
      if(bVoiced==FALSE)    // Start of new voiced segment
      {
        bVoiced=TRUE;
        nStartL=i;
        nMeanPeriodLengthL=0;
        if(idVoiced->GetNRecs()==idVoiced->GetMaxRecs())
          idVoiced->Realloc(idVoiced->GetNRecs()+10);
        idVoiced->IncNRecs(1);
        idVoiced->Dstore(i,idVoiced->GetNRecs()-1,0);
      }
      nMeanPeriodLength+=(INT32)idPitch->Dfetch(i,0);
      nMeanPeriodLengthL+=(INT32)idPitch->Dfetch(i,0);
      nCount++;
    }
    else if(bVoiced==TRUE)  // End of voiced segment
    {
      bVoiced=FALSE;
      nMeanPeriodLengthL=nMeanPeriodLengthL/(FLOAT32)(i-nStartL);
      idVoiced->Dstore(i-nStartL,idVoiced->GetNRecs()-1,1);
      idVoiced->Dstore(nMeanPeriodLengthL,idVoiced->GetNRecs()-1,2);
    }
  }
  nMeanPeriodLength=nMeanPeriodLength/(FLOAT32)nCount;

  IFCHECK idVoiced->Print();
  IFCHECK printf("\n Input mean period length in voiced parts: %f",nMeanPeriodLength);

  // Resample
  for(i=0,nStartL=0; i<idVoiced->GetNRecs(); i++)
  {
    INT32 j       = 0;
    INT32 nSum    = 0;
    INT32 nRecOld = 0;
    INT32 nRecNew = 0;

    // Copy unvoiced
    idAuxP->SelectRecs(idPitch,nStartL,(INT32)idVoiced->Dfetch(i,0)-nStartL);
    idNewPitch->Cat(idAuxP);
    idAuxF->SelectRecs(idFea,nStartL,(INT32)idVoiced->Dfetch(i,0)-nStartL);
    idNewFea->Cat(idAuxF);
    nStartL=(INT32)idVoiced->Dfetch(i,0)+(INT32)idVoiced->Dfetch(i,1);

    // Resample voiced
    idAuxP->SelectRecs(idPitch,(INT32)idVoiced->Dfetch(i,0),(INT32)idVoiced->Dfetch(i,1));
    nRecOld = idAuxP->GetNRecs();

    for(j=0,nSum=0;j<nRecOld;j++) nSum+=(INT32)idAuxP->Dfetch(j,0);  // Target sum

    idAuxP->Resample(idAuxP, rate);

    nRecNew = idAuxP->GetNRecs();

    for(j=0;j<nRecNew;j++) {
      INT32 tmp = (INT32)idAuxP->Dfetch(j,0);
      tmp = (INT32)MAX(m_nSrate/500, tmp);
      tmp = (INT32)MIN(m_nSrate/50, tmp);
      idAuxP->Dstore(tmp,j,0);
    }

    //idAux->Fill_Int(1.0,0.0,1);
    for(k=0;k<nRecNew;k++) idAuxP->Dstore(1.0,k,1);

    for(k=0;k<nRecNew;k++) {
      j = (INT32)((FLOAT64)k * (FLOAT64)nRecOld / (FLOAT64)nRecNew + 0.5);
      idAuxF->SelectRecs(idFea,j+(INT32)idVoiced->Dfetch(i,0),1);
      idNewFea->Cat(idAuxF);
    }

    idNewPitch->Cat(idAuxP);
  }

  // Append last unvoiced segment
  nStartL = (INT32)idVoiced->Dfetch(idVoiced->GetNRecs()-1,0)+(INT32)idVoiced->Dfetch(idVoiced->GetNRecs()-1,1);
  idAuxP->SelectRecs(idPitch,nStartL,idPitch->GetNRecs()-nStartL);
  idNewPitch->Cat(idAuxP);
  idAuxF->SelectRecs(idFea,nStartL,idPitch->GetNRecs()-nStartL);
  idNewFea->Cat(idAuxF);


  DESTROYVIRTUAL(idPitch,idNewPitch);
  DESTROYVIRTUAL(idFea,idNewFea);
  IDESTROY(idVoiced);
  IDESTROY(idAuxP);
  IDESTROY(idAuxF);

  return O_K;
}