void SimpleFontData::platformInit(bool subpixelAscentDescent) {
  if (!m_platformData.size()) {
    m_fontMetrics.reset();
    m_avgCharWidth = 0;
    m_maxCharWidth = 0;
    return;
  }

  SkPaint::FontMetrics metrics;

  m_platformData.setupPaint(&m_paint);
  m_paint.setTextEncoding(SkPaint::kGlyphID_TextEncoding);
  m_paint.getFontMetrics(&metrics);
  SkTypeface* face = m_paint.getTypeface();
  ASSERT(face);

  int vdmxAscent = 0, vdmxDescent = 0;
  bool isVDMXValid = false;

#if OS(LINUX) || OS(ANDROID)
  // Manually digging up VDMX metrics is only applicable when bytecode hinting
  // using FreeType.  With DirectWrite or CoreText, no bytecode hinting is ever
  // done.  This code should be pushed into FreeType (hinted font metrics).
  static const uint32_t vdmxTag = SkSetFourByteTag('V', 'D', 'M', 'X');
  int pixelSize = m_platformData.size() + 0.5;
  if (!m_paint.isAutohinted() &&
      (m_paint.getHinting() == SkPaint::kFull_Hinting ||
       m_paint.getHinting() == SkPaint::kNormal_Hinting)) {
    size_t vdmxSize = face->getTableSize(vdmxTag);
    if (vdmxSize && vdmxSize < maxVDMXTableSize) {
      uint8_t* vdmxTable = (uint8_t*)WTF::Partitions::fastMalloc(
          vdmxSize, WTF_HEAP_PROFILER_TYPE_NAME(SimpleFontData));
      if (vdmxTable &&
          face->getTableData(vdmxTag, 0, vdmxSize, vdmxTable) == vdmxSize &&
          parseVDMX(&vdmxAscent, &vdmxDescent, vdmxTable, vdmxSize, pixelSize))
        isVDMXValid = true;
      WTF::Partitions::fastFree(vdmxTable);
    }
  }
#endif

  float ascent;
  float descent;

  // Beware those who step here: This code is designed to match Win32 font
  // metrics *exactly* except:
  // - the adjustment of ascent/descent on Linux/Android
  // - metrics.fAscent and .fDesscent are not rounded to int for tiny fonts
  if (isVDMXValid) {
    ascent = vdmxAscent;
    descent = -vdmxDescent;
  } else {
    // For tiny fonts, the rounding of fAscent and fDescent results in equal
    // baseline for different types of text baselines (crbug.com/338908).
    // Please see CanvasRenderingContext2D::getFontBaseline for the heuristic.
    if (subpixelAscentDescent &&
        (-metrics.fAscent < 3 || -metrics.fAscent + metrics.fDescent < 2)) {
      ascent = -metrics.fAscent;
      descent = metrics.fDescent;
    } else {
      ascent = SkScalarRoundToScalar(-metrics.fAscent);
      descent = SkScalarRoundToScalar(metrics.fDescent);
    }
#if OS(LINUX) || OS(ANDROID)
    // When subpixel positioning is enabled, if the descent is rounded down, the
    // descent part of the glyph may be truncated when displayed in a 'overflow:
    // hidden' container.  To avoid that, borrow 1 unit from the ascent when
    // possible.
    // FIXME: This can be removed if sub-pixel ascent/descent is supported.
    if (platformData().getFontRenderStyle().useSubpixelPositioning &&
        descent < SkScalarToFloat(metrics.fDescent) && ascent >= 1) {
      ++descent;
      --ascent;
    }
#endif
  }

#if OS(MACOSX)
  // We are preserving this ascent hack to match Safari's ascent adjustment
  // in their SimpleFontDataMac.mm, for details see crbug.com/445830.
  // We need to adjust Times, Helvetica, and Courier to closely match the
  // vertical metrics of their Microsoft counterparts that are the de facto
  // web standard. The AppKit adjustment of 20% is too big and is
  // incorrectly added to line spacing, so we use a 15% adjustment instead
  // and add it to the ascent.
  DEFINE_STATIC_LOCAL(AtomicString, timesName, ("Times"));
  DEFINE_STATIC_LOCAL(AtomicString, helveticaName, ("Helvetica"));
  DEFINE_STATIC_LOCAL(AtomicString, courierName, ("Courier"));
  String familyName = m_platformData.fontFamilyName();
  if (familyName == timesName || familyName == helveticaName ||
      familyName == courierName)
    ascent += floorf(((ascent + descent) * 0.15f) + 0.5f);
#endif

  m_fontMetrics.setAscent(ascent);
  m_fontMetrics.setDescent(descent);

  float xHeight;
  if (metrics.fXHeight) {
    xHeight = metrics.fXHeight;
#if OS(MACOSX)
    // Mac OS CTFontGetXHeight reports the bounding box height of x,
    // including parts extending below the baseline and apparently no x-height
    // value from the OS/2 table. However, the CSS ex unit
    // expects only parts above the baseline, hence measuring the glyph:
    // http://www.w3.org/TR/css3-values/#ex-unit
    const Glyph xGlyph = glyphForCharacter('x');
    if (xGlyph) {
      FloatRect glyphBounds(boundsForGlyph(xGlyph));
      // SkGlyph bounds, y down, based on rendering at (0,0).
      xHeight = -glyphBounds.y();
    }
#endif
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

  if (platformData().isVerticalAnyUpright() && !isTextOrientationFallback()) {
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
#if OS(WIN)
  m_maxCharWidth = SkScalarRoundToInt(metrics.fMaxCharWidth);

  // Older version of the DirectWrite API doesn't implement support for max
  // char width. Fall back on a multiple of the ascent. This is entirely
  // arbitrary but comes pretty close to the expected value in most cases.
  if (m_maxCharWidth < 1)
    m_maxCharWidth = ascent * 2;
#elif OS(MACOSX)
  // FIXME: The current avg/max character width calculation is not ideal,
  // it should check either the OS2 table or, better yet, query FontMetrics.
  // Sadly FontMetrics provides incorrect data on Mac at the moment.
  // https://crbug.com/420901
  m_maxCharWidth = std::max(m_avgCharWidth, m_fontMetrics.floatAscent());
#else
  // Better would be to rely on either fMaxCharWidth or fAveCharWidth.
  // skbug.com/3087
  m_maxCharWidth = SkScalarRoundToInt(metrics.fXMax - metrics.fXMin);

#endif

#if !OS(MACOSX)
  if (metrics.fAvgCharWidth) {
    m_avgCharWidth = SkScalarRoundToInt(metrics.fAvgCharWidth);
  } else {
#endif
    m_avgCharWidth = xHeight;
    const Glyph xGlyph = glyphForCharacter('x');
    if (xGlyph) {
      m_avgCharWidth = widthForGlyph(xGlyph);
    }
#if !OS(MACOSX)
  }
#endif

  if (int unitsPerEm = face->getUnitsPerEm())
    m_fontMetrics.setUnitsPerEm(unitsPerEm);
}