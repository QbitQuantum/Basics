int iKX::init_winmm()
{
    // check for Vista and Windows7:
    OSVERSIONINFOEX ver;
    memset(&ver,0,sizeof(ver));
    ver.dwOSVersionInfoSize=sizeof(ver);

    if(GetVersionEx((OSVERSIONINFO *)&ver)) // ok?
    {
     if(ver.dwPlatformId==VER_PLATFORM_WIN32_NT && ver.dwMajorVersion>=6)
     {
      debug("iKX(): init_winmm: mixers are not supported. Vista+ workaround\n");
      return 0;
     }
    }

    int ret=-1;

    for(unsigned int i=0;i<mixerGetNumDevs();i++)
    {
        HMIXER mixer=0;
        int to_close=1;

        // open mixer
        if(mixerOpen(&mixer,i,0,0,MIXER_OBJECTF_MIXER)!=MMSYSERR_NOERROR)
        {
            debug("iKX(): mixerOpen failed [%x]\n",GetLastError());
            continue; // next mixer
        }
        // get mixer caps
        MIXERCAPS mc; memset(&mc,0,sizeof(mc));
        if(mixerGetDevCaps(i,&mc,sizeof(mc))!=MMSYSERR_NOERROR)
        {
            debug("iKX(): mixerGetDevCaps() failed [%x]\n",GetLastError());
            mixerClose(mixer);
            continue;
        }

        // debug("iKX(): init_winmm: looking for '%s': '%s' [#%d out of %d]\n",wave_name,mc.szPname,i,mixerGetNumDevs());

        if(strncmp(mc.szPname,wave_name,strlen(wave_name)-4)!=NULL) // yes, this should be 'wave_name', not 'mixer_name';
        { mixerClose(mixer); continue; }

        if(strcmp(mc.szPname,wave_name)==0)
         { mixer_handler[0]=(uintptr_t)mixer; to_close=0; ret=0; }
        else
         if(strcmp(mc.szPname,wave23_name)==0)
          { mixer_handler[1]=(uintptr_t)mixer; to_close=0;  ret=0; }
         else
          if(strcmp(mc.szPname,wave45_name)==0)
           { mixer_handler[2]=(uintptr_t)mixer; to_close=0;  ret=0; }
          else
           if(strcmp(mc.szPname,wave67_name)==0)
            { mixer_handler[3]=(uintptr_t)mixer; to_close=0;  ret=0; }
           else
           if(strcmp(mc.szPname,waveHQ_name)==0)
             { mixer_handler[4]=(uintptr_t)mixer; to_close=0; ret=0; }
            else
            {
             debug("kXAPI: WARNING: incorrect init_winmm() code: %s\n",mc.szPname);
            }
        if(to_close)
         mixerClose(mixer);
//      break;
    }
    if(ret==-1)
    {
     debug("iKX(): init_winmm: number of mixers: %d\n",mixerGetNumDevs());
    }

    return ret;
}