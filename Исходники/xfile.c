static HRESULT WINAPI ID3DXFileImpl_CreateEnumObject(ID3DXFile *iface, const void *source, D3DXF_FILELOADOPTIONS options, ID3DXFileEnumObject **enum_object)
{
    ID3DXFileImpl *This = impl_from_ID3DXFile(iface);
    ID3DXFileEnumObjectImpl *object;
    IDirectXFileEnumObject *dxfile_enum_object;
    void *dxfile_source;
    DXFILELOADOPTIONS dxfile_options;
    DXFILELOADRESOURCE dxfile_resource;
    DXFILELOADMEMORY dxfile_memory;
    IDirectXFileData *data_object;
    HRESULT ret;

    TRACE("(%p)->(%p, %x, %p)\n", iface, source, options, enum_object);

    if (!enum_object)
        return E_POINTER;

    *enum_object = NULL;

    if (options == D3DXF_FILELOAD_FROMFILE)
    {
        dxfile_source = (void*)source;
        dxfile_options = DXFILELOAD_FROMFILE;
    }
    else if (options == D3DXF_FILELOAD_FROMRESOURCE)
    {
        D3DXF_FILELOADRESOURCE *resource = (D3DXF_FILELOADRESOURCE*)source;

        dxfile_resource.hModule = resource->hModule;
        dxfile_resource.lpName = resource->lpName;
        dxfile_resource.lpType = resource->lpType;
        dxfile_source = &dxfile_resource;
        dxfile_options = DXFILELOAD_FROMRESOURCE;
    }
    else if (options == D3DXF_FILELOAD_FROMMEMORY)
    {
        D3DXF_FILELOADMEMORY *memory = (D3DXF_FILELOADMEMORY*)source;

        dxfile_memory.lpMemory = memory->lpMemory;
        dxfile_memory.dSize = memory->dSize;
        dxfile_source = &dxfile_memory;
        dxfile_options = DXFILELOAD_FROMMEMORY;
    }
    else
    {
        FIXME("Source type %u is not handled yet\n", options);
        return E_NOTIMPL;
    }

    object = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*object));
    if (!object)
        return E_OUTOFMEMORY;

    object->ID3DXFileEnumObject_iface.lpVtbl = &ID3DXFileEnumObject_Vtbl;
    object->ref = 1;

    ret = IDirectXFile_CreateEnumObject(This->dxfile, dxfile_source, dxfile_options, &dxfile_enum_object);

    if (ret != S_OK)
    {
        HeapFree(GetProcessHeap(), 0, object);
        return ret;
    }

    /* Fill enum object with top level data objects */
    while (SUCCEEDED(ret = IDirectXFileEnumObject_GetNextDataObject(dxfile_enum_object, &data_object)))
    {
        if (object->children)
            object->children = HeapReAlloc(GetProcessHeap(), 0, object->children, sizeof(*object->children) * (object->nb_children + 1));
        else
            object->children = HeapAlloc(GetProcessHeap(), 0, sizeof(*object->children));
        if (!object->children)
        {
            ret = E_OUTOFMEMORY;
            break;
        }
        ret = ID3DXFileDataImpl_Create((IDirectXFileObject*)data_object, &object->children[object->nb_children]);
        if (ret != S_OK)
            break;
        object->nb_children++;
    }

    IDirectXFileEnumObject_Release(dxfile_enum_object);

    if (ret != DXFILEERR_NOMOREOBJECTS)
        WARN("Cannot get all top level data objects\n");

    TRACE("Found %u children\n", object->nb_children);

    *enum_object = &object->ID3DXFileEnumObject_iface;

    return S_OK;
}