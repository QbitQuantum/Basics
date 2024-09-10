static int OpenDisplay(vout_display_t *vd)
{
    vout_display_sys_t *sys = vd->sys;

    DFBSurfaceDescription dsc;
    /*dsc.flags = DSDESC_CAPS | DSDESC_HEIGHT | DSDESC_WIDTH;*/
    dsc.flags = DSDESC_CAPS;
    dsc.caps  = DSCAPS_PRIMARY | DSCAPS_FLIPPING;
    /*dsc.width = 352;*/
    /*dsc.height = 240;*/

    IDirectFB *directfb = NULL;
    if (DirectFBCreate(&directfb) != DFB_OK || !directfb)
        return VLC_EGENERIC;
    sys->directfb = directfb;

    IDirectFBSurface *primary = NULL;
    if (directfb->CreateSurface(directfb, &dsc, &primary) || !primary)
        return VLC_EGENERIC;
    sys->primary = primary;

    primary->GetSize(primary, &sys->width, &sys->height);
    primary->GetPixelFormat(primary, &sys->pixel_format);
    primary->FillRectangle(primary, 0, 0, sys->width, sys->height);
    primary->Flip(primary, NULL, 0);

    return VLC_SUCCESS;
}