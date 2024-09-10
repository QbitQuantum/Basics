bool
DOMStorageCache::LoadItem(const nsAString& aKey, const nsString& aValue)
{
  MonitorAutoLock monitor(mMonitor);
  if (mLoaded) {
    return false;
  }

  Data& data = mData[kDefaultSet];
  if (data.mKeys.Get(aKey, nullptr)) {
    return true; // don't stop, just don't override
  }

  data.mKeys.Put(aKey, aValue);
  data.mOriginQuotaUsage += aKey.Length() + aValue.Length();
  return true;
}