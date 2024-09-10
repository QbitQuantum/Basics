void readConfigFile (string configFileList, string configFilePath)
{
  // Input stream for data file
  ifstream inFile;       
  // Open input file
  inFile.open (configFileList.c_str(), ios::in);
  
  // If can't open input file, exit the code
  if (!inFile)
    {
      cerr << "ERROR: Can't open input file: " << configFileList << endl;
      exit (1);
    }

  // ROOT configuration file


  while (inFile >> inputType) 
    {

      string configfile=configFilePath + "/" + inputType;

      TEnv *params = new TEnv ("config_file");
      params->ReadFile (configfile.c_str(), kEnvChange);
      
      // Get Root file name
      string rootFileNameNum = params->GetValue ("NormalizedrootfileNum", "file");
      inputRootFileNum.push_back (rootFileNameNum.c_str() ); 

      string rootFileNameDen = params->GetValue ("NormalizedrootfileDen", "file");
      inputRootFileDen.push_back (rootFileNameDen.c_str() );

      // Get process name: data, ttbar, wjets etc.
      string process = params->GetValue ("process", "theprocess"); 
      inputProcess.push_back(process.c_str());

      // Marker Style
      int themarker = params->GetValue("marketStyle", 20);
      inputMarkerStyle.push_back(themarker); 

      // Line Color
      int thecolor = params->GetValue("color" , kRed);
      inputColor.push_back (thecolor);

      // Store TLegend text
      string thelegend = params->GetValue("legend" , "histo");
      inputLegend.push_back (thelegend.c_str());

      // Use collision data in your plots? --> 99% of the time yes...just in case you do not want to
      
      string isSignal = params->GetValue("isSignal", "False");
      inputIsSignal.push_back ( isSignal.c_str() );

      // Output root file name
      HistosOutputRootFile = params->GetValue("outputRootFileHistos", "Histos.root");

    }
  
  inFile.close();
}