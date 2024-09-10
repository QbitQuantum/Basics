static void STDMETHODCALLTYPE d3d8_cubetexture_wined3d_object_destroyed(void *parent)
{
    HeapFree(GetProcessHeap(), 0, parent);
}