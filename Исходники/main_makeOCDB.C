void main_makeOCDB(Int_t runNumber, TString  targetOCDBstorage="", TString sourceOCDBstorage="raw://", Int_t detectorBitsQualityFlag = -1)
{
  //
  // extract OCDB entries for detectors participating in the calibration for the current run
  //

  // switch off log info
  AliLog::SetClassDebugLevel("AliESDEvent",0);

  // config GRP
  printf("runNumber from runCalibTrain = %d\n",runNumber);
  ConfigCalibTrain(runNumber, sourceOCDBstorage.Data());

  // check the presence of the detectors
  AliCDBEntry* entry = AliCDBManager::Instance()->Get("GRP/GRP/Data");
  AliGRPObject* grpData = dynamic_cast<AliGRPObject*>(entry->GetObject());
  if (!grpData) {printf("Failed to get GRP data for run %d",runNumber); return;}
  Int_t activeDetectors = grpData->GetDetectorMask();
  TString detStr = AliDAQ::ListOfTriggeredDetectors(activeDetectors);
  printf("Detectors in the data:\n%s\n",detStr.Data());
  TString LHCperiod = grpData->GetLHCPeriod();
  Bool_t isLHC10 =  LHCperiod.Contains("LHC10");
  Bool_t isLHC11 =  LHCperiod.Contains("LHC11");
  Bool_t isLHC12 =  LHCperiod.Contains("LHC12");
  Bool_t isLHC13 =  LHCperiod.Contains("LHC13");
  Bool_t isLHC13b =  LHCperiod.Contains("LHC13b");
  Bool_t isLHC13c =  LHCperiod.Contains("LHC13c");
  printf("LHCperiod:%s\n isLHC10:%d isLHC11:%d isLHC12:%d isLHC13:%d isLHC13b:%d isLHC13c:%d\n",LHCperiod.Data(),(Int_t)isLHC10,(Int_t)isLHC11,(Int_t)isLHC12,(Int_t)isLHC13,(Int_t)isLHC13b,(Int_t)isLHC13c);
  TString beamtype=grpData->GetBeamType();

  // Steering Tasks - set output storage
  // DefaultStorage set already before - in ConfigCalibTrain.C

  // Setting the mirror SEs for the default storage
  TString mirrorsStr(gSystem->Getenv("MIRRORSE") ? gSystem->Getenv("MIRRORSE") : "ALICE::CERN::OCDB,ALICE::FZK::SE,ALICE::CNAF::SE");
  AliCDBManager::Instance()->SetMirrorSEs(mirrorsStr.Data());
  printf("List of mirror SEs set to: \"%s\"\n",mirrorsStr.Data());

  // activate target OCDB storage
  AliCDBStorage* targetStorage = 0x0;
  if (targetOCDBstorage.Length()==0) {
    targetOCDBstorage+="local://"+gSystem->GetFromPipe("pwd")+"/OCDB";
    targetStorage = AliCDBManager::Instance()->GetStorage(targetOCDBstorage.Data());
  }
  else if (targetOCDBstorage.CompareTo("same",TString::kIgnoreCase) == 0 ){
    targetStorage = AliCDBManager::Instance()->GetDefaultStorage();
  }
  else {
    targetStorage = AliCDBManager::Instance()->GetStorage(targetOCDBstorage.Data());
  }
  printf("** targetOCDBstorage: \"%s\"\n",targetOCDBstorage.Data());

  // specific storage for TPC/Calib/Correction entry
  if (gSystem->AccessPathName("TPC", kFileExists)==0) {  
    AliCDBManager::Instance()->SetSpecificStorage("TPC/Calib/Correction","local://");
  }

  // Magnetic field
  AliMagF* fld = (AliMagF*)TGeoGlobalMagField::Instance()->GetField();
  Double_t bz = fld->SolenoidField();
  Bool_t isMagFieldON = kTRUE;
  if (TMath::Abs(bz)>0) {
    printf("Mag field is %f --> ON\n", bz);
  }
  else {
    isMagFieldON = kFALSE;
    printf("Mag field is %f --> OFF\n", bz);
  }

  // Quality flags
  Bool_t TPC_qf = kTRUE;
  Bool_t TOF_qf = kTRUE;
  Bool_t TRD_qf = kTRUE;
  Bool_t T0_qf  = kTRUE;
  Bool_t SDD_qf = kTRUE;
  Bool_t SPD_qf = kTRUE;
  Bool_t AD_qf  = kTRUE;

  /*
    // RS: commenting to sync with working version from alidaq
  if (detectorBitsQualityFlag != -1){
    TPC_qf = ((detectorBitsQualityFlag & AliDAQ::kTPC_QF) == AliDAQ::kTPC_QF)? kTRUE : kFALSE;
    TOF_qf = ((detectorBitsQualityFlag & AliDAQ::kTOF_QF) == AliDAQ::kTOF_QF)? kTRUE : kFALSE;
    TRD_qf = ((detectorBitsQualityFlag & AliDAQ::kTRD_QF) == AliDAQ::kTRD_QF)? kTRUE : kFALSE;
    T0_qf  = ((detectorBitsQualityFlag & AliDAQ::kT0_QF)  == AliDAQ::kT0_QF)?  kTRUE : kFALSE;
    SDD_qf = ((detectorBitsQualityFlag & AliDAQ::kSDD_QF) == AliDAQ::kSDD_QF)? kTRUE : kFALSE;
    SPD_qf = ((detectorBitsQualityFlag & AliDAQ::kSPD_QF) == AliDAQ::kSPD_QF)? kTRUE : kFALSE;
    AD_qf = ((detectorBitsQualityFlag & AliDAQ::kAD_QF) == AliDAQ::kAD_QF)? kTRUE : kFALSE;
  }    
  */

  Printf("Quality flags: detectorBitsQualityFlag = %d, TPC = %d, TOF = %d, TRD = %d, T0 = %d, SDD = %d, SPD = %d, AD = %d", detectorBitsQualityFlag, (Int_t)TPC_qf, (Int_t)TOF_qf, (Int_t)TRD_qf, (Int_t)T0_qf, (Int_t)SDD_qf, (Int_t)SPD_qf, (Int_t)AD_qf);

  // ===========================================================================
  // ===| TPC part |============================================================
  //
  AliTPCPreprocessorOffline *procesTPC = 0;
  if (detStr.Contains("TPC") && TPC_qf){
    Printf("\n******* Calibrating TPC *******");

    // ===| set up residual storage |===========================================
    TString targetStorageResidual="local://"+gSystem->GetFromPipe("pwd")+"/OCDB";

    // --- check for overwrites
    const TString targetStorageResidualEnv(gSystem->Getenv("targetStorageResidual"));
    if (!targetStorageResidualEnv.IsNull())  targetStorageResidual=targetStorageResidualEnv;
    AliCDBStorage *residualStorage = AliCDBManager::Instance()->GetStorage(targetStorageResidual.Data());

    // ===| set up TPC calibration object |=====================================
    procesTPC = new AliTPCPreprocessorOffline;

    // ---| set up gain calibratin type |---------------------------------------
    //
    // default is Combined Calibration + Residual QA in CPass1
    // will be overwritte by mergeMakeOCDB.byComponent.perStage.sh
    // NOTE: This must be consistent to the settings in runCPass*.sh (runCalibTrain.C)
    //
    procesTPC->SetGainCalibrationType(AliTPCPreprocessorOffline::kResidualGainQA);

    // --- check for overwrites from environment variable
    //
    const TString sGainTypeFromEnv(gSystem->Getenv("TPC_CPass1_GainCalibType"));
    if (!sGainTypeFromEnv.IsNull()) {
      if (!procesTPC->SetGainCalibrationType(sGainTypeFromEnv)) {
        ::Fatal("makeOCDB","Could not set up gain calibration type from environment variable TPC_CPass1_GainCalibType: %s",sGainTypeFromEnv.Data());
      }

      ::Info("makeOCDB","Setting gain calibration type from environment variable TPC_CPass1_GainCalibType: %d", Int_t(procesTPC->GetGainCalibrationType()));
    }

    // ---| switch on parameter validation |------------------------------------
    procesTPC->SetTimeGainRange(0.5,5.0);

    if(beamtype=="A-A"){
      procesTPC->SetMinTracksVdrift(100000);
    }else{
      procesTPC->SetMinTracksVdrift(10000);
      if(LHCperiod.Contains("LHC16")) procesTPC->SetMaxVDriftCorr(0.2); 
    }
    procesTPC->SwitchOnValidation();

    // ===| Run calibration |===================================================
    //
    // ---| Make time gain calibration |----------------------------------------
    if (isMagFieldON) procesTPC->CalibTimeGain("CalibObjects.root", runNumber, runNumber, targetStorage, residualStorage);

    // ---| Make vdrift calibration |-------------------------------------------
    // ---| Disabling: now the vdrift is done in the TPC SP calibration process (but the input is still available in the CalibObjects.root file, if needed
    // procesTPC->CalibTimeVdrift("CalibObjects.root",runNumber, runNumber, residualStorage);
  }
  else {
    Printf("\n******* NOT Calibrating TPC: detStr = %s, TPC_qf = %d *******", detStr.Data(), (Int_t)TPC_qf);
  }

  // ===========================================================================
  // ===| TOF part |============================================================
  //
  AliTOFAnalysisTaskCalibPass0 *procesTOF=0;
  if (detStr.Contains("TOF") && detStr.Contains("TPC") && TOF_qf){
    procesTOF = new AliTOFAnalysisTaskCalibPass0;
    Printf("\n******* Calibrating TOF *******");
    if (isMagFieldON) procesTOF->ProcessOutput("CalibObjects.root", targetStorage);
    else {
      printf("Not calibrating TOF in case of mag field OFF\n");
    }
  }
  else {
    Printf("\n******* NOT Calibrating TOF: detStr = %s, TOF_qf = %d *******", detStr.Data(), (Int_t)TOF_qf);
  }

  // T0 part
  AliT0PreprocessorOffline *procesT0= 0;
  if (detStr.Contains("T0") && T0_qf) {
    Printf("\n******* Calibrating T0 *******");
    procesT0 = new AliT0PreprocessorOffline;
    // Make  calibration of channels offset
    procesT0->setDArun(100000);
    procesT0->Process("CalibObjects.root",runNumber, runNumber, targetStorage);
  }
  else {
    Printf("\n******* NOT Calibrating T0: detStr = %s, T0_qf = %d *******", detStr.Data(), (Int_t)T0_qf);
  }

  //TRD part
  AliTRDPreprocessorOffline *procesTRD = 0;
  if (detStr.Contains("TRD") && detStr.Contains("TPC") && TRD_qf){
    Printf("\n******* Calibrating TRD *******");
    procesTRD = new  AliTRDPreprocessorOffline;
    if(isLHC10 || isLHC13b || isLHC13c) procesTRD->SetSwitchOnChamberStatus(kFALSE);
    procesTRD->SetLinearFitForVdrift(kTRUE);
    procesTRD->SetMinStatsVdriftT0PH(600*10);
    procesTRD->SetMinStatsVdriftLinear(50);
    procesTRD->SetMinStatsGain(600);
    procesTRD->SetLimitValidateNoData(140);
    procesTRD->SetLimitValidateBadCalib(140);
    procesTRD->SetMinTimeOffsetValidate(-2.1);
    procesTRD->SetAlternativeDriftVelocityFit(kTRUE);
    if((!isLHC10) && (!isLHC11) && (!isLHC12) && (!isLHC13)) {
      printf("Run II\n");
      procesTRD->SetT0Shift1(0.2524132);// release the condition on the first bin and last bins
    }
    procesTRD->Init("CalibObjects.root");
    Int_t versionVdriftUsed = procesTRD->GetVersionVdriftUsed();
    Int_t subversionVdriftUsed = procesTRD->GetSubVersionVdriftUsed();
    Int_t versionGainUsed = procesTRD->GetVersionGainUsed();
    Int_t subversionGainUsed = procesTRD->GetSubVersionGainUsed();
    Int_t versionExBUsed = procesTRD->GetVersionExBUsed();
    Int_t subversionExBUsed = procesTRD->GetSubVersionExBUsed();
    printf("version and subversion vdrift %d and %d\n",versionVdriftUsed,subversionVdriftUsed);
    printf("version and subversion gain %d and %d\n",versionGainUsed,subversionGainUsed);
    printf("version and subversion exb %d and %d\n",versionExBUsed,subversionExBUsed);
    procesTRD->Process("CalibObjects.root",runNumber,runNumber,targetStorage);
  }
  else {
    Printf("\n******* NOT Calibrating TRD: detStr = %s, TRD_qf = %d *******", detStr.Data(), (Int_t)TRD_qf);
  }
  
  //Mean Vertex
  AliMeanVertexPreprocessorOffline * procesMeanVtx=0;
  if (detStr.Contains("ITSSPD") && SPD_qf) {
    Printf("\n******* Calibrating MeanVertex *******");
    procesMeanVtx = new AliMeanVertexPreprocessorOffline;
    procesMeanVtx->ProcessOutput("CalibObjects.root", targetStorage, runNumber);
  }
  else {
    Printf("\n******* NOT Calibrating MeanVertex: detStr = %s, SPD_qf = %d *******", detStr.Data(), (Int_t)SPD_qf);
  }

  AliAnalysisTaskADCalib *procesAD = NULL;
  if (detStr.Contains("AD") && AD_qf) {
    Printf("\n******* Calibrating AD *******");
    procesAD = new AliAnalysisTaskADCalib;
    procesAD->ProcessOutput("CalibObjects.root", targetStorage, runNumber);
  }
  else {
    Printf("\n******* NOT Calibrating AD: detStr = %s, AD_qf = %d*******", detStr.Data(), (Int_t)AD_qf);
  }

  //
  // Print calibration status into the stdout
  //
  Int_t trdStatus = (procesTRD) ?  procesTRD->GetStatus():0;
  Int_t tofStatus = (procesTOF) ?  procesTOF->GetStatus():0;
  Int_t t0Status  = (procesT0)  ?  procesT0->GetStatus():0;
  Int_t tpcStatus = (procesTPC) ?  procesTPC->GetStatus():0;
  Int_t adStatus  = (procesAD)  ?  procesAD->GetStatus():0;
  //
  printf("\n");
  printf("******* CPass1 calibration status *******\n");
  printf("TRD calibration status=%d\n",trdStatus);
  printf("TOF calibration status=%d\n",tofStatus);
  printf("TPC calibration status=%d\n",tpcStatus);
  printf("T0  calibration status=%d\n",t0Status);
  printf("AD  calibration status=%d\n",adStatus);
  
  TTreeSRedirector *pcstream = new TTreeSRedirector("cpassStat.root","recreate");
  printCalibStat(runNumber, "CalibObjects.root",pcstream);
  delete pcstream;
  return;
}