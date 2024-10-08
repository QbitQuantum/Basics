void runCalibSummary(TString runNumberString ="0")
{

  Int_t irun = runNumberString.Atoi();

  // Load libraries
  gSystem->Load("libANALYSIS");
  gSystem->Load("libTPCcalib");

  // Configure OCDB
  gROOT->LoadMacro("ConfigOCDB.C");
  ConfigOCDB(irun);

  // run extraction of the calibration summary ...
  AliTPCcalibSummary *calibSummary = new AliTPCcalibSummary;
  calibSummary->ProcessRun(irun);
  delete calibSummary;

  return;
}