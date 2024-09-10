NS_IMETHODIMP
nsPersistentProperties::SetStringProperty(const nsACString& aKey,
                                          const nsAString& aNewValue,
                                          nsAString& aOldValue)
{
  const nsAFlatCString&  flatKey = PromiseFlatCString(aKey);
  PropertyTableEntry *entry =
    static_cast<PropertyTableEntry*>
               (PL_DHashTableOperate(&mTable, flatKey.get(), PL_DHASH_ADD));

  if (entry->mKey) {
    aOldValue = entry->mValue;
    NS_WARNING(nsPrintfCString(aKey.Length() + 30,
                               "the property %s already exists\n",
                               flatKey.get()).get());
  }
  else {
    aOldValue.Truncate();
  }

  entry->mKey = ArenaStrdup(flatKey, &mArena);
  entry->mValue = ArenaStrdup(PromiseFlatString(aNewValue), &mArena);

  return NS_OK;
}