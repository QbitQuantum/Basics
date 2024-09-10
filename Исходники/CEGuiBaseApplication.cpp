//----------------------------------------------------------------------------//
void CEGuiBaseApplication::updateFPSGeometry()
{
    const CEGUI::Rectf scrn(d_renderer->getDefaultRenderTarget().getArea());
    const glm::vec3 position(scrn.getSize().d_width - 120.0f, 0.0f, 0.0f);

    const size_t bufferCount = d_FPSGeometry.size();
    for (size_t i = 0; i < bufferCount; ++i)
    {
        d_FPSGeometry[i]->setClippingRegion(scrn);
        d_FPSGeometry[i]->setTranslation(position);
    }
}