int main(int argc, char *argv[])
{
   char *datafn, *s;
   int nSeg;
   void Initialise(void);
   void LoadFile(char *fn);
   void EstimateModel(void);
   void SaveModel(char *outfn);
   
   if(InitShell(argc,argv,hinit_version,hinit_vc_id)<SUCCESS)
      HError(2100,"HInit: InitShell failed");
   InitMem();   InitLabel();
   InitMath();  InitSigP();
   InitWave();  InitAudio();
   InitVQ();    InitModel();
   if(InitParm()<SUCCESS)  
      HError(2100,"HInit: InitParm failed");
   InitTrain(); InitUtil();

   if (!InfoPrinted() && NumArgs() == 0)
      ReportUsage();
   if (NumArgs() == 0) Exit(0);
   SetConfParms();

   CreateHMMSet(&hset,&gstack,FALSE);
   while (NextArg() == SWITCHARG) {
      s = GetSwtArg();
      if (strlen(s)!=1) 
         HError(2119,"HInit: Bad switch %s; must be single letter",s);
      switch(s[0]){
      case 'e':
         epsilon = GetChkedFlt(0.0,1.0,s); break;
      case 'i':
         maxIter = GetChkedInt(0,100,s); break;
      case 'l':
         if (NextArg() != STRINGARG)
            HError(2119,"HInit: Segment label expected");
         segLab = GetStrArg();
         break;
      case 'm':
         minSeg = GetChkedInt(1,1000,s); break;
      case 'n':
         newModel = FALSE; break;
      case 'o':
         outfn = GetStrArg();
         break;
      case 'u':
         SetuFlags(); break;
      case 'v':
         minVar = GetChkedFlt(0.0,10.0,s); break;
      case 'w':
         mixWeightFloor = MINMIX * GetChkedFlt(0.0,10000.0,s); 
         break;
      case 'B':
         saveBinary = TRUE;
         break;
      case 'F':
         if (NextArg() != STRINGARG)
            HError(2119,"HInit: Data File format expected");
         if((dff = Str2Format(GetStrArg())) == ALIEN)
            HError(-2189,"HInit: Warning ALIEN Data file format set");
         break;
      case 'G':
         if (NextArg() != STRINGARG)
            HError(2119,"HInit: Label File format expected");
         if((lff = Str2Format(GetStrArg())) == ALIEN)
            HError(-2189,"HInit: Warning ALIEN Label file format set");
         break;
      case 'H':
         if (NextArg() != STRINGARG)
            HError(2119,"HInit: HMM macro file name expected");
         AddMMF(&hset,GetStrArg());
         break;
      case 'I':
         if (NextArg() != STRINGARG)
            HError(2119,"HInit: MLF file name expected");
         LoadMasterFile(GetStrArg());
         break;
      case 'L':
         if (NextArg()!=STRINGARG)
            HError(2119,"HInit: Label file directory expected");
         labDir = GetStrArg(); break;
      case 'M':
         if (NextArg()!=STRINGARG)
            HError(2119,"HInit: Output macro file directory expected");
         outDir = GetStrArg();
         break;
      case 'T':
         if (NextArg() != INTARG)
            HError(2119,"HInit: Trace value expected");
         trace = GetChkedInt(0,01777,s);
         break;
      case 'X':
         if (NextArg()!=STRINGARG)
            HError(2119,"HInit: Label file extension expected");
         labExt = GetStrArg(); break;
      default:
         HError(2119,"HInit: Unknown switch %s",s);
      }
   }
   if (NextArg()!=STRINGARG)
      HError(2119,"HInit: source HMM file name expected");
   hmmfn = GetStrArg();
   Initialise();
   do {
      if (NextArg()!=STRINGARG)
         HError(2119,"HInit: training data file name expected");
      datafn = GetStrArg();
      LoadFile(datafn);
   } while (NumArgs()>0);
   nSeg = NumSegs(segStore);
   if (nSeg < minSeg)
      HError(2121,"HInit: Too Few Observation Sequences [%d]",nSeg);
   if (trace&T_TOP) {
      printf("%d Observation Sequences Loaded\n",nSeg);
      fflush(stdout);
   }
   EstimateModel();
   SaveModel(outfn);
   if (trace&T_TOP)
      printf("Output written to directory %s\n",
             outDir==NULL?"current":outDir);
   Exit(0);
   return (0);          /* never reached -- make compiler happy */
}