// enum device
void dsound_enum_device(dsound_enum_callback &callback) {
  struct EnumDSound {
    static BOOL CALLBACK Func(LPGUID guid, LPCSTR desc, LPCSTR module, LPVOID context) {
      dsound_enum_callback *callback = (dsound_enum_callback *)context;
      (*callback)(desc);
      return TRUE;
    }
  };

  DirectSoundEnumerateA(&EnumDSound::Func, &callback);
}