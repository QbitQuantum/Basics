/*** IDirectXFile methods ***/
static HRESULT WINAPI IDirectXFileImpl_CreateEnumObject(IDirectXFile* iface, LPVOID pvSource, DXFILELOADOPTIONS dwLoadOptions, LPDIRECTXFILEENUMOBJECT* ppEnumObj)
{
  IDirectXFileImpl *This = impl_from_IDirectXFile(iface);
  IDirectXFileEnumObjectImpl* object;
  HRESULT hr;
  LPBYTE file_buffer;
  DWORD file_size;
  DWORD bytes_written;

  TRACE("(%p/%p)->(%p,%x,%p)\n", This, iface, pvSource, dwLoadOptions, ppEnumObj);

  if (!ppEnumObj)
    return DXFILEERR_BADVALUE;

  /* Only lowest 4 bits are relevant in DXFILELOADOPTIONS */
  dwLoadOptions &= 0xF;

  hr = IDirectXFileEnumObjectImpl_Create(&object);
  if (FAILED(hr))
    return hr;

  if (dwLoadOptions == DXFILELOAD_FROMFILE)
  {
    HANDLE hFile, file_mapping;

    TRACE("Open source file '%s'\n", (char*)pvSource);

    hFile = CreateFileA(pvSource, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
      TRACE("File '%s' not found\n", (char*)pvSource);
      return DXFILEERR_FILENOTFOUND;
    }

    file_size = GetFileSize(hFile, NULL);

    file_mapping = CreateFileMappingA(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
    CloseHandle(hFile);
    if (!file_mapping)
    {
      hr = DXFILEERR_BADFILETYPE;
      goto error;
    }

    object->mapped_memory = MapViewOfFile(file_mapping, FILE_MAP_READ, 0, 0, 0);
    CloseHandle(file_mapping);
    if (!object->mapped_memory)
    {
      hr = DXFILEERR_BADFILETYPE;
      goto error;
    }
    file_buffer = object->mapped_memory;
  }
  else if (dwLoadOptions == DXFILELOAD_FROMRESOURCE)
  {
    HRSRC resource_info;
    HGLOBAL resource_data;
    LPDXFILELOADRESOURCE lpdxflr = pvSource;

    TRACE("Source in resource (module = %p, name = %s, type = %s)\n", lpdxflr->hModule, debugstr_a(lpdxflr->lpName), debugstr_a(lpdxflr->lpType));

    resource_info = FindResourceA(lpdxflr->hModule, lpdxflr->lpName, lpdxflr->lpType);
    if (!resource_info)
    {
      hr = DXFILEERR_RESOURCENOTFOUND;
      goto error;
    }

    file_size = SizeofResource(lpdxflr->hModule, resource_info);

    resource_data = LoadResource(lpdxflr->hModule, resource_info);
    if (!resource_data)
    {
      hr = DXFILEERR_BADRESOURCE;
      goto error;
    }

    file_buffer = LockResource(resource_data);
    if (!file_buffer)
    {
      hr = DXFILEERR_BADRESOURCE;
      goto error;
    }
  }
  else if (dwLoadOptions == DXFILELOAD_FROMMEMORY)
  {
    LPDXFILELOADMEMORY lpdxflm = pvSource;

    TRACE("Source in memory at %p with size %d\n", lpdxflm->lpMemory, lpdxflm->dSize);

    file_buffer = lpdxflm->lpMemory;
    file_size = lpdxflm->dSize;
  }
  else
  {
    FIXME("Source type %d is not handled yet\n", dwLoadOptions);
    hr = DXFILEERR_NOTDONEYET;
    goto error;
  }

  TRACE("File size is %d bytes\n", file_size);

  if (TRACE_ON(d3dxof_dump))
  {
    static USHORT num;
    char tmp[12];
    HANDLE file;
    sprintf(tmp, "file%05u.x", num++);

    file = CreateFileA(tmp, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, 0, NULL);
    if (file != INVALID_HANDLE_VALUE)
    {
      WriteFile(file, file_buffer, file_size, &bytes_written, NULL);
      CloseHandle(file);
    }
  }

  object->pDirectXFile = This;

  object->buf.pdxf = This;
  object->buf.token_present = FALSE;
  object->buf.buffer = file_buffer;
  object->buf.rem_bytes = file_size;
  hr = parse_header(&object->buf, &object->decomp_buffer);
  if (FAILED(hr))
    goto error;

  /* Check if there are templates defined before the object */
  if (!parse_templates(&object->buf, TRUE))
  {
    hr = DXFILEERR_PARSEERROR;
    goto error;
  }

  if (TRACE_ON(d3dxof))
  {
    ULONG i;
    TRACE("Registered templates (%d):\n", This->nb_xtemplates);
    for (i = 1; i < This->nb_xtemplates; i++)
      DPRINTF("%s - %s\n", This->xtemplates[i].name, debugstr_guid(&This->xtemplates[i].class_id));
  }

  *ppEnumObj = &object->IDirectXFileEnumObject_iface;

  return DXFILE_OK;

error:
  IDirectXFileEnumObject_Release(&object->IDirectXFileEnumObject_iface);
  *ppEnumObj = NULL;

  return hr;
}