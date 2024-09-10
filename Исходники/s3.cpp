void enum_sound_play_devices(device_enum_callback *lpDSEnumCallback, LPVOID lpContext)
{
    DirectSoundEnumerateW(lpDSEnumCallback,lpContext);
}