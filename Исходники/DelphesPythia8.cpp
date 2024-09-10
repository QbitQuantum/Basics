int main(int argc, char *argv[])
{
  char appName[] = "DelphesPythia8";
  stringstream message;
  TFile *outputFile = 0;
  TStopwatch readStopWatch, procStopWatch;
  ExRootTreeWriter *treeWriter = 0;
  ExRootTreeBranch *branchEvent = 0;
  ExRootConfReader *confReader = 0;
  Delphes *modularDelphes = 0;
  DelphesFactory *factory = 0;
  TObjArray *stableParticleOutputArray = 0, *allParticleOutputArray = 0, *partonOutputArray = 0;
  Long64_t eventCounter, errorCounter;
  Long64_t numberOfEvents, timesAllowErrors;

  Pythia8::Pythia *pythia = 0;

  if(argc != 4)
  {
    cout << " Usage: " << appName << " config_file" << " pythia_card" << " output_file" << endl;
    cout << " config_file - configuration file in Tcl format," << endl;
    cout << " pythia_card - Pythia8 configuration file," << endl;
    cout << " output_file - output file in ROOT format." << endl;
    return 1;
  }

  signal(SIGINT, SignalHandler);

  gROOT->SetBatch();

  int appargc = 1;
  char *appargv[] = {appName};
  TApplication app(appName, &appargc, appargv);

  try
  {
    outputFile = TFile::Open(argv[3], "CREATE");

    if(outputFile == NULL)
    {
      message << "can't create output file " << argv[3];
      throw runtime_error(message.str());
    }

    treeWriter = new ExRootTreeWriter(outputFile, "Delphes");

    branchEvent = treeWriter->NewBranch("Event", HepMCEvent::Class());

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

    // Initialize pythia
    pythia = new Pythia8::Pythia;

    if(pythia == NULL)
    {
      throw runtime_error("can't create Pythia instance");
    }

    // Read in commands from configuration file
    pythia->readFile(argv[2]);

    // Extract settings to be used in the main program
    numberOfEvents = pythia->mode("Main:numberOfEvents");
    timesAllowErrors = pythia->mode("Main:timesAllowErrors");

    pythia->init();

    // ExRootProgressBar progressBar(numberOfEvents - 1);
    ExRootProgressBar progressBar(-1);

    // Loop over all events
    errorCounter = 0;
    treeWriter->Clear();
    modularDelphes->Clear();
    readStopWatch.Start();
    for(eventCounter = 0; eventCounter < numberOfEvents && !interrupted; ++eventCounter)
    {
      if(!pythia->next())
      {
        // If failure because reached end of file then exit event loop
        if (pythia->info.atEndOfFile())
        {
          cerr << "Aborted since reached end of Les Houches Event File" << endl;
          break;
        }

        // First few failures write off as "acceptable" errors, then quit
        if (++errorCounter < timesAllowErrors) continue;
        cerr << "Event generation aborted prematurely, owing to error!" << endl;
        break;
      }

      readStopWatch.Stop();

      procStopWatch.Start();
      ConvertInput(eventCounter, pythia, branchEvent, factory,
        allParticleOutputArray, stableParticleOutputArray, partonOutputArray,
        &readStopWatch, &procStopWatch);
      modularDelphes->ProcessTask();
      procStopWatch.Stop();

      treeWriter->Fill();

      treeWriter->Clear();
      modularDelphes->Clear();

      readStopWatch.Start();
      progressBar.Update(eventCounter, eventCounter);
    }

    progressBar.Update(eventCounter, eventCounter, kTRUE);
    progressBar.Finish();

    pythia->statistics();

    modularDelphes->FinishTask();
    treeWriter->Write();

    cout << "** Exiting..." << endl;

    delete pythia;
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