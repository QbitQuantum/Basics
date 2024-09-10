int Recab::execute(int argc, char *argv[])
{
    bool verboseFlag = false;

    String inFile,outFile,logFile;

    bool noeof = false;
    bool params = false;

    SamFile samIn,samOut;

    ParameterList inputParameters;

    LongParamContainer parameters;

    parameters.addGroup("Required Generic Parameters");
    parameters.addString("in", &inFile);
    parameters.addString("out", &outFile);
    parameters.addGroup("Optional Generic Parameters");
    parameters.addString("log", &logFile);
    parameters.addBool("verbose", &verboseFlag);
    parameters.addBool("noeof", &noeof);
    parameters.addBool("params", &params);
    parameters.addPhoneHome(VERSION);
    addRecabSpecificParameters(parameters);
    inputParameters.Add(new LongParameters ("Input Parameters", 
                                            parameters.getLongParameterList()));
    
    // parameters start at index 2 rather than 1.
    inputParameters.Read(argc, argv, 2);
    
    // If no eof block is required for a bgzf file, set the bgzf file type to 
    // not look for it.
    if(noeof)
    {
        // Set that the eof block is not required.
        BgzfFileType::setRequireEofBlock(false);
    }

    if(inFile.IsEmpty())
    {
        usage();
        inputParameters.Status();
        std::cerr << "Missing required --in parameter" << std::endl;
        return EXIT_FAILURE;
    }

    if(outFile.IsEmpty())
    {
        usage();
        inputParameters.Status();
        std::cerr << "Missing required --out parameter" << std::endl;
        return EXIT_FAILURE;
    }

    int status = processRecabParam();
    if(status != 0)
    {
        inputParameters.Status();
        return(status);
    }

    if ( logFile.IsEmpty() )
    {
        logFile = outFile + ".log";
    }
  
    if(params)
    {
        inputParameters.Status();
    }
    
    Logger::gLogger = new Logger(logFile.c_str(), verboseFlag);

    ////////////////
    //////  Errormodel
    Logger::gLogger->writeLog("Initialize errormodel structure...");

    ////////////////////////////////////////
    // SAM/BAM file open
    ////////////////////////////////////////
    ////////////////////////////////////////

    // Iterate SAM records
    if(!samIn.OpenForRead(inFile.c_str()))
    {
        Logger::gLogger->error("Failed to open SAM/BAM file %s",inFile.c_str() );
        return EXIT_FAILURE;
    }

    Logger::gLogger->writeLog("Start iterating SAM/BAM file %s",inFile.c_str());

    time_t now = time(0);
    tm* localtm = localtime(&now);

    Logger::gLogger->writeLog("Start: %s", asctime(localtm));
    SamRecord samRecord;
    SamFileHeader samHeader;
    samIn.ReadHeader(samHeader);

    srand (time(NULL));

    int numRecs = 0;
    while(samIn.ReadRecord(samHeader, samRecord) == true)
    {
        processReadBuildTable(samRecord);

        //Status info
        numRecs++;
        if(verboseFlag)
        {
            if(numRecs%10000000==0)
                Logger::gLogger->writeLog("%ld records processed", numRecs);
        }
    }

    now = time(0);
    localtm = localtime(&now);
    Logger::gLogger->writeLog("End: %s", asctime(localtm));

    modelFitPrediction(outFile);

    Logger::gLogger->writeLog("Writing recalibrated file %s",outFile.c_str());

    ////////////////////////
    ////////////////////////
    //// Write file
    samIn.OpenForRead(inFile.c_str());
    samOut.OpenForWrite(outFile.c_str());
    samIn.ReadHeader(samHeader);
    samOut.WriteHeader(samHeader);
    
    while(samIn.ReadRecord(samHeader, samRecord) == true)
    {
        // Recalibrate.
        processReadApplyTable(samRecord);
        samOut.WriteRecord(samHeader, samRecord);
    }

    Logger::gLogger->writeLog("Total # Reads recab table not applied to: %ld", myNumApplySkipped);
    Logger::gLogger->writeLog("Total # Reads recab table applied to: %ld", myNumApplyReads);
    Logger::gLogger->writeLog("Recalibration successfully finished");
    return EXIT_SUCCESS;
}