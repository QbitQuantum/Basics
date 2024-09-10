static HRESULT WINAPI VideoRenderer_GetSourceRect(BaseControlVideo* iface, RECT *pSourceRect)
{
    VideoRendererImpl *This = impl_from_BaseControlVideo(iface);
    CopyRect(pSourceRect,&This->SourceRect);
    return S_OK;
}