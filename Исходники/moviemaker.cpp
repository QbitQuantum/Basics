bool MovieMaker::CreateCompressedStream(const string &codec, uint frameRate)
{
  //Get the compression options
  HRESULT result = AVIERR_OK;
  AVICOMPRESSOPTIONS opts;
  AVICOMPRESSOPTIONS FAR * aopts[1] = {&opts};
  memset(&opts, 0, sizeof(opts));

  //If using the menu
  if(codec == "menu")
  {
    //Load the memu options
    if (!AVISaveOptions(GetActiveWindow(), 0, 1, &ps, (LPAVICOMPRESSOPTIONS FAR *)&aopts))
    {
      AVISaveOptionsFree(1,(LPAVICOMPRESSOPTIONS FAR *) &aopts);
      return false;
    }

    //Create a compressed stream using codec options.
    result = AVIMakeCompressedStream(&psCompressed, 
                                      ps, 
                                     &opts, 
                                      NULL);
    if (result != AVIERR_OK)
    {
      AVISaveOptionsFree(1,(LPAVICOMPRESSOPTIONS FAR *) &aopts);
      return false;
    }

    //Release save options
    result = AVISaveOptionsFree(1,(LPAVICOMPRESSOPTIONS FAR *) &aopts);
    if (result!=AVIERR_OK)
    {
      LOGERR(("CreateCompressedStream -Error releasing memory"));
      return false;
    }

  }
  else
  {
    opts.fccType=streamtypeVIDEO;
    opts.fccHandler= CreateCodecDWORD(codec); // mmioFOURCC('M','P','G','4');
    opts.dwFlags=AVICOMPRESSF_KEYFRAMES | AVICOMPRESSF_VALID;//|AVICOMPRESSF_DATARATE;
    opts.dwKeyFrameEvery=frameRate;

    //Create a compressed stream using codec options.
    result = AVIMakeCompressedStream(&psCompressed, 
                                      ps, 
                                     &opts, 
                                      NULL);
    if (result != AVIERR_OK)
    {
      return false;
    }
  }

  return true;
}