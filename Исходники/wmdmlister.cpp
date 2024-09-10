void WmdmLister::GuessDriveLetter(DeviceInfo* info) {
  qLog(Debug) << "Guessing drive letter for" << info->name_;

  // Windows XP puts the drive letter in brackets at the end of the name
  QRegExp drive_letter("\\(([A-Z]:)\\)$");
  if (drive_letter.indexIn(info->name_) != -1) {
    qLog(Debug) << "Looks like an XP drive" << drive_letter.cap(1);
    CheckDriveLetter(info, drive_letter.cap(1));
    return;
  }

  // Windows 7 sometimes has the drive letter as the whole name
  drive_letter = QRegExp("^([A-Z]:)\\\\$");
  if (drive_letter.indexIn(info->name_) != -1) {
    qLog(Debug) << "Looks like a win7 drive" << drive_letter.cap(1);
    CheckDriveLetter(info, drive_letter.cap(1));
    return;
  }

  // Otherwise Windows 7 uses the drive's DOS label as its whole name.
  // Let's enumerate all the volumes on the system and find one with that
  // label, then get its drive letter.  Yay!
  wchar_t volume_name[MAX_PATH + 1];
  HANDLE handle = FindFirstVolumeW(volume_name, MAX_PATH);

  forever {
    // QueryDosDeviceW doesn't allow a trailing backslash, so remove it.
    int length = wcslen(volume_name);
    volume_name[length - 1] = L'\0';

    wchar_t device_name[MAX_PATH + 1];
    QueryDosDeviceW(&volume_name[4], device_name, MAX_PATH);

    volume_name[length - 1] = L'\\';

    // Don't do cd-roms or floppies
    if (QString::fromWCharArray(device_name).contains("HarddiskVolume")) {
      wchar_t volume_path[MAX_PATH + 1];
      DWORD volume_path_length = MAX_PATH;
      GetVolumePathNamesForVolumeNameW(
          volume_name, volume_path, volume_path_length, &volume_path_length);

      if (wcslen(volume_path) == 3) {
        ScopedWCharArray name(QString(MAX_PATH + 1, '\0'));
        ScopedWCharArray type(QString(MAX_PATH + 1, '\0'));
        DWORD serial = 0;

        if (!GetVolumeInformationW(volume_path, name, MAX_PATH,
            &serial, NULL, NULL, type, MAX_PATH)) {
          qLog(Warning) << "Error getting volume information for" <<
              QString::fromWCharArray(volume_path);
        } else {
          if (name.ToString() == info->name_ && name.characters() != 0) {
            // We found it!
            qLog(Debug) << "Looks like a win7 drive name" << QString::fromWCharArray(volume_path);
            if (CheckDriveLetter(info, QString::fromWCharArray(volume_path))) {
              info->device_name_ = QString::fromWCharArray(device_name);
              info->volume_name_ = QString::fromWCharArray(volume_name);
            }
            break;
          }
        }
      }
    }

    if (!FindNextVolumeW(handle, volume_name, MAX_PATH))
      break;
  }
  FindVolumeClose(handle);
}