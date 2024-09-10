/////////////////////////////////////////////////////////////////////////////////
// main function
int main(int argc, char* argv[])
{
    std::string             sInputFilePath,                 //!< file paths
                            sOutputFilePath;

    long long               iInFileLength       = 0;        //!< length of input file

//    clock_t                 time                = 0;

    float                   **ppfAudioData      = 0;

    CAudioFileIf            *phAudioFile        = 0;
    
    CAudioFileIf::FileSpec_t psFileSpec        = {};
    
    std::ofstream outputFile;
    
    //////////////////////////////////////////////////////////////////////////////

    showClInfo ();

    //////////////////////////////////////////////////////////////////////////////
    // parse command line arguments
    
    
    if (argc < 2) {
        cout<<"Please provide the input and out path as the 1st and 2nd command line arguments respectively."<<endl;
        return 0;
    }
    else {
        sInputFilePath = argv[1];
        sOutputFilePath = argv[2];
    }
    
//    cout<<argv[0]<<"|"<<endl<<argv[1]<<"|"<<endl<<argv[2]<<endl;
    
    //////////////////////////////////////////////////////////////////////////////
    // open the input wave file
    
    phAudioFile->create(phAudioFile);

    int status = phAudioFile->openFile(sInputFilePath, CAudioFileIf::kFileRead);

    cout<<"File Open status -> "<<status<<endl;
    
    phAudioFile->getLength(iInFileLength);
    cout<<"The length is "<<iInFileLength<<" samples"<<endl;
    phAudioFile->getFileSpec(psFileSpec);
    cout<<"Num channels "<<psFileSpec.iNumChannels<<endl;

    //////////////////////////////////////////////////////////////////////////////
    // allocate memory
    
    ppfAudioData = new float *[psFileSpec.iNumChannels];

    for(int i = 0; i < psFileSpec.iNumChannels; i++){
        ppfAudioData[i] = new float[iInFileLength];
    }

    // get audio data
    phAudioFile->readData(ppfAudioData, iInFileLength);
    
    //////////////////////////////////////////////////////////////////////////////
    // get audio info and print it to stdout
    
    outputFile.open(sOutputFilePath,outputFile.app);
    
    outputFile <<"L\t"<<"R"<<endl;
    
    for (int i = 0; i < iInFileLength; i++) {
        outputFile << ppfAudioData[0][i] <<"\t" << ppfAudioData[1][i] <<endl ;
    }

    outputFile.close();

    //////////////////////////////////////////////////////////////////////////////
    // do processing
    cout << "\nHello there! File has been read successfully! " << endl << endl;
   

    //////////////////////////////////////////////////////////////////////////////
    // clean-up
    // clean-up
    for(int i = 0; i < psFileSpec.iNumChannels; i++) {
        delete [] ppfAudioData[i];
    }
    delete [] ppfAudioData;
    
    phAudioFile->destroy(phAudioFile);

    return 0;
    
}