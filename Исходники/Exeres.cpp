int XeresCalibMain_main(int argc,char** argv)
{
   MMD_InitArgcArgv(argc,argv);

   std::string aSeq,aDir,OutCal="Calib";
   int aSz=1500;



   ElInitArgMain
   (
         argc,argv,
         LArgMain()  //  << EAMC(aSeq, "Sequence")
                     << EAMC(aDir, "Directory"),
         LArgMain()  << EAM(aSeq,"Seq",true,"Folder of data, Def=./")
                     << EAM(aSz,"Sz",true,"Sz of TieP, Def=1500")
                     << EAM(OutCal,"Out",true,"")
   );

   // std::string aCdDir = "cd " + aDir + "/";
   // System(aCdDir);
   if (!EAMIsInit(&aSeq) ) aSeq = aDir;

   cElemAppliSetFile anEASF(aDir+"/.*jpg");

   const std::vector<std::string> * aVS = anEASF.SetIm();
   int aNbIm = aVS->size();
   for (int aK=0 ; aK<aNbIm ; aK++)
   {
        const std::string & aName = (*aVS)[aK];
        ELISE_fp::MvFile(aDir+"/"+aName,aDir+"/"+aSeq+"_Calib" +ToString(aK) + ".jpg");
        std::cout << "NAME = " << aName << "\n";
   }

   std::string aStrMMD= "MicMac-LocalChantierDescripteur.xml";

   ELISE_fp::CpFile(aStrMMD,aDir+"/"+aStrMMD);


   std::string aComTiep = MM3dBinFile_quotes("Tapioca") + " All  " + aDir + "/.*jpg " + ToString(aSz);
   System(aComTiep);

   std::string aComOri =  MM3dBinFile_quotes("Tapas ") + " FraserBasic " +  aDir + "/.*jpg " + " Out=" + OutCal
                          + " RankInitPP=0 RankInitF=1 RefineAll=0";
   System(aComOri);


   return EXIT_SUCCESS;
}