FXFT_Face CFX_FontMapper::FindSubstFont(const CFX_ByteString& name, FX_BOOL bTrueType, FX_DWORD flags,
                                        int weight, int italic_angle, int WindowCP, CFX_SubstFont* pSubstFont)
{
    if (!(flags & FXFONT_USEEXTERNATTR)) {
        weight = FXFONT_FW_NORMAL;
        italic_angle = 0;
    }
    CFX_ByteString SubstName = name;
    SubstName.Remove(0x20);
    if (bTrueType) {
        if (name[0] == '@') {
            SubstName = name.Mid(1);
        }
    }
    _PDF_GetStandardFontName(SubstName);
    if (SubstName == FX_BSTRC("Symbol") && !bTrueType) {
        pSubstFont->m_Family = "Chrome Symbol";
        pSubstFont->m_Charset = FXFONT_SYMBOL_CHARSET;
        pSubstFont->m_SubstFlags |= FXFONT_SUBST_STANDARD;
        if (m_FoxitFaces[12]) {
            return m_FoxitFaces[12];
        }
        FX_LPCBYTE pFontData = NULL;
        FX_DWORD size = 0;
        m_pFontMgr->GetStandardFont(pFontData, size, 12);
        m_FoxitFaces[12] = m_pFontMgr->GetFixedFace(pFontData, size, 0);
        return m_FoxitFaces[12];
    }
    if (SubstName == FX_BSTRC("ZapfDingbats")) {
        pSubstFont->m_Family = "Chrome Dingbats";
        pSubstFont->m_Charset = FXFONT_SYMBOL_CHARSET;
        pSubstFont->m_SubstFlags |= FXFONT_SUBST_STANDARD;
        if (m_FoxitFaces[13]) {
            return m_FoxitFaces[13];
        }
        FX_LPCBYTE pFontData = NULL;
        FX_DWORD size = 0;
        m_pFontMgr->GetStandardFont(pFontData, size, 13);
        m_FoxitFaces[13] = m_pFontMgr->GetFixedFace(pFontData, size, 0);
        return m_FoxitFaces[13];
    }
    int iBaseFont = 0;
    CFX_ByteString family, style;
    FX_BOOL	bHasComma = FALSE;
    FX_BOOL bHasHypen = FALSE;
    int find = SubstName.Find(FX_BSTRC(","), 0);
    if (find >= 0) {
        family = SubstName.Left(find);
        _PDF_GetStandardFontName(family);
        style = SubstName.Mid(find + 1);
        bHasComma = TRUE;
    } else {
        family = SubstName;
    }
    for (; iBaseFont < 12; iBaseFont ++)
        if (family == CFX_ByteStringC(g_Base14FontNames[iBaseFont])) {
            break;
        }
    int PitchFamily = 0;
    FX_BOOL bItalic = FALSE;
    FX_DWORD nStyle = 0;
    FX_BOOL bStyleAvail = FALSE;
    FX_BOOL bFamilyStyleIsWhole = FALSE;
    FX_BOOL bNextF = FALSE;
    if (iBaseFont < 12) {
        family = g_Base14FontNames[iBaseFont];
        if ((iBaseFont % 4) == 1 || (iBaseFont % 4) == 2) {
            nStyle |= FX_FONT_STYLE_Bold;
        }
        if ((iBaseFont % 4) / 2) {
            nStyle |= FX_FONT_STYLE_Italic;
        }
        if (iBaseFont < 4) {
            PitchFamily |= FXFONT_FF_FIXEDPITCH;
        }
        if (iBaseFont >= 8) {
            PitchFamily |= FXFONT_FF_ROMAN;
        }
    } else {
        if (!bHasComma) {
            find = family.ReverseFind('-');
            if (find >= 0) {
                style = family.Mid(find + 1);
                family = family.Left(find);
                bHasHypen = TRUE;
            }
        }
        if (!bHasHypen) {
            int nLen = family.GetLength();
            FX_INT32 nRet = GetStyleType(family, TRUE);
            if (nRet > -1) {
                family = family.Left(nLen - g_FontStyles[nRet].len);
                if (nRet == 0) {
                    nStyle |= FX_FONT_STYLE_Bold;
                }
                if (nRet == 1) {
                    nStyle |= FX_FONT_STYLE_Italic;
                }
                if (nRet == 2) {
                    nStyle |= (FX_FONT_STYLE_Bold | FX_FONT_STYLE_Italic);
                }
            }
        }
        if (flags & FXFONT_SERIF) {
            PitchFamily |= FXFONT_FF_ROMAN;
        }
        if (flags & FXFONT_SCRIPT) {
            PitchFamily |= FXFONT_FF_SCRIPT;
        }
        if (flags & FXFONT_FIXED_PITCH) {
            PitchFamily |= FXFONT_FF_FIXEDPITCH;
        }
    }
    if (!style.IsEmpty()) {
        int nLen = style.GetLength();
        FX_LPCSTR pStyle = style;
        int i = 0;
        FX_BOOL bFirstItem = TRUE;
        CFX_ByteString buf;
        while (i < nLen) {
            buf = ParseStyle(pStyle, nLen, i);
            FX_INT32 nRet = GetStyleType(buf, FALSE);
            if ((i && !bStyleAvail) || (!i && nRet < 0)) {
                family = SubstName;
                iBaseFont = 12;
                break;
            } else if (nRet >= 0) {
                bStyleAvail = TRUE;
            }
            if (nRet == 0) {
                if (nStyle & FX_FONT_STYLE_Bold) {
                    nStyle |= FX_FONT_STYLE_BoldBold;
                } else {
                    nStyle |= FX_FONT_STYLE_Bold;
                }
                bFirstItem = FALSE;
            }
            if (nRet == 1) {
                if (bFirstItem) {
                    nStyle |= FX_FONT_STYLE_Italic;
                } else {
                    family = SubstName;
                    iBaseFont = 12;
                }
                break;
            }
            if (nRet == 2) {
                nStyle |= FX_FONT_STYLE_Italic;
                if (nStyle & FX_FONT_STYLE_Bold) {
                    nStyle |= FX_FONT_STYLE_BoldBold;
                } else {
                    nStyle |= FX_FONT_STYLE_Bold;
                }
                bFirstItem = FALSE;
            }
            i += buf.GetLength() + 1;
        }
    }
    weight = weight ? weight : FXFONT_FW_NORMAL;
    int old_weight = weight;
    if (nStyle) {
        weight = nStyle & FX_FONT_STYLE_BoldBold ? 900 : (nStyle & FX_FONT_STYLE_Bold ? FXFONT_FW_BOLD : FXFONT_FW_NORMAL);
    }
    if (nStyle & FX_FONT_STYLE_Italic) {
        bItalic = TRUE;
    }
    FX_BOOL bCJK = FALSE;
    FX_BOOL bExact = FALSE;
    int Charset = FXFONT_ANSI_CHARSET;
    if (WindowCP) {
        Charset = _GetCharsetFromCodePage(WindowCP);
    } else if (iBaseFont == 12 && (flags & FXFONT_SYMBOLIC)) {
        Charset = FXFONT_SYMBOL_CHARSET;
    }
    if (Charset == FXFONT_SHIFTJIS_CHARSET || Charset == FXFONT_GB2312_CHARSET ||
            Charset == FXFONT_HANGEUL_CHARSET || Charset == FXFONT_CHINESEBIG5_CHARSET) {
        bCJK = TRUE;
    }
    if (m_pFontInfo == NULL) {
        pSubstFont->m_SubstFlags |= FXFONT_SUBST_STANDARD;
        return UseInternalSubst(pSubstFont, iBaseFont, italic_angle, old_weight, PitchFamily);
    }
    family = _GetFontFamily(family, nStyle);
    CFX_ByteString match = MatchInstalledFonts(_TT_NormalizeName(family));
    if (match.IsEmpty() && family != SubstName && (!bHasComma && (!bHasHypen || (bHasHypen && !bStyleAvail)))) {
        match = MatchInstalledFonts(_TT_NormalizeName(SubstName));
    }
    if (match.IsEmpty() && iBaseFont >= 12) {
        if (!bCJK) {
            if (!CheckSupportThirdPartFont(family, PitchFamily)) {
                if (italic_angle != 0) {
                    bItalic = TRUE;
                } else {
                    bItalic = FALSE;
                }
                weight = old_weight;
            }
        } else {
            pSubstFont->m_bSubstOfCJK = TRUE;
            if (nStyle) {
                pSubstFont->m_WeightCJK = weight;
            } else {
                pSubstFont->m_WeightCJK = FXFONT_FW_NORMAL;
            }
            if (nStyle & FX_FONT_STYLE_Italic) {
                pSubstFont->m_bItlicCJK = TRUE;
            }
        }
    } else {
        italic_angle = 0;
        weight = nStyle & FX_FONT_STYLE_BoldBold ? 900 : (nStyle & FX_FONT_STYLE_Bold ? FXFONT_FW_BOLD : FXFONT_FW_NORMAL);
    }
    if (!match.IsEmpty() || iBaseFont < 12) {
        pSubstFont->m_SubstFlags |= FXFONT_SUBST_EXACT;
        if (!match.IsEmpty()) {
            family = match;
        }
        if (iBaseFont < 12) {
            if (nStyle && !(iBaseFont % 4)) {
                if ((nStyle & 0x3) == 1) {
                    iBaseFont += 1;
                }
                if ((nStyle & 0x3) == 2) {
                    iBaseFont += 3;
                }
                if ((nStyle & 0x3) == 3) {
                    iBaseFont += 2;
                }
            }
            if (m_pFontMgr->m_ExternalFonts[iBaseFont].m_pFontData) {
                if (m_FoxitFaces[iBaseFont]) {
                    return m_FoxitFaces[iBaseFont];
                }
                m_FoxitFaces[iBaseFont] = m_pFontMgr->GetFixedFace(m_pFontMgr->m_ExternalFonts[iBaseFont].m_pFontData,
                                          m_pFontMgr->m_ExternalFonts[iBaseFont].m_dwSize, 0);
                if (m_FoxitFaces[iBaseFont]) {
                    return m_FoxitFaces[iBaseFont];
                }
            } else {
                family = g_Base14FontNames[iBaseFont];
            }
            pSubstFont->m_SubstFlags |= FXFONT_SUBST_STANDARD;
        }
    } else {
        if (flags & FXFONT_ITALIC) {
            bItalic = TRUE;
        }
    }
    bExact = !match.IsEmpty();
    void* hFont = m_pFontInfo->MapFont(weight, bItalic, Charset, PitchFamily, family, bExact);
    if (bExact) {
        pSubstFont->m_SubstFlags |= FXFONT_SUBST_EXACT;
    }
    if (hFont == NULL) {
        if (bCJK) {
            if (italic_angle != 0) {
                bItalic = TRUE;
            } else {
                bItalic = FALSE;
            }
            weight = old_weight;
        }
        if (!match.IsEmpty()) {
            hFont = m_pFontInfo->GetFont(match);
            if (hFont == NULL) {
                return UseInternalSubst(pSubstFont, iBaseFont, italic_angle, old_weight, PitchFamily);
            }
        } else {
            if (Charset == FXFONT_SYMBOL_CHARSET) {
#if _FXM_PLATFORM_  == _FXM_PLATFORM_APPLE_ || _FXM_PLATFORM_  == _FXM_PLATFORM_ANDROID_
                if (SubstName == FX_BSTRC("Symbol")) {
                    pSubstFont->m_Family = "Chrome Symbol";
                    pSubstFont->m_SubstFlags |= FXFONT_SUBST_STANDARD;
                    pSubstFont->m_Charset = FXFONT_SYMBOL_CHARSET;
                    if (m_FoxitFaces[12]) {
                        return m_FoxitFaces[12];
                    }
                    FX_LPCBYTE pFontData = NULL;
                    FX_DWORD size = 0;
                    m_pFontMgr->GetStandardFont(pFontData, size, 12);
                    m_FoxitFaces[12] = m_pFontMgr->GetFixedFace(pFontData, size, 0);
                    return m_FoxitFaces[12];
                } else {
                    pSubstFont->m_SubstFlags |= FXFONT_SUBST_NONSYMBOL;
                    return FindSubstFont(family, bTrueType, flags & ~FXFONT_SYMBOLIC, weight, italic_angle, 0, pSubstFont);
                }
#else
                pSubstFont->m_SubstFlags |= FXFONT_SUBST_NONSYMBOL;
                return FindSubstFont(family, bTrueType, flags & ~FXFONT_SYMBOLIC, weight, italic_angle, 0, pSubstFont);
#endif
            }
            if (Charset == FXFONT_ANSI_CHARSET) {
                pSubstFont->m_SubstFlags |= FXFONT_SUBST_STANDARD;
                return UseInternalSubst(pSubstFont, iBaseFont, italic_angle, old_weight, PitchFamily);
            }
            int index = m_CharsetArray.Find(Charset);
            if (index < 0) {
                return UseInternalSubst(pSubstFont, iBaseFont, italic_angle, old_weight, PitchFamily);
            } else {
                hFont = m_pFontInfo->GetFont(m_FaceArray[index]);
            }
        }
    }
    pSubstFont->m_ExtHandle = m_pFontInfo->RetainFont(hFont);
    if (hFont == NULL) {
        return NULL;
    }
    m_pFontInfo->GetFaceName(hFont, SubstName);
    if (Charset == FXFONT_DEFAULT_CHARSET) {
        m_pFontInfo->GetFontCharset(hFont, Charset);
    }
    FX_DWORD ttc_size = m_pFontInfo->GetFontData(hFont, 0x74746366, NULL, 0);
    FX_DWORD font_size = m_pFontInfo->GetFontData(hFont, 0, NULL, 0);
    if(font_size == 0 && ttc_size == 0) {
        m_pFontInfo->DeleteFont(hFont);
        return NULL;
    }
    FXFT_Face face = NULL;
    if (ttc_size) {
        FX_BYTE temp[1024];
        m_pFontInfo->GetFontData(hFont, 0x74746366, temp, 1024);
        FX_DWORD checksum = 0;
        for (int i = 0; i < 256; i ++) {
            checksum += ((FX_DWORD*)temp)[i];
        }
        FX_LPBYTE pFontData;
        face = m_pFontMgr->GetCachedTTCFace(ttc_size, checksum, ttc_size - font_size, pFontData);
        if (face == NULL) {
            pFontData = FX_Alloc(FX_BYTE, ttc_size);
            if (pFontData) {
                m_pFontInfo->GetFontData(hFont, 0x74746366, pFontData, ttc_size);
                face = m_pFontMgr->AddCachedTTCFace(ttc_size, checksum, pFontData, ttc_size,
                                                    ttc_size - font_size);
            }
        }
    } else {
        FX_LPBYTE pFontData;
        face = m_pFontMgr->GetCachedFace(SubstName, weight, bItalic, pFontData);
        if (face == NULL) {
            pFontData = FX_Alloc(FX_BYTE, font_size);
            if (!pFontData) {
                m_pFontInfo->DeleteFont(hFont);
                return NULL;
            }
            m_pFontInfo->GetFontData(hFont, 0, pFontData, font_size);
            face = m_pFontMgr->AddCachedFace(SubstName, weight, bItalic, pFontData, font_size, m_pFontInfo->GetFaceIndex(hFont));
        }
    }
    if (face == NULL) {
        m_pFontInfo->DeleteFont(hFont);
        return NULL;
    }
    pSubstFont->m_Family = SubstName;
    pSubstFont->m_Charset = Charset;
    FX_BOOL bNeedUpdateWeight = FALSE;
    if (FXFT_Is_Face_Bold(face)) {
        if (weight == FXFONT_FW_BOLD) {
            bNeedUpdateWeight = FALSE;
        } else {
            bNeedUpdateWeight = TRUE;
        }
    } else {
        if (weight == FXFONT_FW_NORMAL) {
            bNeedUpdateWeight = FALSE;
        } else {
            bNeedUpdateWeight = TRUE;
        }
    }
    if (bNeedUpdateWeight) {
        pSubstFont->m_Weight = weight;
    }
    if (bItalic && !FXFT_Is_Face_Italic(face)) {
        if (italic_angle == 0) {
            italic_angle = -12;
        } else if (FXSYS_abs(italic_angle) < 5) {
            italic_angle = 0;
        }
        pSubstFont->m_ItalicAngle = italic_angle;
    }
    m_pFontInfo->DeleteFont(hFont);
    return face;
}