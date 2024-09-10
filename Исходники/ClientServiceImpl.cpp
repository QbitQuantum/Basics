void ClientServiceImpl::cleanUpCollectedData() {
  ScopeGuard fbCritSectGuard(
     bind(&CComCriticalSection::Lock, ref(facebookDataCritSect)),
     bind(&CComCriticalSection::Unlock, ref(facebookDataCritSect)));

  _toolbarNotifications.clear();
  _friendsChangesPopupNotifications.clear();
  _albumsChanges.clear();
  _popupSelfNotifications.clear();
  ServiceData emptyData;
  _currentData = emptyData;
}