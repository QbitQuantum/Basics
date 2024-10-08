//     const char*   cDataType      = "AOD",       // set the analysis type, AOD or ESD
//##################################################
AliAnalysisManager* EmcalJetCDF (
    const char*   cRunPeriod     = "LHC11d",    // set the run period
    const char*   cLocalFiles    = "data.txt",  // set the local list file
    const Int_t   arg_sel_chg    = 3145763,   // "mykEMC_noGA",  // physics selection
    const Int_t   arg_sel_full   = 3145763,   // "mykEMC_noGA",  // physics selection
    const Int_t   mgr_mode       = 0,         // local = 0, proof = 1, grid = 2, mixing = 3
    const Int_t   alien_mode     = 0,         // test = 0, offline = 1, submit = 2, merge = 3, full = 4
    const char*   cTaskName      = "CDFJets",   // sets name of task manager
    unsigned int  iNumFiles      = 100,         // numger of files to process from list file
    unsigned int  iNumEvents     = 999999999,   // number of events to be analyzed
    bool          bDoChargedJets = true,        // enable charge jets
    bool          bDoFullJets    = false        // enable full jets
) {
//Load needed libs
TString     ListLibs      = ""; // string list of loaded libs
TString     ListLibsExtra = ""; // string list of loaded extra libs
LoadLibs( ListLibs, ListLibsExtra );

AnalysisType  ManagerMode = static_cast<AnalysisType>(mgr_mode);
PluginType    PluginMode  = static_cast<PluginType>(alien_mode);

namespace CDF = PWGJE::EMCALJetTasks::AliAnalysisTaskEmcalJetCDF_NS; // shortcut to task namespace
unsigned int       kGridFilesPerJob         = iNumFiles;      // Maximum number of files per job (gives size of AOD)
unsigned int       kTTL                     = 64800 ;         // Time To Live; 18h = 64800; 12h = 43200

bool bDoBackgroundSubtraction = true;
bool bDoEmbedding = false;

// Embeded Configuration options
// Embedding files list
const TString embeddedFilesList = "aodFilesEmbed.txt";
// If true, events that are not selected in the PbPb will not be used for embedding.
// This ensures that good embedded events are not wasted on bad PbPb events.
const bool internalEventSelection = true;
// Do jet matching
const bool useJetTagger = true;


TString sGridMode ("test");
if ( PluginMode == PluginType::offline ) { sGridMode = "offline"; }
if ( PluginMode == PluginType::submit )  { sGridMode = "submit"; }
if ( PluginMode == PluginType::merge )   { sGridMode = "merge"; }
if ( PluginMode == PluginType::full )    { sGridMode = "full"; }
const char* cGridMode = sGridMode.Data();

TString sAnalysisType ("local");
if ( ManagerMode == AnalysisType::proof )  { sAnalysisType = "proof"; }
if ( ManagerMode == AnalysisType::grid )   { sAnalysisType = "grid"; }
if ( ManagerMode == AnalysisType::mixing ) { sAnalysisType = "mix"; }
const char* cAnalysisType = sAnalysisType.Data();

cout << std::endl << ">>>>>>>> ManagerMode : " << ManagerMode << " ; String value : " << cAnalysisType << std::endl << ">>>>>>>> PluginMode : " << PluginMode << " ; String value : " << cGridMode << std::endl << std::endl;

//---------------------------------------------------------------------------------------------
TRegexp false_regex ("[f,F][a,A][l,L][s,S][e,E]");
TRegexp true_regex ("[t,T][r,R][u,U][e,E]");
TRegexp enable_regex ("[e,E][n,N][a,A][b,B][l,L][e,E]");
TRegexp disable_regex ("[d,D][i,I][s,S][a,A][b,B][l,L][e,E]");

bool  bDoSample = false;
TString ENV_doSAMPLE = gSystem->Getenv("CDF_doSAMPLE");
if (!ENV_doSAMPLE.IsNull() && ( ENV_doSAMPLE.EqualTo("0") || ENV_doSAMPLE.Contains(false_regex) ) ) { bDoSample = kFALSE; }
if (!ENV_doSAMPLE.IsNull() && ( ENV_doSAMPLE.EqualTo("1") || ENV_doSAMPLE.Contains(true_regex)  ) ) { bDoSample = kTRUE; }

bool  bDoCDF    = true;
TString ENV_doCDF = gSystem->Getenv("CDF_doCDF");
if (!ENV_doCDF.IsNull() && ( ENV_doCDF.EqualTo("0") || ENV_doCDF.Contains(false_regex) ) ) { bDoCDF = kFALSE; }
if (!ENV_doCDF.IsNull() && ( ENV_doCDF.EqualTo("1") || ENV_doCDF.Contains(true_regex)  ) ) { bDoCDF = kTRUE; }

// ######   DEBUG    ######
Int_t           debug              =  0 ; // kFatal = 0, kError, kWarning, kInfo, kDebug, kMaxType
UInt_t          mgr_debug          =  0 ; // AliAnalysisManager debug level
UInt_t          kUseSysInfo        =  0 ; // activate debugging

TString ENV_DEBUG = gSystem->Getenv("CDF_DEBUG");
if (!ENV_DEBUG.IsNull() && ENV_DEBUG.IsDigit() ) { debug = ENV_DEBUG.Atoi(); }

TString ENV_DEBUG_MGR = gSystem->Getenv("CDF_DEBUG_MGR");
if (!ENV_DEBUG_MGR.IsNull() && ENV_DEBUG_MGR.IsDigit() ) { mgr_debug = ENV_DEBUG_MGR.Atoi(); }

TString ENV_NSYSINFO = gSystem->Getenv("CDF_NSYSINFO");
if (!ENV_NSYSINFO.IsNull() && ENV_NSYSINFO.IsDigit() ) { kUseSysInfo = ENV_NSYSINFO.Atoi(); }

if ( debug == 0 ) { AliLog::SetGlobalLogLevel ( AliLog::kFatal   ); }
if ( debug == 1 ) { AliLog::SetGlobalLogLevel ( AliLog::kError   ); }
if ( debug == 2 ) { AliLog::SetGlobalLogLevel ( AliLog::kWarning ); }
if ( debug == 3 ) { AliLog::SetGlobalLogLevel ( AliLog::kInfo    ); }
if ( debug >= 4 ) { AliLog::SetGlobalLogLevel ( AliLog::kDebug   ); }

// Progress bar
Bool_t bUseProgBar = kFALSE; // N.B. !! if true will set fDebug to 0
TString ENV_USEPROGBAR = gSystem->Getenv("PROGRESSBAR");
if (!ENV_USEPROGBAR.IsNull() && ( ENV_USEPROGBAR.EqualTo("1") || ENV_USEPROGBAR.Contains(true_regex) ) )  { bUseProgBar = kTRUE; }

//##################################################
//        AliEN plugin variables
//##################################################
const char* curdir = gSystem->BaseName(gSystem->pwd());
TString     kJobTag (curdir);

TString execArgs (" -l -b -q -x");
TString exec =
//               "aliroot";
              "root.exe";

TString     kPluginExecutableCommand = exec + execArgs;

TString     kAliPhysicsVersion       = "vAN-20190304-1";

// == grid plugin files rules
TString     kGridExtraFiles          = ""; // extra files that will be added to the input list in the JDL
TString     kGridMergeExclude        = "AliAOD.root AliAOD.Jets.root"; // Files that should not be merged
TString     kGridOutputStorages      = "disk=2"; // Make replicas on the storages

// FILES USED IN MACRO
TString     kCommonOutputFileName    = "AnalysisResults.root";

//--------------------
//   PROOF SETTINGS
//--------------------
TString kAAF        = "";
Int_t   kProofReset = 0; (void)kProofReset;
Int_t   kWorkers    = 20; (void)kWorkers;
Int_t   kCores      = 8  ; (void)kCores;
// AliRoot mode among the list supported by the proof cluster.
// TString     kAlirootMode             = "ALIROOT";     // STEERBase,ESD,AOD,ANALYSIS,ANALYSISalice (default aliroot mode)

//############################################################
// const AliAnalysisTaskEmcal::EDataType_t kAod = AliAnalysisTaskEmcal::kAOD;
// const AliAnalysisTaskEmcal::EDataType_t kEsd = AliAnalysisTaskEmcal::kESD;

const AliJetContainer::EJetType_t    fulljet = AliJetContainer::kFullJet;
const AliJetContainer::EJetType_t     chgjet = AliJetContainer::kChargedJet;
const AliJetContainer::EJetAlgo_t     antikt = AliJetContainer::antikt_algorithm;
const AliJetContainer::EJetAlgo_t         kt = AliJetContainer::kt_algorithm;
const AliJetContainer::ERecoScheme_t  recomb = AliJetContainer::pt_scheme;

// kTPC, kTPCfid, kEMCAL, kEMCALfid, kDCAL, kDCALfid, kDCALonly, kDCALonlyfid, kPHOS, kPHOSfid, kUser
const AliEmcalJet::JetAcceptanceType acc_chgjets  = AliEmcalJet::kTPCfid;
const AliEmcalJet::JetAcceptanceType acc_fulljets = AliEmcalJet::kEMCALfid;
//############################################################

// data source name
TString kDataSource (cLocalFiles);

// label of dataset from InputData.C
TString kGridDataSet ("");
if ( ManagerMode == AnalysisType::grid ) { kGridDataSet = kDataSource;}

//############################################################
// SETUP OF TRIGGERS
const AliEmcalPhysicsSelection::EOfflineEmcalTypes mykEMCAL  = AliEmcalPhysicsSelection::kEmcalOk;
const AliVEvent::EOfflineTriggerTypes  mykEMC             = static_cast<AliVEvent::EOfflineTriggerTypes>(AliVEvent::kEMC1 | AliVEvent::kEMC7 | AliVEvent::kEMC8 | AliVEvent::kEMCEJE | AliVEvent::kEMCEGA);
const AliVEvent::EOfflineTriggerTypes  mykEMC_noGA        = static_cast<AliVEvent::EOfflineTriggerTypes>(AliVEvent::kEMC1 | AliVEvent::kEMC7 | AliVEvent::kEMC8 | AliVEvent::kEMCEJE);

const AliVEvent::EOfflineTriggerTypes  mykMB              = AliVEvent::kAnyINT;
const AliVEvent::EOfflineTriggerTypes  mykMB_central      = static_cast<AliVEvent::EOfflineTriggerTypes>(AliVEvent::kAnyINT | AliVEvent::kCentral);
const AliVEvent::EOfflineTriggerTypes  mykMB_semicentral  = static_cast<AliVEvent::EOfflineTriggerTypes>(AliVEvent::kAnyINT | AliVEvent::kSemiCentral);
const AliVEvent::EOfflineTriggerTypes  mykMB_mostcentral  = static_cast<AliVEvent::EOfflineTriggerTypes>(AliVEvent::kAnyINT | AliVEvent::kCentral | AliVEvent::kSemiCentral);

AliVEvent::EOfflineTriggerTypes kPhysSel   = mykMB; //AliVEvent::kAnyINT; // physics selection
// AliVEvent::EOfflineTriggerTypes kSel_tasks = mykMB;

AliVEvent::EOfflineTriggerTypes kSel_chg   = static_cast<AliVEvent::EOfflineTriggerTypes>(arg_sel_chg);
AliVEvent::EOfflineTriggerTypes kSel_full  = static_cast<AliVEvent::EOfflineTriggerTypes>(arg_sel_full);

//############################################################
// Analysis manager
  AliAnalysisManager* pMgr = new AliAnalysisManager(cTaskName);
  pMgr->SetDebugLevel(mgr_debug);
  if ( kUseSysInfo > 0 ) { pMgr->SetNSysInfo ( kUseSysInfo ); }

  // actual runName in the form of LHCXXX....
  TString sRunName;
  Bool_t kIsAOD = kTRUE;
  AliAnalysisTaskEmcal::EDataType_t iDataType = AliAnalysisTaskEmcal::kAOD; // assuming default is to process AOD
  TString file;
  AliAnalysisAlien* plugin = NULL;
  if ( ManagerMode == AnalysisType::grid ) {  // start grid analysis
    // ( const char* gridMode, const char* tag, unsigned int nr_test_files, unsigned int TTL, const char* outdir, const char subworkdir, const char* extradirlvl);
    plugin = CreateAlienHandler(cGridMode, kJobTag.Data(), kGridFilesPerJob, kTTL);
    if ( !plugin ) { ::Error ( "runEMCalJetSampleTask.C - StartGridAnalysis", "plugin invalid" ); return NULL; }
    pMgr->SetGridHandler(plugin);

    // use this command to run the macro
    plugin->SetExecutableCommand(kPluginExecutableCommand.Data());

    // AliPhysics version.
    plugin->SetAliPhysicsVersion ( kAliPhysicsVersion.Data() ); // Here you can set the (Ali)PHYSICS version you want to use

    gROOT->LoadMacro("InputData.C");
    InputData(kGridDataSet);
    sRunName = CDF::GetPeriod( plugin->GetGridDataDir() );

    file = CDF::GetFileFromPath(plugin->GetDataPattern());
    if (file.Contains("AliESD")) { iDataType = AliAnalysisTaskEmcal::kESD; kIsAOD = kFALSE; }

    plugin->SetMergeExcludes(kGridMergeExclude.Data());
    }

  if ( ManagerMode == AnalysisType::local ) { // start local analysis
    if ( kDataSource.IsNull() ) { Printf("You need to provide the list of local files!"); return NULL; }
    TChain* pChain = CDF::CreateChain(kDataSource.Data(), "auto", "", iNumFiles);
    if (!pChain) { std::cout << ">>>>>>>>>>>>>>   CHAIN NOT CREATED   <<<<<<<<<<<<<<" << std::endl; return NULL; }
    Printf("Setting local analysis for %d files from list %s, max events = %d", iNumFiles, kDataSource.Data(), iNumEvents);

    // get the path of first file
    file = pChain->GetFile()->GetEndpointUrl()->GetUrl();
    sRunName = CDF::GetPeriod(file.Data()); // get the run name : first token beggining with lhc
    if ( CDF::GetFileFromPath(file).Contains("AliESD") ) { iDataType = AliAnalysisTaskEmcal::kESD; kIsAOD = kFALSE; }
    }

  TString sDataType ("AOD");
  if (!kIsAOD) { sDataType = "ESD"; }
  std::cout << ">>> Analysis data type : " << sDataType.Data() << std::endl;

  // name of de period (for MC is the name of "achored to" production)
  TString sRunPeriod (cRunPeriod);
  sRunPeriod.ToLower();

  bool isMC = false;
  isMC = CDF::PeriodIsMC(sRunName.Data());

  // EMCAL corrections task configuration file
  TString EMCALcfg ("CDF_CorrectionsConf.yaml");
  if (isMC) {EMCALcfg = "CDF_MC_CorrectionsConf.yaml";}

  if ( !kGridExtraFiles.IsNull() ) {kGridExtraFiles += " ";}
  kGridExtraFiles += EMCALcfg;

  AliAnalysisTaskEmcal::BeamType iBeamType = AliAnalysisTaskEmcal::kpp;
  Bool_t bIsRun2 = kFALSE;

  if (sRunPeriod.Length() == 6 && (sRunPeriod.BeginsWith("lhc15") || sRunPeriod.BeginsWith("lhc16") || sRunPeriod.BeginsWith("lhc17") || sRunPeriod.BeginsWith("lhc18") ) ) { bIsRun2 = kTRUE; }

  if (sRunPeriod == "lhc10h" || sRunPeriod == "lhc11h" || sRunPeriod == "lhc15o" || sRunPeriod == "lhc17n" )                            { iBeamType = AliAnalysisTaskEmcal::kAA; }
  if (sRunPeriod == "lhc12g" || sRunPeriod == "lhc13b" || sRunPeriod == "lhc13c" || sRunPeriod == "lhc13d" || sRunPeriod == "lhc13e" ||
      sRunPeriod == "lhc13f" || sRunPeriod == "lhc16q" || sRunPeriod == "lhc16r" || sRunPeriod == "lhc16s" || sRunPeriod == "lhc16t" )  { iBeamType = AliAnalysisTaskEmcal::kpA; }

  Double_t kGhostArea = 0.01;
  if (iBeamType != AliAnalysisTaskEmcal::kpp) { kGhostArea = 0.005; }

  AliTrackContainer::SetDefTrackCutsPeriod(sRunPeriod);
  Printf("Default track cut period set to: %s", AliTrackContainer::GetDefTrackCutsPeriod().Data());

  Bool_t bDoEmcalCorrections  = kFALSE;
  if (bDoFullJets) { bDoEmcalCorrections  = kTRUE; }

// ###   Containers and string definitions
  TString name_tracks   = "usedefault";
  TString name_clusters = "usedefault";
  TString name_cells    = "usedefault";
  // Set centrality estimator for centrality task
  TString cent_est_chg  = "V0M" ;
  TString cent_est_full = "V0M" ;

  TString mc_container ("");
  if (isMC) { mc_container = "mcparticles"; }

/*
  // General input object names
  TString tracksName             = AliEmcalContainerUtils::DetermineUseDefaultName(AliEmcalContainerUtils::kTrack);
  TString clustersName           = AliEmcalContainerUtils::DetermineUseDefaultName(AliEmcalContainerUtils::kCluster);
  TString emcalCellsName         = AliEmcalContainerUtils::DetermineUseDefaultName(AliEmcalContainerUtils::kCaloCells);
  // Combined (PbPb + embedded det level)
  TString emcalCellsCombined = emcalCellsName + "Combined";
  TString clustersCombined = clustersName + "Combined";
*/

//##########################
//   TASKS DEFINITIONS   ###
//##########################
  AliAODInputHandler* pAODHandler = NULL;
  AliESDInputHandler* pESDHandler = NULL;
  if (kIsAOD)
    { pAODHandler = AliAnalysisTaskEmcal::AddAODHandler(); }
  else
    { pESDHandler = AliAnalysisTaskEmcal::AddESDHandler(); }

  // CDBconnect task
  AliTaskCDBconnect* taskCDB = AliTaskCDBconnect::AddTaskCDBconnect();
  taskCDB->SetFallBackToRaw(kTRUE); // Needed for the moment as not all grid sites do support cvmfs OCDB for the moment
  if (!taskCDB) { std::cout << "--------->>>>  taskCDB :: could not connect!!!! CHECK CVMFS" << std::endl; return NULL;}

  // Physics selection task
  AliPhysicsSelectionTask* pPhysSelTask = NULL;
  if (!kIsAOD) {
    // signature : (Bool_t mCAnalysisFlag = kFALSE, Bool_t applyPileupCuts = kFALSE, UInt_t deprecatedFlag2 = 0, Bool_t useSpecialOutput=kFALSE)
    pPhysSelTask = AliPhysicsSelectionTask::AddTaskPhysicsSelection();
    }

  // Centrality task
  // The Run 2 condition is too restrictive, but until the switch to MultSelection is complete, it is the best we can do
  AliCentralitySelectionTask* pCentralityTask = NULL;
  if ( !kIsAOD && (iBeamType != AliAnalysisTaskEmcal::kpp && bIsRun2) ) {
    //signature : (Bool_t fillHistos=kTRUE, Bool_t aod=kFALSE)
    pCentralityTask = AliCentralitySelectionTask::AddTaskCentrality(kFALSE, kIsAOD);
    pCentralityTask->SelectCollisionCandidates(AliVEvent::kAny);
    }

  // AliMultSelection
  AliMultSelectionTask* pMultSelTask = NULL;
  if (bIsRun2) {
    // signature : ( Bool_t lCalibration = kFALSE, TString lExtraOptions = "", Int_t lNDebugEstimators = 1, const TString lMasterJobSessionFlag = "")
    pMultSelTask = AliMultSelectionTask::AddTaskMultSelection();
    pMultSelTask->SelectCollisionCandidates(AliVEvent::kAny);
    }

  // Embedding task
  if (bDoEmbedding) {
    // Debug options
    //AliLog::SetClassDebugLevel("AliAnalysisTaskEmcalEmbeddingHelper", AliLog::kDebug+0);

    // Setup embedding task
    AliAnalysisTaskEmcalEmbeddingHelper * embeddingHelper = AliAnalysisTaskEmcalEmbeddingHelper::AddTaskEmcalEmbeddingHelper();
    embeddingHelper->SelectCollisionCandidates(kPhysSel);
    // The pt hard bin should be set via the filenames in this file
    // If using a file pattern, it could be configured via embeddingHelper->SetPtHardBin(ptHardBin);
    embeddingHelper->SetFileListFilename(embeddedFilesList.Data());

    // Some example settings for LHC12a15e_fix (anchored to LHC11h)
    embeddingHelper->SetNPtHardBins(11);
    embeddingHelper->SetMCRejectOutliers();

    // Setup internal event selection and additional configuration options
    embeddingHelper->SetConfigurationPath("EmbeddingConfigurationExample.yaml");

    // Initialize the task to complete the setup.
    embeddingHelper->Initialize();
    }

  // EMCal corrections
  AliEmcalCorrectionTask* correctionTask = NULL;
  if (bDoEmcalCorrections) {
    // Configuration of the Correction Task is handled via a YAML file, which is setup below
    // signature : (TString suffix)
    correctionTask = AliEmcalCorrectionTask::AddTaskEmcalCorrectionTask();
//  correctionTask = AliEmcalCorrectionTask::ConfigureEmcalCorrectionTaskOnLEGOTrain(suffix);
    correctionTask->SelectCollisionCandidates(kPhysSel);
    correctionTask->SetUseNewCentralityEstimation(bIsRun2);
    correctionTask->SetForceBeamType(static_cast<AliEmcalCorrectionTask::BeamType>(iBeamType));

    // Configure and initialize
    correctionTask->SetUserConfigurationFilename( EMCALcfg.Data() );
    //correctionTask->SetUserConfigurationFilename("alien:///alice/cern.ch/user/m/mfasel/EMCALCorrectionConfig/ConfigDataPWGJEhighClusterThresholds.yaml");
    correctionTask->Initialize(true);

    }

//     TObjArray correctionTasks;
//
//     // Create the Correction Tasks
//     // "data" corresponds to the PbPb level
//     // "embed" corresponds to the embedded detector level
//     // "combined" corresponds to the hybrid (PbPb + embedded detector) level
//     correctionTasks.Add(AliEmcalCorrectionTask::AddTaskEmcalCorrectionTask("data"));
//     correctionTasks.Add(AliEmcalCorrectionTask::AddTaskEmcalCorrectionTask("embed"));
//     // It is important that combined is last!
//     correctionTasks.Add(AliEmcalCorrectionTask::AddTaskEmcalCorrectionTask("combined"));
//
//     // Loop over all of the correction tasks to configure them
//     AliEmcalCorrectionTask * tempCorrectionTask = 0;
//     TIter next(&correctionTasks);
//     while (( tempCorrectionTask = static_cast<AliEmcalCorrectionTask *>(next()))) {
//       tempCorrectionTask->SelectCollisionCandidates(kPhysSel);
//       // Configure centrality
//       tempCorrectionTask->SetNCentBins(5);
//       tempCorrectionTask->SetUseNewCentralityEstimation(bIsRun2);
//       tempCorrectionTask->SetUserConfigurationFilename("$ALICE_PHYSICS/PWGJE/EMCALJetTasks/macros/EMCalCorrectionTaskEmbeddingExample.yaml");
//
//       tempCorrectionTask->Initialize(true);
//       }

  // Background
  TString sRhoChName;
  TString sRhoFuName;
  AliAnalysisTaskRho* pRhoTask = NULL;
  if ( bDoBackgroundSubtraction && iBeamType != AliAnalysisTaskEmcal::kpp ) {
    sRhoChName = "Rho";
    sRhoFuName = "Rho_Scaled";

    AliEmcalJetTask* pKtChJetTask = AliEmcalJetTask::AddTaskEmcalJet(name_tracks.Data(), "", kt, 0.4, chgjet, 0.15, 0, kGhostArea, recomb, "Jet", 0., kFALSE, kFALSE);
    pKtChJetTask->SelectCollisionCandidates(kPhysSel);

    //signature :
    // const char* nTracks = "usedefault", const char* nClusters = "usedefault", const char* nRho = "Rho", Double_t jetradius = 0.2, UInt_t acceptance = AliEmcalJet::kTPCfid,
    // AliJetContainer::EJetType_t jetType = AliJetContainer::kChargedJet, const Bool_t histo = kFALSE, AliJetContainer::ERecoScheme_t rscheme = AliJetContainer::pt_scheme, const char* suffix = ""
    pRhoTask = AliAnalysisTaskRho::AddTaskRhoNew(name_tracks.Data(), name_clusters.Data(), sRhoChName, 0.4);
    pRhoTask->SetExcludeLeadJets(2);
    pRhoTask->SelectCollisionCandidates(kPhysSel);
    pRhoTask->SetRecycleUnusedEmbeddedEventsMode(internalEventSelection);

    if (bDoFullJets) {
      TString sFuncPath = "alien:///alice/cern.ch/user/s/saiola/LHC11h_ScaleFactorFunctions.root";
      TString sFuncName = "LHC11h_HadCorr20_ClustersV2";
      pRhoTask->LoadRhoFunction(sFuncPath, sFuncName);
      }
    }

  // Find Charged jets
  AliEmcalJetTask* pChJet02Task = NULL;
  AliEmcalJetTask* pChJet04Task = NULL;
  AliEmcalJetTask* pChJet02Task_MC = NULL;
  AliEmcalJetTask* pChJet04Task_MC = NULL;
  if (bDoChargedJets) {
    pChJet02Task = AliEmcalJetTask::AddTaskEmcalJet(name_tracks.Data(), "", antikt, 0.2, chgjet, 0.15, 0, kGhostArea, recomb, "Jet", 1., kFALSE, kFALSE);
    pChJet02Task->SelectCollisionCandidates(kSel_chg);

    pChJet04Task = AliEmcalJetTask::AddTaskEmcalJet(name_tracks.Data(), "", antikt, 0.4, chgjet, 0.15, 0, kGhostArea, recomb, "Jet", 1., kFALSE, kFALSE);
    pChJet04Task->SelectCollisionCandidates(kSel_chg);

    if (isMC) {
      pChJet02Task_MC = AliEmcalJetTask::AddTaskEmcalJet(mc_container.Data(), "", antikt, 0.2, chgjet, 0.15, 0, kGhostArea, recomb, "Jet", 1., kFALSE, kFALSE);
      pChJet02Task_MC->SelectCollisionCandidates(kSel_chg);
      if (bDoEmbedding) {
        pChJet02Task_MC->SetRecycleUnusedEmbeddedEventsMode(internalEventSelection);
        AliParticleContainer* partLevelTracks02Task_MC = pChJet02Task_MC->GetParticleContainer(0);
        // Called Embedded, but really just means get from an external event!
        partLevelTracks02Task_MC->SetIsEmbedding(kTRUE);
        }

      pChJet04Task_MC = AliEmcalJetTask::AddTaskEmcalJet(mc_container.Data(), "", antikt, 0.4, chgjet, 0.15, 0, kGhostArea, recomb, "Jet", 1., kFALSE, kFALSE);
      pChJet04Task_MC->SelectCollisionCandidates(kSel_chg);
      if (bDoEmbedding) {
        pChJet04Task_MC->SetRecycleUnusedEmbeddedEventsMode(internalEventSelection);
        AliParticleContainer* partLevelTracks04Task_MC = pChJet04Task_MC->GetParticleContainer(0);
        // Called Embedded, but really just means get from an external event!
        partLevelTracks04Task_MC->SetIsEmbedding(kTRUE);
        }
      } // isMC
    } // bDoChargedJets

  // Find Full jets
  AliEmcalJetTask* pFuJet02Task = NULL;
  AliEmcalJetTask* pFuJet04Task = NULL;
  AliEmcalJetTask* pFuJet02Task_MC = NULL;
  AliEmcalJetTask* pFuJet04Task_MC = NULL;
  if (bDoFullJets) {
    pFuJet02Task = AliEmcalJetTask::AddTaskEmcalJet(name_tracks.Data(), name_clusters.Data(), antikt, 0.2, fulljet, 0.15, 0.30, kGhostArea, recomb, "Jet", 1., kFALSE, kFALSE);
    pFuJet02Task->SelectCollisionCandidates(kSel_full);
    pFuJet02Task->GetClusterContainer(0)->SetDefaultClusterEnergy(AliVCluster::kHadCorr);

    pFuJet04Task = AliEmcalJetTask::AddTaskEmcalJet(name_tracks.Data(), name_clusters.Data(), antikt, 0.4, fulljet, 0.15, 0.30, kGhostArea, recomb, "Jet", 1., kFALSE, kFALSE);
    pFuJet04Task->SelectCollisionCandidates(kSel_full);
    pFuJet04Task->GetClusterContainer(0)->SetDefaultClusterEnergy(AliVCluster::kHadCorr);

    if (isMC) {
      pFuJet02Task_MC = AliEmcalJetTask::AddTaskEmcalJet(mc_container.Data(), name_clusters.Data(), antikt, 0.2, fulljet, 0.15, 0, kGhostArea, recomb, "Jet", 1., kFALSE, kFALSE);
      pFuJet02Task_MC->SelectCollisionCandidates(kSel_chg);
      if (bDoEmbedding) {
        pFuJet02Task_MC->SetRecycleUnusedEmbeddedEventsMode(internalEventSelection);
        AliParticleContainer* partLevelTracks02Task_MC = pFuJet02Task_MC->GetParticleContainer(0);
        // Called Embedded, but really just means get from an external event!
        partLevelTracks02Task_MC->SetIsEmbedding(kTRUE);
        }

      pFuJet04Task_MC = AliEmcalJetTask::AddTaskEmcalJet(mc_container.Data(), name_clusters.Data(), antikt, 0.4, fulljet, 0.15, 0, kGhostArea, recomb, "Jet", 1., kFALSE, kFALSE);
      pFuJet04Task_MC->SelectCollisionCandidates(kSel_chg);
      pFuJet04Task_MC->SetRecycleUnusedEmbeddedEventsMode(internalEventSelection);
      if (bDoEmbedding) {
        pFuJet04Task_MC->SetRecycleUnusedEmbeddedEventsMode(internalEventSelection);
        AliParticleContainer* partLevelTracks04Task_MC = pFuJet04Task_MC->GetParticleContainer(0);
        // Called Embedded, but really just means get from an external event!
        partLevelTracks04Task_MC->SetIsEmbedding(kTRUE);
        }
      } // isMC
    } // bDoFullJets

////////////////////////
//   ANALYSIS TASKS   //
////////////////////////

  // Sample task - charge jets
  AliAnalysisTaskEmcalJetSample* sampleTaskchg = NULL;
  if (bDoSample && bDoChargedJets) {
    sampleTaskchg = AliAnalysisTaskEmcalJetSample::AddTaskEmcalJetSample(name_tracks.Data(), "", "", "SMPCHG");
    sampleTaskchg->SetHistoBins(600, 0, 300);
    sampleTaskchg->SelectCollisionCandidates(kSel_chg);
    sampleTaskchg->SetDebugLevel(debug);

    AliParticleContainer* sampleTaskchg_partCont = sampleTaskchg->GetParticleContainer(0);
    sampleTaskchg_partCont->SetParticlePtCut(0.15);

    if (bDoEmbedding) { sampleTaskchg_partCont->SetIsEmbedding(kTRUE); }

    if ( pMultSelTask ) {
      sampleTaskchg->SetUseNewCentralityEstimation(bIsRun2);
      sampleTaskchg->SetNCentBins(5);
      }
    }

  // Sample task - full jets
  AliAnalysisTaskEmcalJetSample* sampleTaskfull = NULL;
  if (bDoSample && bDoFullJets) {
    sampleTaskfull = AliAnalysisTaskEmcalJetSample::AddTaskEmcalJetSample(name_tracks.Data(), name_clusters.Data(), name_cells.Data(), "SMPFULL");
    sampleTaskfull->SetHistoBins(600, 0, 300);
    sampleTaskfull->SelectCollisionCandidates(kSel_full);
    sampleTaskfull->SetDebugLevel(debug);

    AliParticleContainer* sampleTaskfull_partCont = sampleTaskfull->GetParticleContainer(0);
    sampleTaskfull_partCont->SetParticlePtCut(0.15);

    AliClusterContainer* sampleTaskfull_clusCont = sampleTaskfull->GetClusterContainer(0);
    sampleTaskfull_clusCont->SetClusECut(0.);
    sampleTaskfull_clusCont->SetClusPtCut(0.);
    sampleTaskfull_clusCont->SetClusNonLinCorrEnergyCut(0.);
    sampleTaskfull_clusCont->SetClusHadCorrEnergyCut(0.30);
    sampleTaskfull_clusCont->SetDefaultClusterEnergy(AliVCluster::kHadCorr);

    if (bDoEmbedding) {
      sampleTaskfull_partCont->SetIsEmbedding(kTRUE);
      sampleTaskfull_clusCont->SetIsEmbedding(kTRUE);
      }

    if ( pMultSelTask ) {
      sampleTaskfull->SetUseNewCentralityEstimation(bIsRun2);
      sampleTaskfull->SetNCentBins(5);
      }
    }


  //###   CDF task - charged jets
  AliAnalysisTaskEmcalJetCDF* anaTaskCDFchg = NULL;
  AliAnalysisTaskEmcalJetCDF* anaTaskCDFchg_MC = NULL;
  if (bDoCDF && bDoChargedJets) {
    anaTaskCDFchg = CDF::AddTaskEmcalJetCDF ( name_tracks.Data(), "", "", "", "CDFchg" );
    anaTaskCDFchg->SetHistoBins(600, 0, 300);
    anaTaskCDFchg->SelectCollisionCandidates(kSel_chg);
    anaTaskCDFchg->SetDebugLevel(debug);

    AliParticleContainer* anaTaskCDFchg_partCont = anaTaskCDFchg->GetParticleContainer(0);
    anaTaskCDFchg_partCont->SetParticlePtCut(0.15);

    if (bDoEmbedding) { anaTaskCDFchg_partCont->SetIsEmbedding(kTRUE); }

    if ( pMultSelTask ) {
      anaTaskCDFchg->SetUseNewCentralityEstimation(bIsRun2);
      anaTaskCDFchg->SetNCentBins(5);
      anaTaskCDFchg->SetCentralityEstimator(cent_est_chg.Data());
      }

    //#################################################
    if (isMC){
      anaTaskCDFchg_MC = CDF::AddTaskEmcalJetCDF ( mc_container.Data(), "", "", "", "CDFchgMC" );
      anaTaskCDFchg_MC->SetHistoBins(600, 0, 300);
      anaTaskCDFchg_MC->SelectCollisionCandidates(kSel_chg);
      anaTaskCDFchg_MC->SetDebugLevel(debug);

      AliParticleContainer* anaTaskCDFchg_partCont_MC = anaTaskCDFchg_MC->GetMCParticleContainer(0);
      anaTaskCDFchg_partCont->SetParticlePtCut(0.15);

      if (bDoEmbedding) { anaTaskCDFchg_partCont_MC->SetIsEmbedding(kTRUE); }

      if ( pMultSelTask ) {
        anaTaskCDFchg_MC->SetUseNewCentralityEstimation(bIsRun2);
        anaTaskCDFchg_MC->SetNCentBins(5);
        anaTaskCDFchg_MC->SetCentralityEstimator(cent_est_chg.Data());
        }
      }
    }

  //###   CDF task - full jets
  AliAnalysisTaskEmcalJetCDF* anaTaskCDFfull = NULL;
  if (bDoCDF && bDoFullJets) {
    anaTaskCDFfull = CDF::AddTaskEmcalJetCDF ( name_tracks.Data(), name_clusters.Data(), name_cells.Data(), mc_container.Data(), "CDFfull" );
    anaTaskCDFfull->SetHistoBins(600, 0, 300);
    anaTaskCDFfull->SelectCollisionCandidates(kSel_full);
    anaTaskCDFfull->SetDebugLevel(debug);

    AliParticleContainer* anaTaskCDFfull_partCont = anaTaskCDFfull->GetParticleContainer(0);
    anaTaskCDFfull_partCont->SetParticlePtCut(0.15);

    AliClusterContainer* anaTaskCDFfull_clusCont = anaTaskCDFfull->GetClusterContainer(0);
    anaTaskCDFfull_clusCont->SetClusECut(0.);
    anaTaskCDFfull_clusCont->SetClusPtCut(0.);
    anaTaskCDFfull_clusCont->SetClusNonLinCorrEnergyCut(0.);
    anaTaskCDFfull_clusCont->SetClusHadCorrEnergyCut(0.30);
    anaTaskCDFfull_clusCont->SetDefaultClusterEnergy(AliVCluster::kHadCorr);

    if (bDoEmbedding) {
      anaTaskCDFfull_partCont->SetIsEmbedding(kTRUE);
      anaTaskCDFfull_clusCont->SetIsEmbedding(kTRUE);
      }

    if ( pMultSelTask ) {
      anaTaskCDFfull->SetUseNewCentralityEstimation(bIsRun2);
      anaTaskCDFfull->SetNCentBins(5);
      anaTaskCDFfull->SetCentralityEstimator(cent_est_full.Data());
      }
    }

//########################
//   ANALYSIS TASKS - CONTAINERS SETUP
//########################

//   AliEmcalJetTask* pChJet02Task_MC = NULL;
//   AliEmcalJetTask* pChJet04Task_MC = NULL;

// add jet containers to CDF task for charged jets
  if (bDoChargedJets && bDoCDF) {
    AliJetContainer* jetcont_chg = NULL;
    for ( Float_t fi = 0 ; fi<=100 ; fi+=10) {
      // CHG JETS 0.2
      jetcont_chg  = anaTaskCDFchg->AddJetContainer(chgjet, antikt, recomb, 0.2, acc_chgjets, "Jet");
      CDF::jetContSetParams (jetcont_chg,    fi,   fi+10, 0, 0);

      // CHG JETS 0.4
      jetcont_chg  = anaTaskCDFchg->AddJetContainer(chgjet, antikt, recomb, 0.4, acc_chgjets, "Jet");
      CDF::jetContSetParams (jetcont_chg,    fi,   fi+10, 0, 0);

      if (isMC) {
        // CHG JETS MC 0.2
        jetcont_chg = AddJetContainerJetTask(dynamic_cast<AliAnalysisTaskEmcalJetCDF*>(anaTaskCDFchg_MC), pChJet02Task_MC, acc_chgjets);
        CDF::jetContSetParams (jetcont_chg,    fi,   fi+10, 0, 0);

        // CHG JETS MC 0.4
        jetcont_chg = AddJetContainerJetTask(dynamic_cast<AliAnalysisTaskEmcalJetCDF*>(anaTaskCDFchg_MC), pChJet04Task_MC, acc_chgjets);
        CDF::jetContSetParams (jetcont_chg,    fi,   fi+10, 0, 0);
        }
      }

    jetcont_chg   = anaTaskCDFchg->AddJetContainer(chgjet, antikt, recomb, 0.2, acc_chgjets, "Jet");
    CDF::jetContSetParams (jetcont_chg,     1., 500., 0, 0);
    jetcont_chg   = anaTaskCDFchg->AddJetContainer(chgjet, antikt, recomb, 0.4, acc_chgjets, "Jet");
    CDF::jetContSetParams (jetcont_chg,     1., 500., 0, 0);

    if (isMC) {
      jetcont_chg = AddJetContainerJetTask(dynamic_cast<AliAnalysisTaskEmcalJetCDF*>(anaTaskCDFchg_MC), pChJet02Task_MC, acc_chgjets);
      CDF::jetContSetParams (jetcont_chg,     1., 500., 0, 0);

      jetcont_chg = AddJetContainerJetTask(dynamic_cast<AliAnalysisTaskEmcalJetCDF*>(anaTaskCDFchg_MC), pChJet04Task_MC, acc_chgjets);
      CDF::jetContSetParams (jetcont_chg,     1., 500., 0, 0);
      }

    jetcont_chg = NULL;
    }

  // add jet containers to CDF task for full jets
  if (bDoFullJets && bDoCDF) {
    AliJetContainer* jetcont_full = NULL;
    for ( Float_t fi = 0 ; fi<=100 ; fi+=10) {
      // FULL JETS 0.2
      jetcont_full  = anaTaskCDFfull->AddJetContainer(fulljet, antikt, recomb, 0.2, acc_fulljets, "Jet");
      CDF::jetContSetParams (jetcont_full,    fi,   fi+10, 0, 2);

      // FULL JETS 0.4
      jetcont_full  = anaTaskCDFfull->AddJetContainer(fulljet, antikt, recomb, 0.4, acc_fulljets, "Jet");
      CDF::jetContSetParams (jetcont_full,    fi,   fi+10, 0, 2);

      if (isMC) {
        // CHG JETS MC 0.2
        jetcont_full = AddJetContainerJetTask(dynamic_cast<AliAnalysisTaskEmcalJetCDF*>(anaTaskCDFfull_MC), pFuJet02Task_MC, acc_fulljets);
        CDF::jetContSetParams (jetcont_full,    fi,   fi+10, 0, 0);

        // CHG JETS MC 0.4
        jetcont_full = AddJetContainerJetTask(dynamic_cast<AliAnalysisTaskEmcalJetCDF*>(anaTaskCDFfull_MC), pFuJet04Task_MC, acc_fulljets);
        CDF::jetContSetParams (jetcont_full,    fi,   fi+10, 0, 0);
        }
      }

    jetcont_full   = anaTaskCDFfull->AddJetContainer(fulljet, antikt, recomb, 0.2, acc_fulljets, "Jet");
    CDF::jetContSetParams (jetcont_full,     1., 500., 0, 2);

    jetcont_full   = anaTaskCDFfull->AddJetContainer(fulljet, antikt, recomb, 0.4, acc_fulljets, "Jet");
    CDF::jetContSetParams (jetcont_full,     1., 500., 0, 2);

    if (isMC) {
      jetcont_full = AddJetContainerJetTask(dynamic_cast<AliAnalysisTaskEmcalJetCDF*>(anaTaskCDFfull_MC), pFuJet02Task_MC, acc_fulljets);
      CDF::jetContSetParams (jetcont_full,     1., 500., 0, 0);

      jetcont_full = AddJetContainerJetTask(dynamic_cast<AliAnalysisTaskEmcalJetCDF*>(anaTaskCDFfull_MC), pFuJet04Task_MC, acc_fulljets);
      CDF::jetContSetParams (jetcont_full,     1., 500., 0, 0);
      }
    jetcont_full = NULL;
    }

  // add jet containers to sample task for charged jets
  if (bDoChargedJets && bDoSample) {
    AliJetContainer* jetCont02chg_sample = sampleTaskchg->AddJetContainer(chgjet, antikt, recomb, 0.2, acc_chgjets, "Jet");
    AliJetContainer* jetCont04chg_sample = sampleTaskchg->AddJetContainer(chgjet, antikt, recomb, 0.4, acc_chgjets, "Jet");

    if (iBeamType != AliAnalysisTaskEmcal::kpp) {
      jetCont02chg_sample->SetRhoName(sRhoChName);
      jetCont02chg_sample->SetPercAreaCut(0.6);

      jetCont04chg_sample->SetRhoName(sRhoChName);
      jetCont04chg_sample->SetPercAreaCut(0.6);
      }
    }

  // add jet containers to sample task for full jets
  if (bDoFullJets && bDoSample) {
    AliJetContainer* jetCont02full_sample = sampleTaskfull->AddJetContainer(fulljet, antikt, recomb, 0.2, acc_fulljets, "Jet");
    AliJetContainer* jetCont04full_sample = sampleTaskfull->AddJetContainer(fulljet, antikt, recomb, 0.4, acc_fulljets, "Jet");

    if (iBeamType != AliAnalysisTaskEmcal::kpp) {
      jetCont02full_sample->SetRhoName(sRhoFuName);
      jetCont02full_sample->SetPercAreaCut(0.6);

      jetCont04full_sample->SetRhoName(sRhoFuName);
      jetCont04full_sample->SetPercAreaCut(0.6);
      }
    }


  TObjArray* tasks_list = pMgr->GetTasks(); TIter task_iter (tasks_list); AliAnalysisTaskSE* task = NULL;
  while (( task = dynamic_cast<AliAnalysisTaskSE*>(task_iter.Next()) )) {
    if (task->InheritsFrom("AliAnalysisTaskEmcal")) {
      Printf("Setting beam type %d for task %s", iBeamType, static_cast<AliAnalysisTaskEmcal*>(task)->GetName());
      static_cast<AliAnalysisTaskEmcal*>(task)->SetForceBeamType(iBeamType);
      }
    }

  //   Let's start #########################################################################################################
  if ( !pMgr->InitAnalysis() ) { std::cout << ">>>>>>>>>>>>>> AliAnalysisManager Initialising FAILED!!! " << std::endl; return NULL; }
  std::cout << "##-->> Initialising Analysis :: Status :" << std::endl;
  pMgr->PrintStatus();
  pMgr->SetUseProgressBar(bUseProgBar, 100);

  // task profiling
  if ( kUseSysInfo > 0 ) {
    for ( int i = 0; i < pMgr->GetTopTasks()->GetEntries(); i++ ) { pMgr->ProfileTask (i); }
    }

  CDF::SaveManager("train.root");

  if ( ManagerMode == AnalysisType::local ) { // start local analysis
    // enable class level debugging for these classes
    if ( debug > 2 ) {
    //   pMgr->AddClassDebug("AliJetContainer", 100);
    //   pMgr->AddClassDebug("AliEmcalJetTask", 100);
      if (bDoCDF)    { pMgr->AddClassDebug("AliAnalysisTaskEmcalJetCDF", 100); }
      if (bDoSample) { pMgr->AddClassDebug("AliAnalysisTaskEmcalJetSample", 100); }
      }

    TChain* pChain = CDF::CreateChain(kDataSource.Data(), "auto", "", iNumFiles);
    if (!pChain) { std::cout << ">>>>>>>>>>>>>>   CHAIN NOT CREATED   <<<<<<<<<<<<<<" << std::endl; return NULL; }

    // start analysis
    Printf("Starting LOCAL Analysis...");
    pMgr->StartAnalysis( cAnalysisType, pChain, iNumEvents );
    }

  if ( ManagerMode == AnalysisType::grid ) {  // start grid analysis
    // start analysis
    Printf("Starting GRID Analysis...");

    ListLibs += kGridExtraFiles;
    if ( ListLibs.Length() )       { plugin->SetAdditionalLibs     ( ListLibs.Data() ); }
    if ( ListLibsExtra.Length() )  { plugin->SetAdditionalRootLibs ( ListLibsExtra.Data() ); }

    if ( PluginMode == PluginType::test )
      { plugin->StartAnalysis(iNumEvents); }
    else {
      pMgr->SetDebugLevel(0);
      plugin->StartAnalysis();
      }
    }

cout << "END of EmcalJetCDF.C" << std::endl;
return pMgr;
}