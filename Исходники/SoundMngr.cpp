int SoundManager::Init()
{
  if(active==true) return 1;

  FONLINE_LOG("SoundManager Init\n");

  if (!fm.Init(opt_masterpath.c_str(), opt_critterpath.c_str(), opt_fopath.c_str())) return 0;;

  if(DirectSoundCreate8(0,&lpDS,0)!=DS_OK)
  {
    FONLINE_LOG("Неудалось создать устройство!\n");
    return 0;
  }

  if(lpDS->SetCooperativeLevel(GetForegroundWindow(),DSSCL_NORMAL)!=DS_OK)
  {
    FONLINE_LOG("Неудалось установить уровень кооперации!\n");
    return 0;
  }

  cur_snd=1;

  active=true;

  FONLINE_LOG("SoundManager Init OK\n");

  return 1;
}