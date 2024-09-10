void SimpleFontData::platformInit() {
  if (!m_platformData.size()) {
    m_fontMetrics.reset();
    m_avgCharWidth = 0;
    m_maxCharWidth = 0;
    return;
  }

  SkPaint paint;
  SkPaint::FontMetrics metrics;

  m_platformData.setupPaint(&paint);
  paint.getFontMetrics(&metrics);
  SkTypeface* face = paint.getTypeface();
  ASSERT(face);

  int vdmxAscent = 0, vdmxDescent = 0;
  bool isVDMXValid = false;

#if OS(LINUX) || OS(ANDROID)
  // Manually digging up VDMX metrics is only applicable when bytecode hinting
  // using FreeType. With GDI, the metrics will already have taken this into
  // account (as needed). With DirectWrite or CoreText, no bytecode hinting is
  // ever done. This code should be pushed into FreeType (hinted font metrics).
  static const uint32_t vdmxTag = SkSetFourByteTag('V', 'D', 'M', 'X');
  int pixelSize = m_platformData.size() + 0.5;
  if (!paint.isAutohinted() &&
      (paint.getHinting() == SkPaint::kFull_Hinting ||
       paint.getHinting() == SkPaint::kNormal_Hinting)) {
    size_t vdmxSize = face->getTableSize(vdmxTag);
    if (vdmxSize && vdmxSize < maxVDMXTableSize) {
      uint8_t* vdmxTable = (uint8_t*)fastMalloc(vdmxSize);
      if (vdmxTable &&
          face->getTableData(vdmxTag, 0, vdmxSize, vdmxTable) == vdmxSize &&
          parseVDMX(&vdmxAscent, &vdmxDescent, vdmxTable, vdmxSize, pixelSize))
        isVDMXValid = true;
      fastFree(vdmxTable);
    }
  }
#endif

  float ascent;
  float descent;

  // Beware those who step here: This code is designed to match Win32 font
  // metrics *exactly* (except the adjustment of ascent/descent on
  // Linux/Android).
  if (isVDMXValid) {
    ascent = vdmxAscent;
    descent = -vdmxDescent;
  } else {
    ascent = SkScalarRoundToInt(-metrics.fAscent);
    descent = SkScalarRoundToInt(metrics.fDescent);
#if OS(LINUX) || OS(ANDROID)
    // When subpixel positioning is enabled, if the descent is rounded down, the
    // descent part of the glyph may be truncated when displayed in a 'overflow:
    // hidden' container. To avoid that, borrow 1 unit from the ascent when
    // possible.
    // FIXME: This can be removed if sub-pixel ascent/descent is supported.
    if (platformData().fontRenderStyle().useSubpixelPositioning &&
        descent < SkScalarToFloat(metrics.fDescent) && ascent >= 1) {
      ++descent;
      --ascent;
    }
#endif
  }

  m_fontMetrics.setAscent(ascent);
  m_fontMetrics.setDescent(descent);

  float xHeight;
  if (metrics.fXHeight) {
    xHeight = metrics.fXHeight;
    m_fontMetrics.setXHeight(xHeight);
  } else {
    xHeight = ascent * 0.56;  // Best guess from Windows font metrics.
    m_fontMetrics.setXHeight(xHeight);
    m_fontMetrics.setHasXHeight(false);
  }

  float lineGap = SkScalarToFloat(metrics.fLeading);
  m_fontMetrics.setLineGap(lineGap);
  m_fontMetrics.setLineSpacing(lroundf(ascent) + lroundf(descent) +
                               lroundf(lineGap));

  SkScalar underlineThickness, underlinePosition;
  if (metrics.hasUnderlineThickness(&underlineThickness) &&
      metrics.hasUnderlinePosition(&underlinePosition)) {
    m_fontMetrics.setUnderlineThickness(SkScalarToFloat(underlineThickness));
    m_fontMetrics.setUnderlinePosition(SkScalarToFloat(-underlinePosition));
  }

  if (platformData().orientation() == Vertical &&
      !isTextOrientationFallback()) {
    static const uint32_t vheaTag = SkSetFourByteTag('v', 'h', 'e', 'a');
    static const uint32_t vorgTag = SkSetFourByteTag('V', 'O', 'R', 'G');
    size_t vheaSize = face->getTableSize(vheaTag);
    size_t vorgSize = face->getTableSize(vorgTag);
    if ((vheaSize > 0) || (vorgSize > 0))
      m_hasVerticalGlyphs = true;
  }

  // In WebKit/WebCore/platform/graphics/SimpleFontData.cpp, m_spaceWidth is
  // calculated for us, but we need to calculate m_maxCharWidth and
  // m_avgCharWidth in order for text entry widgets to be sized correctly.
  // FIXME: This seems incorrect and should probably use fMaxCharWidth as
  // the code path above.
  SkScalar xRange = metrics.fXMax - metrics.fXMin;
  m_maxCharWidth =
      SkScalarRoundToInt(xRange * SkScalarRoundToInt(m_platformData.size()));

  if (metrics.fAvgCharWidth)
    m_avgCharWidth = SkScalarRoundToInt(metrics.fAvgCharWidth);
  else {
    m_avgCharWidth = xHeight;

    GlyphPage* glyphPageZero = GlyphPageTreeNode::getRootChild(this, 0)->page();

    if (glyphPageZero) {
      static const UChar32 xChar = 'x';
      const Glyph xGlyph = glyphPageZero->glyphForCharacter(xChar);

      if (xGlyph) {
        // In widthForGlyph(), xGlyph will be compared with
        // m_zeroWidthSpaceGlyph, which isn't initialized yet here.
        // Initialize it with zero to make sure widthForGlyph() returns
        // the right width.
        m_zeroWidthSpaceGlyph = 0;
        m_avgCharWidth = widthForGlyph(xGlyph);
      }
    }
  }

  if (int unitsPerEm = face->getUnitsPerEm())
    m_fontMetrics.setUnitsPerEm(unitsPerEm);
}