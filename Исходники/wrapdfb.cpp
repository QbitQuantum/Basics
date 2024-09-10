wxIDirectFBSurfacePtr
wxIDirectFBSurface::CreateCompatible(const wxSize& sz, int flags)
{
    wxSize size(sz);
    if ( size == wxDefaultSize )
    {
        if ( !GetSize(&size.x, &size.y) )
            return NULL;
    }

    wxCHECK_MSG( size.x > 0 && size.y > 0, NULL, "invalid size" );

    DFBSurfaceDescription desc;
    desc.flags = (DFBSurfaceDescriptionFlags)(
            DSDESC_CAPS | DSDESC_WIDTH | DSDESC_HEIGHT | DSDESC_PIXELFORMAT);
    GetCapabilities(&desc.caps);
    GetPixelFormat(&desc.pixelformat);
    desc.width = size.x;
    desc.height = size.y;

    // filter out caps that don't make sense for a new compatible surface:
    int caps = desc.caps;
    caps &= ~DSCAPS_PRIMARY;
    caps &= ~DSCAPS_SUBSURFACE;
    if ( flags & CreateCompatible_NoBackBuffer )
    {
        caps &= ~DSCAPS_DOUBLE;
        caps &= ~DSCAPS_TRIPLE;
    }
    desc.caps = (DFBSurfaceCapabilities)caps;

    wxIDirectFBSurfacePtr snew(wxIDirectFB::Get()->CreateSurface(&desc));
    if ( !snew )
        return NULL;

    if ( desc.pixelformat == DSPF_LUT8 )
    {
        wxIDirectFBPalettePtr pal(GetPalette());
        if ( pal )
        {
            if ( !snew->SetPalette(pal) )
                return NULL;
        }
    }

    return snew;
}