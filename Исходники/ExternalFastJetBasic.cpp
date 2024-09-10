int main(int argc, char *argv[])
{
  // Declaration of variables
  ExRootConfReader *confReader = 0;
  Delphes *modularDelphes = 0;
  DelphesFactory *factory = 0;
  TObjArray *allParticleOutputArray = 0;
  TObjArray *stableParticleOutputArray = 0;
  TObjArray *partonOutputArray = 0;

  Int_t event;

  TObjArray *inputArray = 0;
  TIterator *inputIterator = 0;
  Candidate *candidate = 0;
  TLorentzVector momentum;

  JetDefinition *definition = 0;
  vector<PseudoJet> inputList, outputList;
  PseudoJet jet;

  gROOT->SetBatch();

  int appargc = 1;
  char appName[] = "ExternalFastJetBasic";
  char *appargv[] = {appName};
  TApplication app(appName, &appargc, appargv);

  if(argc != 2)
  {
    cout << " Usage: " << appName << " config_file" << endl;
    cout << " config_file - configuration file in Tcl format." << endl;
    return 1;
  }

  try
  {
    // Initialization
    confReader = new ExRootConfReader;
    confReader->ReadFile(argv[1]);

    modularDelphes = new Delphes("Delphes");
    modularDelphes->SetConfReader(confReader);

    factory = modularDelphes->GetFactory();

    allParticleOutputArray = modularDelphes->ExportArray("allParticles");
    stableParticleOutputArray = modularDelphes->ExportArray("stableParticles");
    partonOutputArray = modularDelphes->ExportArray("partons");

    modularDelphes->InitTask();

    
    // fastjet definition
    ClusterSequence::print_banner();
    definition = new JetDefinition(antikt_algorithm, 0.5);
    
    // Define your input candidates to fastjet (by default particle-flow objects).
    // If you want pure calorimeter towers change "EFlowMerger/eflow" into "Calorimeter/towers":
     
    inputArray = modularDelphes->ImportArray("EFlowMerger/eflow");
      
    inputIterator = inputArray->MakeIterator();

    // Event loop
    for(event = 0; event < NEVENTS; ++event)
    {
      modularDelphes->Clear();
      
      // convert EVENT input array into Delphes internal format
      ConvertInput(event, factory, allParticleOutputArray, stableParticleOutputArray, partonOutputArray);
      
      // run Delphes reconstruction
      modularDelphes->ProcessTask();

      inputList.clear();
      inputIterator->Reset();
      
      
      // pass delphes candidates to fastjet clustering  
      while((candidate = static_cast<Candidate*>(inputIterator->Next())))
      {
        momentum = candidate->Momentum;
        jet = PseudoJet(momentum.Px(), momentum.Py(), momentum.Pz(), momentum.E());
        inputList.push_back(jet);
      }
     
      // run clustering 
      ClusterSequence sequence(inputList, *definition);
      outputList.clear();
      outputList = sorted_by_pt(sequence.inclusive_jets(0.0));

      // tell the user what was done
      //  - the description of the algorithm used
      //  - show the inclusive jets as
      //      {index, rapidity, phi, pt}
      //----------------------------------------------------------
      cout << "Ran " << definition->description() << endl;

      // label the columns
      printf("%5s %15s %15s %15s\n","jet #", "rapidity", "phi", "pt");

      // print out the details for each jet
      for (unsigned int i = 0; i < outputList.size(); i++) {
        printf("%5u %15.8f %15.8f %15.8f\n",
               i, outputList[i].rap(), outputList[i].phi(),
               outputList[i].perp());
      }
    }

    // Finalization
    modularDelphes->FinishTask();
    delete modularDelphes;
    delete confReader;
    return 0;
  }
  catch(runtime_error &e)
  {
    cerr << "** ERROR: " << e.what() << endl;
    return 1;
  }
}