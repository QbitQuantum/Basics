int32_t main (int32_t iArgC, char* pArgV[]) {
  ISVCDecoder* pDecoder = NULL;

  SDecodingParam sDecParam = {0};
  string strInputFile (""), strOutputFile (""), strOptionFile ("");

  sDecParam.sVideoProperty.size = sizeof (sDecParam.sVideoProperty);

  if (iArgC < 2) {
    printf ("usage 1: h264dec.exe welsdec.cfg\n");
    printf ("usage 2: h264dec.exe welsdec.264 out.yuv\n");
    printf ("usage 3: h264dec.exe welsdec.264\n");
    return 1;
  } else if (iArgC == 2) {
    if (strstr (pArgV[1], ".cfg")) { // read config file //confirmed_safe_unsafe_usage
      CReadConfig cReadCfg (pArgV[1]);
      string strTag[4];
      string strReconFile ("");

      if (!cReadCfg.ExistFile()) {
        printf ("Specified file: %s not exist, maybe invalid path or parameter settting.\n", cReadCfg.GetFileName().c_str());
        return 1;
      }

      while (!cReadCfg.EndOfFile()) {
        long nRd = cReadCfg.ReadLine (&strTag[0]);
        if (nRd > 0) {
          if (strTag[0].compare ("InputFile") == 0) {
            strInputFile	= strTag[1];
          } else if (strTag[0].compare ("OutputFile") == 0) {
            strOutputFile	= strTag[1];
          } else if (strTag[0].compare ("RestructionFile") == 0) {
            strReconFile	= strTag[1];
            int32_t iLen = strReconFile.length();
            sDecParam.pFileNameRestructed	= new char[iLen + 1];
            if (sDecParam.pFileNameRestructed != NULL) {
              sDecParam.pFileNameRestructed[iLen] = 0;
            }

            strncpy (sDecParam.pFileNameRestructed, strReconFile.c_str(), iLen); //confirmed_safe_unsafe_usage
          } else if (strTag[0].compare ("TargetDQID") == 0) {
            sDecParam.uiTargetDqLayer	= (uint8_t)atol (strTag[1].c_str());
          } else if (strTag[0].compare ("OutColorFormat") == 0) {
            sDecParam.iOutputColorFormat = atol (strTag[1].c_str());
          } else if (strTag[0].compare ("ErrorConcealmentFlag") == 0) {
            sDecParam.uiEcActiveFlag	= (uint8_t)atol (strTag[1].c_str());
          } else if (strTag[0].compare ("CPULoad") == 0) {
            sDecParam.uiCpuLoad	= (uint32_t)atol (strTag[1].c_str());
          } else if (strTag[0].compare ("VideoBitstreamType") == 0) {
            sDecParam.sVideoProperty.eVideoBsType = (VIDEO_BITSTREAM_TYPE)atol (strTag[1].c_str());
          }
        }
      }
      if (strOutputFile.empty()) {
        printf ("No output file specified in configuration file.\n");
        return 1;
      }
    } else if (strstr (pArgV[1],
                       ".264")) { // no output dump yuv file, just try to render the decoded pictures //confirmed_safe_unsafe_usage
      strInputFile	= pArgV[1];
      sDecParam.iOutputColorFormat          = videoFormatI420;
      sDecParam.uiTargetDqLayer	          = (uint8_t) - 1;
      sDecParam.uiEcActiveFlag	          = 1;
      sDecParam.sVideoProperty.eVideoBsType = VIDEO_BITSTREAM_DEFAULT;
    }
  } else { //iArgC > 2
    strInputFile	= pArgV[1];
    strOutputFile	= pArgV[2];
    sDecParam.iOutputColorFormat	= videoFormatI420;
    sDecParam.uiTargetDqLayer	= (uint8_t) - 1;
    sDecParam.uiEcActiveFlag	= 1;
    sDecParam.sVideoProperty.eVideoBsType = VIDEO_BITSTREAM_DEFAULT;
    if (iArgC > 3) {
      for (int i = 3; i < iArgC; i++) {
        char* cmd = pArgV[i];

        if (!strcmp (cmd, "-options")) {
          if (i + 1 < iArgC)
            strOptionFile = pArgV[i++];
          else {
            printf ("options file not specified.\n");
            return 1;
          }
        } else if (!strcmp (cmd, "-trace")) {
          if (i + 1 < iArgC)
            WelsStderrSetTraceLevel (atoi (pArgV[i++]));
          else {
            printf ("trace level not specified.\n");
            return 1;
          }
        }
      }
    }

    if (strOutputFile.empty()) {
      printf ("No output file specified in configuration file.\n");
      return 1;
    }
  }

  if (strInputFile.empty()) {
    printf ("No input file specified in configuration file.\n");
    return 1;
  }




#if defined(_MSC_VER)

  HMODULE hModule = LoadLibraryA (".\\welsdec.dll");

  PCreateDecoderFunc  pCreateDecoderFunc				= NULL;
  PDestroyDecoderFunc pDestroyDecoderFunc				= NULL;


  pCreateDecoderFunc  = (PCreateDecoderFunc)::GetProcAddress (hModule, "CreateDecoder");
  pDestroyDecoderFunc = (PDestroyDecoderFunc)::GetProcAddress (hModule, "DestroyDecoder");

  if ((hModule != NULL) && (pCreateDecoderFunc != NULL) && (pDestroyDecoderFunc != NULL)) {
    printf ("load library sw function successfully\n");

    if (pCreateDecoderFunc (&pDecoder)  || (NULL == pDecoder)) {
      printf ("Create Decoder failed.\n");
      return 1;
    }
  } else {
    printf ("load library sw function failed\n");
    return 1;
  }


#else


  if (CreateDecoder (&pDecoder)  || (NULL == pDecoder)) {
    printf ("Create Decoder failed.\n");
    return 1;
  }

#endif


  if (pDecoder->Initialize (&sDecParam, INIT_TYPE_PARAMETER_BASED)) {
    printf ("Decoder initialization failed.\n");
    return 1;
  }


  int32_t iWidth = 0;
  int32_t iHeight = 0;


  H264DecodeInstance (pDecoder, strInputFile.c_str(), strOutputFile.c_str(), iWidth, iHeight,
                      (!strOptionFile.empty() ? (void_t*) (const_cast<char*> (strOptionFile.c_str())) : NULL));

  if (sDecParam.pFileNameRestructed != NULL) {
    delete []sDecParam.pFileNameRestructed;
    sDecParam.pFileNameRestructed = NULL;
  }

  if (pDecoder) {
    pDecoder->Uninitialize();

#if defined(_MSC_VER)
    pDestroyDecoderFunc (pDecoder);
#else
    DestroyDecoder (pDecoder);
#endif
  }

  return 0;
}