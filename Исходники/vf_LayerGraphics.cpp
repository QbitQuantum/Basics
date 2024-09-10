LayerGraphics::~LayerGraphics ()
{
  // Convert from premultiplied to normal.
  //
  unPremultiplyImage (m_fill);

  // Extract the layer's RGB components as Image::RGB
  //
  Image fillImage (ChannelImageType::fromImage (m_fill, -1));

  // Extract the layer's alpha mask as a single channel image.
  //
  Image maskImage (ChannelImageType::fromImage (m_fill, PixelARGB::indexA));

  // Obtain bitmap data for mask and fill.
  //
  Pixels fillPixels (fillImage);
  Pixels maskPixels (maskImage);
  Pixels workPixels (m_work);

  m_options.innerShadow (fillPixels, maskPixels);

  m_options.dropShadow (m_work, maskImage);

  if (m_options.general.groupInteriorEffects)
  {
    // satin
    m_options.colourOverlay (fillPixels);
    m_options.gradientOverlay (fillPixels);
    m_options.patternOverlay (fillPixels);
    m_options.innerGlow (fillPixels, maskPixels);
    m_options.fill (m_work, m_fill);
  }
  else
  {
    m_options.fill (m_work, m_fill);
    m_options.colourOverlay (workPixels);
    m_options.gradientOverlay (workPixels);
    m_options.patternOverlay (workPixels);
    m_options.innerGlow (workPixels, maskPixels);
  }

  m_options.outerGlow (workPixels, maskPixels);
  m_options.bevelEmboss (workPixels, maskPixels);
  m_options.stroke (workPixels, maskPixels);

  // Copy the work image onto the background layer
  // using normal mode and the general opacity.
  copyImage (
    m_base,
    m_workOrigin,
    m_work,
    m_work.getBounds (),
    BlendMode::modeNormal,
    m_options.general.opacity);
}