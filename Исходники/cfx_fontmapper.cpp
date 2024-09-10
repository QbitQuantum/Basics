FXFT_Face CFX_FontMapper::FindSubstFont(const CFX_ByteString& name,
                                        FX_BOOL bTrueType,
                                        uint32_t flags,
                                        int weight,
                                        int italic_angle,
                                        int WindowCP,
                                        CFX_SubstFont* pSubstFont) {
  if (!(flags & FXFONT_USEEXTERNATTR)) {
    weight = FXFONT_FW_NORMAL;
    italic_angle = 0;
  }
  CFX_ByteString SubstName = name;
  SubstName.Remove(' ');
  if (bTrueType && name[0] == '@')
    SubstName = name.Mid(1);
  PDF_GetStandardFontName(&SubstName);
  if (SubstName == "Symbol" && !bTrueType) {
    pSubstFont->m_Family = "Chrome Symbol";
    pSubstFont->m_Charset = FXFONT_SYMBOL_CHARSET;
    pSubstFont->m_SubstFlags |= FXFONT_SUBST_STANDARD;
    if (m_FoxitFaces[12])
      return m_FoxitFaces[12];
    const uint8_t* pFontData = nullptr;
    uint32_t size = 0;
    m_pFontMgr->GetBuiltinFont(12, &pFontData, &size);
    m_FoxitFaces[12] = m_pFontMgr->GetFixedFace(pFontData, size, 0);
    return m_FoxitFaces[12];
  }
  if (SubstName == "ZapfDingbats") {
    pSubstFont->m_Family = "Chrome Dingbats";
    pSubstFont->m_Charset = FXFONT_SYMBOL_CHARSET;
    pSubstFont->m_SubstFlags |= FXFONT_SUBST_STANDARD;
    if (m_FoxitFaces[13])
      return m_FoxitFaces[13];
    const uint8_t* pFontData = nullptr;
    uint32_t size = 0;
    m_pFontMgr->GetBuiltinFont(13, &pFontData, &size);
    m_FoxitFaces[13] = m_pFontMgr->GetFixedFace(pFontData, size, 0);
    return m_FoxitFaces[13];
  }
  int iBaseFont = 0;
  CFX_ByteString family;
  CFX_ByteString style;
  bool bHasComma = false;
  bool bHasHyphen = false;
  int find = SubstName.Find(",", 0);
  if (find >= 0) {
    family = SubstName.Left(find);
    PDF_GetStandardFontName(&family);
    style = SubstName.Mid(find + 1);
    bHasComma = true;
  } else {
    family = SubstName;
  }
  for (; iBaseFont < kExternalFontIndex; iBaseFont++) {
    if (family == CFX_ByteStringC(g_Base14FontNames[iBaseFont]))
      break;
  }
  int PitchFamily = 0;
  bool bItalic = false;
  uint32_t nStyle = 0;
  bool bStyleAvail = false;
  if (iBaseFont < kExternalFontIndex) {
    if ((iBaseFont % 4) == 1 || (iBaseFont % 4) == 2)
      nStyle |= FX_FONT_STYLE_Bold;
    if ((iBaseFont % 4) / 2)
      nStyle |= FX_FONT_STYLE_Italic;
    if (iBaseFont < 4)
      PitchFamily |= FXFONT_FF_FIXEDPITCH;
    if (iBaseFont >= 8)
      PitchFamily |= FXFONT_FF_ROMAN;
  } else {
    if (!bHasComma) {
      find = family.ReverseFind('-');
      if (find >= 0) {
        style = family.Mid(find + 1);
        family = family.Left(find);
        bHasHyphen = true;
      }
    }
    if (!bHasHyphen) {
      int nLen = family.GetLength();
      int32_t nRet = GetStyleType(family, true);
      if (nRet > -1) {
        family = family.Left(nLen - g_FontStyles[nRet].len);
        if (nRet == 0)
          nStyle |= FX_FONT_STYLE_Bold;
        else if (nRet == 1)
          nStyle |= FX_FONT_STYLE_Italic;
        else if (nRet == 2)
          nStyle |= (FX_FONT_STYLE_Bold | FX_FONT_STYLE_Italic);
      }
    }
    UpdatePitchFamily(flags, PitchFamily);
  }
  if (!style.IsEmpty()) {
    int nLen = style.GetLength();
    const FX_CHAR* pStyle = style.c_str();
    int i = 0;
    bool bFirstItem = true;
    CFX_ByteString buf;
    while (i < nLen) {
      buf = ParseStyle(pStyle, nLen, i);
      int32_t nRet = GetStyleType(buf, false);
      if ((i && !bStyleAvail) || (!i && nRet < 0)) {
        family = SubstName;
        iBaseFont = kExternalFontIndex;
        break;
      }
      if (nRet >= 0) {
        bStyleAvail = true;
      }
      if (nRet == 1) {
        if (bFirstItem) {
          nStyle |= FX_FONT_STYLE_Italic;
        } else {
          family = SubstName;
          iBaseFont = kExternalFontIndex;
        }
        break;
      }
      if (nRet == 0) {
        if (nStyle & FX_FONT_STYLE_Bold)
          nStyle |= FX_FONT_STYLE_BoldBold;
        else
          nStyle |= FX_FONT_STYLE_Bold;
        bFirstItem = false;
      } else if (nRet == 2) {
        nStyle |= FX_FONT_STYLE_Italic;
        if (nStyle & FX_FONT_STYLE_Bold)
          nStyle |= FX_FONT_STYLE_BoldBold;
        else
          nStyle |= FX_FONT_STYLE_Bold;
        bFirstItem = false;
      }
      i += buf.GetLength() + 1;
    }
  }
  weight = weight ? weight : FXFONT_FW_NORMAL;
  int old_weight = weight;
  if (nStyle) {
    weight =
        nStyle & FX_FONT_STYLE_BoldBold
            ? 900
            : (nStyle & FX_FONT_STYLE_Bold ? FXFONT_FW_BOLD : FXFONT_FW_NORMAL);
  }
  if (nStyle & FX_FONT_STYLE_Italic)
    bItalic = true;
  int iExact = 0;
  int Charset = FXFONT_ANSI_CHARSET;
  if (WindowCP)
    Charset = GetCharsetFromCodePage(WindowCP);
  else if (iBaseFont == kExternalFontIndex && (flags & FXFONT_SYMBOLIC))
    Charset = FXFONT_SYMBOL_CHARSET;
  bool bCJK =
      (Charset == FXFONT_SHIFTJIS_CHARSET || Charset == FXFONT_GB2312_CHARSET ||
       Charset == FXFONT_HANGUL_CHARSET ||
       Charset == FXFONT_CHINESEBIG5_CHARSET);
  if (!m_pFontInfo) {
    pSubstFont->m_SubstFlags |= FXFONT_SUBST_STANDARD;
    return UseInternalSubst(pSubstFont, iBaseFont, italic_angle, old_weight,
                            PitchFamily);
  }
  family = GetFontFamily(family, nStyle);
  CFX_ByteString match = MatchInstalledFonts(TT_NormalizeName(family.c_str()));
  if (match.IsEmpty() && family != SubstName &&
      (!bHasComma && (!bHasHyphen || (bHasHyphen && !bStyleAvail)))) {
    match = MatchInstalledFonts(TT_NormalizeName(SubstName.c_str()));
  }
  if (match.IsEmpty() && iBaseFont >= kExternalFontIndex) {
    if (!bCJK) {
      if (!CheckSupportThirdPartFont(family, PitchFamily)) {
        bItalic = italic_angle != 0;
        weight = old_weight;
      }
    } else {
      pSubstFont->m_bSubstCJK = true;
      if (nStyle)
        pSubstFont->m_WeightCJK = nStyle ? weight : FXFONT_FW_NORMAL;
      if (nStyle & FX_FONT_STYLE_Italic)
        pSubstFont->m_bItalicCJK = true;
    }
  } else {
    italic_angle = 0;
    weight =
        nStyle & FX_FONT_STYLE_BoldBold
            ? 900
            : (nStyle & FX_FONT_STYLE_Bold ? FXFONT_FW_BOLD : FXFONT_FW_NORMAL);
  }
  if (!match.IsEmpty() || iBaseFont < kExternalFontIndex) {
    if (!match.IsEmpty())
      family = match;
    if (iBaseFont < kExternalFontIndex) {
      if (nStyle && !(iBaseFont % 4)) {
        if ((nStyle & 0x3) == 1)
          iBaseFont += 1;
        if ((nStyle & 0x3) == 2)
          iBaseFont += 3;
        if ((nStyle & 0x3) == 3)
          iBaseFont += 2;
      }
      family = g_Base14FontNames[iBaseFont];
      pSubstFont->m_SubstFlags |= FXFONT_SUBST_STANDARD;
    }
  } else {
    if (flags & FXFONT_ITALIC)
      bItalic = true;
  }
  iExact = !match.IsEmpty();
  void* hFont = m_pFontInfo->MapFont(weight, bItalic, Charset, PitchFamily,
                                     family.c_str(), iExact);
  if (iExact)
    pSubstFont->m_SubstFlags |= FXFONT_SUBST_EXACT;
  if (!hFont) {
#ifdef PDF_ENABLE_XFA
    if (flags & FXFONT_EXACTMATCH)
      return nullptr;
#endif  // PDF_ENABLE_XFA
    if (bCJK) {
      bItalic = italic_angle != 0;
      weight = old_weight;
    }
    if (!match.IsEmpty()) {
      hFont = m_pFontInfo->GetFont(match.c_str());
      if (!hFont) {
        return UseInternalSubst(pSubstFont, iBaseFont, italic_angle, old_weight,
                                PitchFamily);
      }
    } else {
      if (Charset == FXFONT_SYMBOL_CHARSET) {
#if _FXM_PLATFORM_ == _FXM_PLATFORM_APPLE_ || \
    _FXM_PLATFORM_ == _FXM_PLATFORM_ANDROID_
        if (SubstName == "Symbol") {
          pSubstFont->m_Family = "Chrome Symbol";
          pSubstFont->m_SubstFlags |= FXFONT_SUBST_STANDARD;
          pSubstFont->m_Charset = FXFONT_SYMBOL_CHARSET;
          if (m_FoxitFaces[12])
            return m_FoxitFaces[12];
          const uint8_t* pFontData = nullptr;
          uint32_t size = 0;
          m_pFontMgr->GetBuiltinFont(12, &pFontData, &size);
          m_FoxitFaces[12] = m_pFontMgr->GetFixedFace(pFontData, size, 0);
          return m_FoxitFaces[12];
        }
#endif
        pSubstFont->m_SubstFlags |= FXFONT_SUBST_NONSYMBOL;
        return FindSubstFont(family, bTrueType, flags & ~FXFONT_SYMBOLIC,
                             weight, italic_angle, 0, pSubstFont);
      }
      if (Charset == FXFONT_ANSI_CHARSET) {
        pSubstFont->m_SubstFlags |= FXFONT_SUBST_STANDARD;
        return UseInternalSubst(pSubstFont, iBaseFont, italic_angle, old_weight,
                                PitchFamily);
      }

      auto it =
          std::find_if(m_FaceArray.begin(), m_FaceArray.end(),
                       [Charset](const FaceData& face) {
                         return face.charset == static_cast<uint32_t>(Charset);
                       });
      if (it == m_FaceArray.end()) {
        return UseInternalSubst(pSubstFont, iBaseFont, italic_angle, old_weight,
                                PitchFamily);
      }
      hFont = m_pFontInfo->GetFont(it->name.c_str());
    }
  }
  if (!hFont)
    return nullptr;

  m_pFontInfo->GetFaceName(hFont, SubstName);
  if (Charset == FXFONT_DEFAULT_CHARSET)
    m_pFontInfo->GetFontCharset(hFont, Charset);
  uint32_t ttc_size = m_pFontInfo->GetFontData(hFont, kTableTTCF, nullptr, 0);
  uint32_t font_size = m_pFontInfo->GetFontData(hFont, 0, nullptr, 0);
  if (font_size == 0 && ttc_size == 0) {
    m_pFontInfo->DeleteFont(hFont);
    return nullptr;
  }
  FXFT_Face face = nullptr;
  if (ttc_size)
    face = GetCachedTTCFace(hFont, kTableTTCF, ttc_size, font_size);
  else
    face = GetCachedFace(hFont, SubstName, weight, bItalic, font_size);
  if (!face) {
    m_pFontInfo->DeleteFont(hFont);
    return nullptr;
  }
  pSubstFont->m_Family = SubstName;
  pSubstFont->m_Charset = Charset;
  bool bNeedUpdateWeight = false;
  if (FXFT_Is_Face_Bold(face))
    bNeedUpdateWeight = weight != FXFONT_FW_BOLD;
  else
    bNeedUpdateWeight = weight != FXFONT_FW_NORMAL;
  if (bNeedUpdateWeight)
    pSubstFont->m_Weight = weight;
  if (bItalic && !FXFT_Is_Face_Italic(face)) {
    if (italic_angle == 0)
      italic_angle = -12;
    else if (FXSYS_abs(italic_angle) < 5)
      italic_angle = 0;
    pSubstFont->m_ItalicAngle = italic_angle;
  }
  m_pFontInfo->DeleteFont(hFont);
  return face;
}