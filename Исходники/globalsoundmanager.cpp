bool GlobalSoundManager::create(HWND hMainWindow) {
  if (APP_ERROR(FAILED(DirectSoundCreate8(NULL, &direct_sound_, NULL)) ||
           FAILED(direct_sound_->SetCooperativeLevel(hMainWindow, DSSCL_NORMAL)))
    ("Couldn't initialize DirectSound"))
    return false;
  return true;
}