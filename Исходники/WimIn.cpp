static HRESULT ParseDirItem(const Byte *base, size_t pos, size_t size,
    const UString &prefix, CObjectVector<CItem> &items)
{
  for (;;)
  {
    if (pos + 8 > size)
      return S_FALSE;
    const Byte *p = base + pos;
    UInt64 length = Get64(p);
    if (length == 0)
      return S_OK;
    if (pos + 102 > size || pos + length + 8 > size || length > ((UInt64)1 << 62))
      return S_FALSE;
    CItem item;
    item.Attrib = Get32(p + 8);
    // item.SecurityId = Get32(p + 0xC);
    UInt64 subdirOffset = Get64(p + 0x10);
    GetFileTimeFromMem(p + 0x28, &item.CTime);
    GetFileTimeFromMem(p + 0x30, &item.ATime);
    GetFileTimeFromMem(p + 0x38, &item.MTime);
    memcpy(item.Hash, p + 0x40, kHashSize);

    // UInt16 shortNameLen = Get16(p + 98);
    UInt16 fileNameLen = Get16(p + 100);
    
    size_t tempPos = pos + 102;
    if (tempPos + fileNameLen > size)
      return S_FALSE;
    
    wchar_t *sz = item.Name.GetBuffer(prefix.Length() + fileNameLen / 2 + 1);
    MyStringCopy(sz, (const wchar_t *)prefix);
    sz += prefix.Length();
    for (UInt16 i = 0; i + 2 <= fileNameLen; i += 2)
      *sz++ = Get16(base + tempPos + i);
    *sz++ = '\0';
    item.Name.ReleaseBuffer();
    if (fileNameLen == 0 && item.isDir() && !item.HasStream())
    {
      item.Attrib = 0x10; // some swm archives have system/hidden attributes for root
      item.Name.Delete(item.Name.Length() - 1);
    }
    items.Add(item);
    pos += (size_t)length;
    if (item.isDir() && (subdirOffset != 0))
    {
      if (subdirOffset >= size)
        return S_FALSE;
      RINOK(ParseDirItem(base, (size_t)subdirOffset, size, item.Name + WCHAR_PATH_SEPARATOR, items));
    }
  }
}