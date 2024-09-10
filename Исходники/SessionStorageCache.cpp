nsresult
SessionStorageCache::RemoveItem(DataSetType aDataSetType, const nsAString& aKey,
                                nsString& aOldValue)
{
  DataSet* dataSet = Set(aDataSetType);

  if (!dataSet->mKeys.Get(aKey, &aOldValue)) {
    return NS_SUCCESS_DOM_NO_OPERATION;
  }

  // Recalculate the cached data size
  dataSet->ProcessUsageDelta(-(static_cast<int64_t>(aOldValue.Length()) +
                               static_cast<int64_t>(aKey.Length())));

  dataSet->mKeys.Remove(aKey);
  return NS_OK;
}