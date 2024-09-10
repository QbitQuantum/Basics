//----------------------------------------------------------------------------//
DirectFBRenderTarget::DirectFBRenderTarget(DirectFBRenderer& owner,
                                           IDirectFBSurface& target) :
    d_owner(owner),
    d_target(target),
    d_area(0, 0, 0, 0)
{
    int w, h;
    d_target.GetSize(&d_target, &w, &h);
    setArea(Rectf(d_area.getPosition(),
                 Sizef(static_cast<float>(w), static_cast<float>(h))));
}