//----------------------------------------------------------------------------//
void OpenGLApplePBTextureTarget::restoreTexture()
{
    const Sizef sz(d_area.getSize());
    d_area.setSize(Sizef(0.0f, 0.0f));

    OpenGLTextureTarget::restoreTexture();
    initialiseTexture();
    declareRenderSize(sz);
}