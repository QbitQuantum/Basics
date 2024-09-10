void getScaleFactors()
{
  MakeElectronFR("fakerates_trigger_Moriond13_ewksub");
  MakeElectronFR("fakerates_trigger_Moriond13_ewksub_jet15");
  MakeElectronFR("fakerates_trigger_Moriond13_ewksub_jet50");

  Invert("prompt_rateMuons",     "effDATA_prompt_rate",      "MuPR");
  Invert("prompt_rateElectrons", "effDATA_All_selec",        "ElePR");
  Invert("allMuonsSF",           "muonsDATAMCratio_all",     "MuSF");
  Invert("allElectronsSF",       "electronsDATAMCratio_all", "EleSF");

  Invert("prompt_rateMuons_Moriond13",     "effDATA_prompt_rate", "MuPR_Moriond13");
  Invert("prompt_rateElectrons_Moriond13", "effDATA_All_selec",   "ElePR_Moriond13");
}