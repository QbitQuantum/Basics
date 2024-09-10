/// <summary>
/// Handles change notifications for the current folder.
/// </summary>
LRESULT TileGroup::HandleChangeNotify(HANDLE changeHandle, DWORD processId) {
  long event;
  PIDLIST_ABSOLUTE *idList;
  HANDLE notifyLock = SHChangeNotification_Lock(changeHandle, processId, &idList, &event);

  if (notifyLock) {
    switch (event) {
    case SHCNE_ATTRIBUTES:
    case SHCNE_UPDATEITEM:
    case SHCNE_UPDATEDIR:
      UpdateIcon(ILFindLastID(idList[0]));
      break;

    case SHCNE_MKDIR:
    case SHCNE_CREATE:
      AddIcon(ILFindLastID(idList[0]));
      break;

    case SHCNE_RMDIR:
    case SHCNE_DELETE:
      RemoveIcon(ILFindLastID(idList[0]));
      break;

    case SHCNE_RENAMEITEM:
    case SHCNE_RENAMEFOLDER:
      RenameIcon(ILFindLastID(idList[0]), ILFindLastID(idList[1]));
      break;

    case SHCNE_ASSOCCHANGED:
    case SHCNE_UPDATEIMAGE:
      UpdateAllIcons();
      break;
    }

    SHChangeNotification_Unlock(notifyLock);
  }
  return 0;
}