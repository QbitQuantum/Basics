int main(int argc, char *argv[])
{
  char appName[] = "DelphesCMSFWLite";
  stringstream message;
  TFile *inputFile = 0;
  TFile *outputFile = 0;
  TStopwatch eventStopWatch;
  ExRootTreeWriter *treeWriter = 0;
  ExRootTreeBranch *branchEvent = 0, *branchRwgt = 0;
  ExRootConfReader *confReader = 0;
  Delphes *modularDelphes = 0;
  DelphesFactory *factory = 0;
  TObjArray *allParticleOutputArray = 0, *stableParticleOutputArray = 0, *partonOutputArray = 0;
  Int_t i;
  Long64_t eventCounter, numberOfEvents;

  if(argc < 4)
  {
    cout << " Usage: " << appName << " config_file" << " output_file" << " input_file(s)" << endl;
    cout << " config_file - configuration file in Tcl format," << endl;
    cout << " output_file - output file in ROOT format," << endl;
    cout << " input_file(s) - input file(s) in ROOT format." << endl;
    return 1;
  }

  signal(SIGINT, SignalHandler);

  gROOT->SetBatch();

  int appargc = 1;
  char *appargv[] = {appName};
  TApplication app(appName, &appargc, appargv);

  FWLiteEnabler::enable();
  
  try
  {
    outputFile = TFile::Open(argv[2], "CREATE");

    if(outputFile == NULL)
    {
      message << "can't open " << argv[2] << endl;
      throw runtime_error(message.str());
    }

    treeWriter = new ExRootTreeWriter(outputFile, "Delphes");

    branchEvent = treeWriter->NewBranch("Event", HepMCEvent::Class());
    branchRwgt = treeWriter->NewBranch("Rwgt", Weight::Class());

    confReader = new ExRootConfReader;
    confReader->ReadFile(argv[1]);

    modularDelphes = new Delphes("Delphes");
    modularDelphes->SetConfReader(confReader);
    modularDelphes->SetTreeWriter(treeWriter);

    factory = modularDelphes->GetFactory();
    allParticleOutputArray = modularDelphes->ExportArray("allParticles");
    stableParticleOutputArray = modularDelphes->ExportArray("stableParticles");
    partonOutputArray = modularDelphes->ExportArray("partons");

    modularDelphes->InitTask();

    for(i = 3; i < argc && !interrupted; ++i)
    {
      cout << "** Reading " << argv[i] << endl;

      inputFile = TFile::Open(argv[i]);

      if(inputFile == NULL)
      {
        message << "can't open " << argv[i] << endl;
        throw runtime_error(message.str());
      }

      fwlite::Event event(inputFile);

      numberOfEvents = event.size();

      if(numberOfEvents <= 0) continue;

      // ExRootProgressBar progressBar(numberOfEvents - 1);
      ExRootProgressBar progressBar(-1);

      // Loop over all objects
      eventCounter = 0;
      modularDelphes->Clear();
      treeWriter->Clear();
      for(event.toBegin(); !event.atEnd() && !interrupted; ++event)
      {
        ConvertInput(event, eventCounter, branchEvent, branchRwgt, factory,
          allParticleOutputArray, stableParticleOutputArray, partonOutputArray);
        modularDelphes->ProcessTask();

        treeWriter->Fill();

        modularDelphes->Clear();
        treeWriter->Clear();

        progressBar.Update(eventCounter, eventCounter);
        ++eventCounter;
      }

      progressBar.Update(eventCounter, eventCounter, kTRUE);
      progressBar.Finish();

      inputFile->Close();
    }

    modularDelphes->FinishTask();
    treeWriter->Write();

    cout << "** Exiting..." << endl;

    delete modularDelphes;
    delete confReader;
    delete treeWriter;
    delete outputFile;

    return 0;
  }
  catch(runtime_error &e)
  {
    if(treeWriter) delete treeWriter;
    if(outputFile) delete outputFile;
    cerr << "** ERROR: " << e.what() << endl;
    return 1;
  }
}