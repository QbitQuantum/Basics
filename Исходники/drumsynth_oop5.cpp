int drumsynth::load_patch(char *dsfile)
{
  // init();
  // if(wavemode==0) //semi-real-time adjustments if working in memory!!
  // {
  //   mem_t = 1.0f;
  //   mem_o = 1.0f;
  //   mem_n = 1.0f;
  //   mem_b = 1.0f;
  //   mem_tune = 0.0f;
  //   mem_time = 1.0f;
  //   mem_time = 2.0f;
  // }

  //try to read version from input file
  //lstrcpy(sec, "General");
  strcpy(sec, "General"); 
  GetPrivateProfileString(sec,"Version","",ver,sizeof(ver),dsfile);
  ver[9]=0; 
  //if(lstrcmp(ver, "DrumSynth") != 0) {busy=0; return 2;} //input fail
  printf("%s\n",ver);
  if(strcmp(ver, "DrumSynth") != 0) {busy=0; return 2;} //input fail
  if(ver[11] != '1' && ver[11] != '2') {busy=0; return 1;} //version fail
  

  //read master parameters
  GetPrivateProfileString(sec,"Comment","",comment,sizeof(comment),dsfile);
  while((comment[commentLen]!=0) && (commentLen<254)) commentLen++;
  if(commentLen==0) { comment[0]=32; comment[1]=0; commentLen=1;}
  comment[commentLen+1]=0; commentLen++;
  if((commentLen % 2)==1) commentLen++; 
  
  timestretch = .01f * mem_time * GetPrivateProfileFloat(sec,"Stretch",100.0,dsfile);
  if(timestretch<0.2f) timestretch=0.2f; 
  if(timestretch>10.f) timestretch=10.f;

  DGain = 1.0f; //leave this here!
  DGain = (float)pow(10.0, 0.05 * GetPrivateProfileFloat(sec,"Level",0,dsfile));

  MasterTune = GetPrivateProfileFloat(sec,"Tuning",0.0,dsfile);
  MasterTune = (float)pow(1.0594631f, MasterTune + mem_tune);
  MainFilter = 2 * GetPrivateProfileInt(sec,"Filter",0,dsfile); 
  MFres = 0.0101f * GetPrivateProfileFloat(sec,"Resonance",0.0,dsfile);
  MFres = (float)pow(MFres, 0.5f);
  
  HighPass = GetPrivateProfileInt(sec,"HighPass",0,dsfile);
  getEnv(7, sec, "FilterEnv", dsfile);

 
  //read noise parameters
  //lstrcpy(sec, "Noise");
  strcpy(sec, "Noise");
  chkOn[1] = GetPrivateProfileInt(sec,"On",0,dsfile);
  sliLev[1] = GetPrivateProfileInt(sec,"Level",0,dsfile);    
  NT =  GetPrivateProfileInt(sec,"Slope",0,dsfile); 
  getEnv(2, sec, "Envelope", dsfile);
  NON = chkOn[1]; 
  NL = (float)(sliLev[1] * sliLev[1]) * mem_n;
  if(NT<0)
  { a = 1.f + (NT / 105.f); d = -NT / 105.f;
    g = (1.f + 0.0005f * NT * NT) * NL; }
  else
  { a = 1.f; b = -NT / 50.f; c = (float)fabs((float)NT) / 100.f; g = NL; }
  
  //if(GetPrivateProfileInt(sec,"FixedSeq",0,dsfile)!=0) 
    srand(1); //fixed random sequence
 
   //read tone parameters
    //lstrcpy(sec, "Tone");
  strcpy(sec, "Tone");
  chkOn[0] = GetPrivateProfileInt(sec,"On",0,dsfile); TON = chkOn[0];
  sliLev[0] = GetPrivateProfileInt(sec,"Level",128,dsfile); 
  TL = (float)(sliLev[0] * sliLev[0]) * mem_t;
  getEnv(1, sec, "Envelope", dsfile);
  F1 = MasterTune * TwoPi * GetPrivateProfileFloat(sec,"F1",200.0,dsfile) / Fs;
  if(fabs(F1)<0.001f) F1=0.001f; //to prevent overtone ratio div0
  F2 = MasterTune * TwoPi * GetPrivateProfileFloat(sec,"F2",120.0,dsfile) / Fs;
  Fsync = F2;
  TDroopRate = GetPrivateProfileFloat(sec,"Droop",0.f,dsfile);
  if(TDroopRate>0.f)
  {
    TDroopRate = (float)pow(10.0f, (TDroopRate - 20.0f) / 30.0f);
    TDroopRate = TDroopRate * -4.f / envData[1][MDA_MAX];
    TDroop = 1;
    F2 = F1+((F2-F1)/(1.f-(float)exp(TDroopRate * envData[1][MDA_MAX])));
    ddF = F1 - F2;
  }
  else ddF = F2-F1;
 
  Tphi = GetPrivateProfileFloat(sec,"Phase",90.f,dsfile) / 57.29578f; //degrees>radians

  //read overtone parameters
  //lstrcpy(sec, "Overtones");
  strcpy(sec, "Overtones");
  chkOn[2] = GetPrivateProfileInt(sec,"On",0,dsfile); OON = chkOn[2];
  sliLev[2] = GetPrivateProfileInt(sec,"Level",128,dsfile); 
  OL = (float)(sliLev[2] * sliLev[2]) * mem_o;
  getEnv(3, sec, "Envelope1", dsfile);
  getEnv(4, sec, "Envelope2", dsfile);
  OMode = GetPrivateProfileInt(sec,"Method",2,dsfile);
  OF1 = MasterTune * TwoPi * GetPrivateProfileFloat(sec,"F1",200.0,dsfile) / Fs;
  OF2 = MasterTune * TwoPi * GetPrivateProfileFloat(sec,"F2",120.0,dsfile) / Fs;
  OW1 = GetPrivateProfileInt(sec,"Wave1",0,dsfile);
  OW2 = GetPrivateProfileInt(sec,"Wave2",0,dsfile);
  OBal2 = (float)GetPrivateProfileInt(sec,"Param",50,dsfile);
  ODrive = (float)pow(OBal2, 3.0f) / (float)pow(50.0f, 3.0f);
  OBal2 *= 0.01f; 
  OBal1 = 1.f - OBal2;
  Ophi1 = Tphi; 
  Ophi2 = Tphi;
  if(MainFilter==0) 
    MainFilter = GetPrivateProfileInt(sec,"Filter",0,dsfile);
  if((GetPrivateProfileInt(sec,"Track1",0,dsfile)==1) && (TON==1))
  { OF1Sync = 1;  OF1 = OF1 / F1; }
  if((GetPrivateProfileInt(sec,"Track2",0,dsfile)==1) && (TON==1))
  { OF2Sync = 1;  OF2 = OF2 / F1; }

  OcA = 0.28f + OBal1 * OBal1;  //overtone cymbal mode
  OcQ = OcA * OcA;
  OcF = (1.8f - 0.7f * OcQ) * 0.92f; //multiply by env 2
  OcA *= 1.0f + 4.0f * OBal1;  //level is a compromise!
  Ocf1 = TwoPi / OF1;
  Ocf2 = TwoPi / OF2;
  for(i=0; i<6; i++) Oc[i][0] = Oc[i][1] = Ocf1 + (Ocf2 - Ocf1) * 0.2f * (float)i;

  //read noise band parameters
  //lstrcpy(sec, "NoiseBand");
  strcpy(sec, "NoiseBand");
  chkOn[3] = GetPrivateProfileInt(sec,"On",0,dsfile); BON = chkOn[3];
  sliLev[3] = GetPrivateProfileInt(sec,"Level",128,dsfile); 
  BL = (float)(sliLev[3] * sliLev[3]) * mem_b;
  BF = MasterTune * TwoPi * GetPrivateProfileFloat(sec,"F",1000.0,dsfile) / Fs;
  BPhi = TwoPi / 8.f;
  getEnv(5, sec, "Envelope", dsfile);
  BFStep = GetPrivateProfileInt(sec,"dF",50,dsfile); 
  BQ = (float)BFStep; 
  BQ = BQ * BQ / (10000.f-6600.f*((float)sqrt(BF)-0.19f));
  BFStep = 1 + (int)((40.f - (BFStep / 2.5f)) / (BQ + 1.f + (1.f * BF)));

  //lstrcpy(sec, "NoiseBand2");
  strcpy(sec, "NoiseBand2");
  chkOn[4] = GetPrivateProfileInt(sec,"On",0,dsfile); BON2 = chkOn[4];
  sliLev[4] = GetPrivateProfileInt(sec,"Level",128,dsfile); 
  BL2 = (float)(sliLev[4] * sliLev[4]) * mem_b;
  BF2 = MasterTune * TwoPi * GetPrivateProfileFloat(sec,"F",1000.0,dsfile) / Fs;
  BPhi2 = TwoPi / 8.f;
  getEnv(6, sec, "Envelope", dsfile);
  BFStep2 = GetPrivateProfileInt(sec,"dF",50,dsfile); 
  BQ2 = (float)BFStep2;
  BQ2 = BQ2 * BQ2 / (10000.f-6600.f*((float)sqrt(BF2)-0.19f));
  BFStep2 = 1 + (int)((40 - (BFStep2 / 2.5)) / (BQ2 + 1 + (1 * BF2)));
 
  //read distortion parameters
  //lstrcpy(sec, "Distortion");
  strcpy(sec, "Distortion");
  chkOn[5] = GetPrivateProfileInt(sec,"On",0,dsfile); DiON = chkOn[5];
  DStep = 1 + GetPrivateProfileInt(sec,"Rate",0,dsfile);
  if(DStep==7) DStep=20; if(DStep==6) DStep=10; if(DStep==5) DStep=8;

  clippoint = 32700;
  DAtten = 1.0f;

  if(DiON==1) 
  {
    DAtten = DGain * (short)LoudestEnv(); 
    if(DAtten>32700) clippoint=32700; else clippoint=(short)DAtten; 
    DAtten = (float)pow(2.0, 2.0 * GetPrivateProfileInt(sec,"Bits",0,dsfile));
    DGain = DAtten * DGain * (float)pow(10.0, 0.05 * GetPrivateProfileInt(sec,"Clipping",0,dsfile));
  }
  
  //prepare envelopes
  randmax = 1.f / RAND_MAX; randmax2 = 2.f * randmax;
  for (i=1;i<8;i++) { envData[i][NEXTT]=0; envData[i][PNT]=0; }
  Length = LongestEnv();

  /* if(wave!=NULL) free(wave); */
  /* wave = (short *)malloc(2 * Length + 1280); //wave memory buffer */
  if(wave==NULL) {busy=0; return 1;}
  wavewords = 0;
  prepare=1;
  return 0;
}