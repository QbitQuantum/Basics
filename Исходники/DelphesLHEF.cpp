int main(int argc, char *argv[])
{
  char appName[] = "DelphesLHEF";
  stringstream message;
  FILE *inputFile = 0;
  TFile *outputFile = 0;
  TStopwatch readStopWatch, procStopWatch;
  ExRootTreeWriter *treeWriter = 0;
  ExRootTreeBranch *branchEvent = 0, *branchWeight = 0;
  ExRootConfReader *confReader = 0;
  Delphes *modularDelphes = 0;
  DelphesFactory *factory = 0;
  TObjArray *stableParticleOutputArray = 0, *allParticleOutputArray = 0, *partonOutputArray = 0;
  DelphesLHEFReader *reader = 0;
  Int_t i, maxEvents, skipEvents;
  Long64_t length, eventCounter;

  if(argc < 3)
  {
    cout << " Usage: " << appName << " config_file" << " output_file" << " [input_file(s)]" << endl;
    cout << " config_file - configuration file in Tcl format," << endl;
    cout << " output_file - output file in ROOT format," << endl;
    cout << " input_file(s) - input file(s) in LHEF format," << endl;
    cout << " with no input_file, or when input_file is -, read standard input." << endl;
    return 1;
  }

  signal(SIGINT, SignalHandler);

  gROOT->SetBatch();

  int appargc = 1;
  char *appargv[] = {appName};
  TApplication app(appName, &appargc, appargv);

  try
  {
    outputFile = TFile::Open(argv[2], "CREATE");

    if(outputFile == NULL)
    {
      message << "can't create output file " << argv[2];
      throw runtime_error(message.str());
    }

    treeWriter = new ExRootTreeWriter(outputFile, "Delphes");

    branchEvent = treeWriter->NewBranch("Event", LHEFEvent::Class());
    branchWeight = treeWriter->NewBranch("Weight", Weight::Class());

    confReader = new ExRootConfReader;
    confReader->ReadFile(argv[1]);

    maxEvents = confReader->GetInt("::MaxEvents", 0);
    skipEvents = confReader->GetInt("::SkipEvents", 0);

    if(maxEvents < 0)
    {
      throw runtime_error("MaxEvents must be zero or positive");
    }

    if(skipEvents < 0)
    {
      throw runtime_error("SkipEvents must be zero or positive");
    }

    modularDelphes = new Delphes("Delphes");
    modularDelphes->SetConfReader(confReader);
    modularDelphes->SetTreeWriter(treeWriter);

    factory = modularDelphes->GetFactory();
    allParticleOutputArray = modularDelphes->ExportArray("allParticles");
    stableParticleOutputArray = modularDelphes->ExportArray("stableParticles");
    partonOutputArray = modularDelphes->ExportArray("partons");

    reader = new DelphesLHEFReader;

    modularDelphes->InitTask();

    i = 3;
    do
    {
      if(interrupted) break;

      if(i == argc || strncmp(argv[i], "-", 2) == 0)
      {
        cout << "** Reading standard input" << endl;
        inputFile = stdin;
        length = -1;
      }
      else
      {
        cout << "** Reading " << argv[i] << endl;
        inputFile = fopen(argv[i], "r");

        if(inputFile == NULL)
        {
          message << "can't open " << argv[i];
          throw runtime_error(message.str());
        }

        fseek(inputFile, 0L, SEEK_END);
        length = ftello(inputFile);
        fseek(inputFile, 0L, SEEK_SET);

        if(length <= 0)
        {
          fclose(inputFile);
          ++i;
          continue;
        }
      }

      reader->SetInputFile(inputFile);

      ExRootProgressBar progressBar(length);

      // Loop over all objects
      eventCounter = 0;
      treeWriter->Clear();
      modularDelphes->Clear();
      reader->Clear();
      readStopWatch.Start();
      while((maxEvents <= 0 || eventCounter - skipEvents < maxEvents) &&
        reader->ReadBlock(factory, allParticleOutputArray,
        stableParticleOutputArray, partonOutputArray) && !interrupted)
      {
        if(reader->EventReady())
        {
          ++eventCounter;

          readStopWatch.Stop();

          if(eventCounter > skipEvents)
          {
            readStopWatch.Stop();
            procStopWatch.Start();
            modularDelphes->ProcessTask();
            procStopWatch.Stop();

            reader->AnalyzeEvent(branchEvent, eventCounter, &readStopWatch, &procStopWatch);
            reader->AnalyzeWeight(branchWeight);

            treeWriter->Fill();

            treeWriter->Clear();
          }

          modularDelphes->Clear();
          reader->Clear();

          readStopWatch.Start();
        }
        progressBar.Update(ftello(inputFile), eventCounter);
      }

      fseek(inputFile, 0L, SEEK_END);
      progressBar.Update(ftello(inputFile), eventCounter, kTRUE);
      progressBar.Finish();

      if(inputFile != stdin) fclose(inputFile);

      ++i;
    }
    while(i < argc);

    modularDelphes->FinishTask();
    treeWriter->Write();

    cout << "** Exiting..." << endl;

    delete reader;
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