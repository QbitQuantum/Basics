void
sbWin32FileSystemWatcher::WatchNextChange()
{
  TRACE("%s", __FUNCTION__);
  DWORD const flags =
    FILE_NOTIFY_CHANGE_FILE_NAME |
    FILE_NOTIFY_CHANGE_DIR_NAME |
    FILE_NOTIFY_CHANGE_LAST_WRITE |
    FILE_NOTIFY_CHANGE_CREATION;

  if (mRootDirHandle != INVALID_HANDLE_VALUE) {
    BOOL result =
      ReadDirectoryChangesW(mRootDirHandle,
                            mBuffer,
                            BUFFER_LEN,
                            TRUE,  // watch subdirs
                            flags,
                            NULL,
                            &mOverlapped,
                            ReadDirectoryChangesWCallbackRoutine);
    if (!result) {
      NS_WARNING("ERROR: Could not ReadDirectoryChangesW()");
      if (mRootDirHandle != INVALID_HANDLE_VALUE) {
        CloseHandle(mRootDirHandle);
        mRootDirHandle = INVALID_HANDLE_VALUE;
      }
    }
  }
}