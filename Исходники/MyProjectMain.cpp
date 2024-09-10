/////////////////////////////////////////////////////////////////////////////////
// main function
int main(int argc, char* argv[])
{
    std::string             sInputFilePath,
                            sOutputFilePath;

    float                   **ppfAudioData  = 0;
    static const int        kBlockSize      = 1024;

    CAudioFileIf            *phInputFile;
    std::fstream            hOutputFile;
    CAudioFileIf::FileSpec_t stFileSpec;

    // detect memory leaks in win32
#if (defined(WITH_MEMORYCHECK) && !defined(NDEBUG) && defined (GTCMT_WIN32))
    // set memory checking flags
    int iDbgFlag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
    iDbgFlag       |= _CRTDBG_CHECK_ALWAYS_DF;
    iDbgFlag       |= _CRTDBG_LEAK_CHECK_DF;
    _CrtSetDbgFlag( iDbgFlag );
#endif

    // enable floating point exceptions in win32
#if (defined(WITH_FLOATEXCEPTIONS) && !defined(NDEBUG) && defined (GTCMT_WIN32))
    // enable check for exceptions (don't forget to enable stop in MSVC!)
    _controlfp(~(_EM_INVALID | _EM_ZERODIVIDE | _EM_OVERFLOW | _EM_UNDERFLOW | _EM_DENORMAL), _MCW_EM) ;
#endif // #ifndef WITHOUT_EXCEPTIONS

    showClInfo ();

    // parse command line arguments
    getClArgs (sInputFilePath, sOutputFilePath, argc, argv);

    // open the input wave file
    CAudioFileIf::createInstance(phInputFile);
    phInputFile->openFile(sInputFilePath, CAudioFileIf::kFileRead);
    if (!phInputFile->isOpen())
    {
        cout << "Wave file open error!";
        return -1;
    }
    phInputFile->getFileSpec(stFileSpec);

    // open the output text file
     hOutputFile.open (sOutputFilePath.c_str(), std::ios::out);
     if (!hOutputFile.is_open())
     {
         cout << "Text file open error!";
         return -1;
     }

    // allocate audio data buffer
    ppfAudioData            = new float* [stFileSpec.iNumChannels];
    for (int i = 0; i < stFileSpec.iNumChannels; i++)
        ppfAudioData[i] = new float [kBlockSize];

    // read wave
    while (!phInputFile->isEof())
    {
        int iNumFrames = kBlockSize;
        phInputFile->readData(ppfAudioData, iNumFrames);

        for (int i = 0; i < iNumFrames; i++)
        {
            for (int c = 0; c < stFileSpec.iNumChannels; c++)
            {
                hOutputFile << ppfAudioData[c][i] << "\t";
            }
            hOutputFile << endl;
        }

    }

    // close the files
    CAudioFileIf::destroyInstance(phInputFile);
    hOutputFile.close();

    // free memory
    for (int i = 0; i < stFileSpec.iNumChannels; i++)
        delete [] ppfAudioData[i];
    delete [] ppfAudioData;
    ppfAudioData = 0;

    return 0;
    
}