int GCPCtrl_main(int argc,char ** argv)
{
    // MemoArg(argc,argv);
    MMD_InitArgcArgv(argc,argv);
    std::string  aDir,aPat,aFullDir;


    std::string AeroIn;
    std::string DicoPts;
    std::string MesureIm;
    bool        CPI = false;
    bool ShowUnused = true;


    ElInitArgMain
    (
        argc,argv,
        LArgMain()  << EAMC(aFullDir,"Full name (Dir+Pat)", eSAM_IsPatFile)
                    << EAMC(AeroIn,"Orientation in", eSAM_IsExistDirOri)
                    << EAMC(DicoPts,"Ground Control Points File", eSAM_IsExistFile)
                    << EAMC(MesureIm,"Image Measurements File", eSAM_IsExistFile),
        LArgMain()
                    <<  EAM(CPI,"CPI",true,"when Calib Per Image has to be used", eSAM_IsBool)
                    <<  EAM(ShowUnused,"ShowU",true,"Show unused point (def=true)", eSAM_IsBool)
    );

    if (!MMVisualMode)
    {
    #if (ELISE_windows)
        replace( aFullDir.begin(), aFullDir.end(), '\\', '/' );
    #endif
    SplitDirAndFile(aDir,aPat,aFullDir);
    StdCorrecNameOrient(AeroIn,aDir);



    std::string aCom =   MM3dBinFile_quotes( "Apero" )
                       + ToStrBlkCorr( MMDir()+"include/XML_MicMac/Apero-GCP-Control.xml" )+" "
                       + std::string(" DirectoryChantier=") +aDir +  std::string(" ")
                       + std::string(" +PatternAllIm=") + QUOTE(aPat) + std::string(" ")
                       + std::string(" +AeroIn=") + AeroIn
                       + std::string(" +DicoApp=") +  DicoPts
                       + std::string(" +SaisieIm=") +  MesureIm
                    ;

    if (EAMIsInit(&ShowUnused)) aCom = aCom + " +ShowUnused=" + ToString(ShowUnused);
    if (CPI) aCom += " +CPI=true ";


    std::cout << "Com = " << aCom << "\n";
    int aRes = System(aCom.c_str(),false,true,true);


    return aRes;

    }
    else return EXIT_SUCCESS;
}