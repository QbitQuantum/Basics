CPDF_Font* CPDF_Document::AddWindowsFont(LOGFONTA* pLogFont, FX_BOOL bVert, FX_BOOL bTranslateName)
{
    pLogFont->lfHeight = -1000;
    pLogFont->lfWidth = 0;
    HGDIOBJ hFont = CreateFontIndirectA(pLogFont);
    HDC hDC = CreateCompatibleDC(NULL);
    hFont = SelectObject(hDC, hFont);
    int tm_size = GetOutlineTextMetrics(hDC, 0, NULL);
    if (tm_size == 0) {
        hFont = SelectObject(hDC, hFont);
        DeleteObject(hFont);
        DeleteDC(hDC);
        return NULL;
    }
    LPBYTE tm_buf = FX_Alloc(BYTE, tm_size);
    OUTLINETEXTMETRIC* ptm = (OUTLINETEXTMETRIC*)tm_buf;
    GetOutlineTextMetrics(hDC, tm_size, ptm);
    int flags = 0, italicangle, ascend, descend, capheight, bbox[4];
    if (pLogFont->lfItalic) {
        flags |= PDFFONT_ITALIC;
    }
    if ((pLogFont->lfPitchAndFamily & 3) == FIXED_PITCH) {
        flags |= PDFFONT_FIXEDPITCH;
    }
    if ((pLogFont->lfPitchAndFamily & 0xf8) == FF_ROMAN) {
        flags |= PDFFONT_SERIF;
    }
    if ((pLogFont->lfPitchAndFamily & 0xf8) == FF_SCRIPT) {
        flags |= PDFFONT_SCRIPT;
    }
    FX_BOOL bCJK = pLogFont->lfCharSet == CHINESEBIG5_CHARSET || pLogFont->lfCharSet == GB2312_CHARSET ||
                   pLogFont->lfCharSet == HANGEUL_CHARSET || pLogFont->lfCharSet == SHIFTJIS_CHARSET;
    CFX_ByteString basefont;
    if (bTranslateName && bCJK) {
        basefont = _FPDF_GetPSNameFromTT(hDC);
    }
    if (basefont.IsEmpty()) {
        basefont = pLogFont->lfFaceName;
    }
    italicangle = ptm->otmItalicAngle / 10;
    ascend = ptm->otmrcFontBox.top;
    descend = ptm->otmrcFontBox.bottom;
    capheight = ptm->otmsCapEmHeight;
    bbox[0] = ptm->otmrcFontBox.left;
    bbox[1] = ptm->otmrcFontBox.bottom;
    bbox[2] = ptm->otmrcFontBox.right;
    bbox[3] = ptm->otmrcFontBox.top;
    FX_Free(tm_buf);
    basefont.Replace(" ", "");
    CPDF_Dictionary* pBaseDict = FX_NEW CPDF_Dictionary;
    pBaseDict->SetAtName("Type", "Font");
    CPDF_Dictionary* pFontDict = pBaseDict;
    if (!bCJK) {
        if (pLogFont->lfCharSet == ANSI_CHARSET || pLogFont->lfCharSet == DEFAULT_CHARSET ||
                pLogFont->lfCharSet == SYMBOL_CHARSET) {
            if (pLogFont->lfCharSet == SYMBOL_CHARSET) {
                flags |= PDFFONT_SYMBOLIC;
            } else {
                flags |= PDFFONT_NONSYMBOLIC;
            }
            pBaseDict->SetAtName(FX_BSTRC("Encoding"), "WinAnsiEncoding");
        } else {
            flags |= PDFFONT_NONSYMBOLIC;
            int i;
            for (i = 0; i < sizeof g_FX_CharsetUnicodes / sizeof(FX_CharsetUnicodes); i ++)
                if (g_FX_CharsetUnicodes[i].m_Charset == pLogFont->lfCharSet) {
                    break;
                }
            if (i < sizeof g_FX_CharsetUnicodes / sizeof(FX_CharsetUnicodes)) {
                CPDF_Dictionary* pEncoding = FX_NEW CPDF_Dictionary;
                pEncoding->SetAtName(FX_BSTRC("BaseEncoding"), "WinAnsiEncoding");
                CPDF_Array* pArray = FX_NEW CPDF_Array;
                pArray->AddInteger(128);
                const FX_WCHAR* pUnicodes = g_FX_CharsetUnicodes[i].m_pUnicodes;
                for (int j = 0; j < 128; j ++) {
                    CFX_ByteString name = PDF_AdobeNameFromUnicode(pUnicodes[j]);
                    if (name.IsEmpty()) {
                        pArray->AddName(FX_BSTRC(".notdef"));
                    } else {
                        pArray->AddName(name);
                    }
                }
                pEncoding->SetAt(FX_BSTRC("Differences"), pArray);
                AddIndirectObject(pEncoding);
                pBaseDict->SetAtReference(FX_BSTRC("Encoding"), this, pEncoding);
            }
        }
        if (pLogFont->lfWeight > FW_MEDIUM && pLogFont->lfItalic) {
            basefont += ",BoldItalic";
        } else if (pLogFont->lfWeight > FW_MEDIUM) {
            basefont += ",Bold";
        } else if (pLogFont->lfItalic) {
            basefont += ",Italic";
        }
        pBaseDict->SetAtName("Subtype", "TrueType");
        pBaseDict->SetAtName("BaseFont", basefont);
        pBaseDict->SetAtNumber("FirstChar", 32);
        pBaseDict->SetAtNumber("LastChar", 255);
        int char_widths[224];
        GetCharWidth(hDC, 32, 255, char_widths);
        CPDF_Array* pWidths = FX_NEW CPDF_Array;
        for (int i = 0; i < 224; i ++) {
            pWidths->AddInteger(char_widths[i]);
        }
        pBaseDict->SetAt("Widths", pWidths);
    } else {
        flags |= PDFFONT_NONSYMBOLIC;
        pFontDict = FX_NEW CPDF_Dictionary;
        CFX_ByteString cmap;
        CFX_ByteString ordering;
        int supplement;
        CPDF_Array* pWidthArray = FX_NEW CPDF_Array;
        switch (pLogFont->lfCharSet) {
        case CHINESEBIG5_CHARSET:
            cmap = bVert ? "ETenms-B5-V" : "ETenms-B5-H";
            ordering = "CNS1";
            supplement = 4;
            pWidthArray->AddInteger(1);
            _InsertWidthArray(hDC, 0x20, 0x7e, pWidthArray);
            break;
        case GB2312_CHARSET:
            cmap = bVert ? "GBK-EUC-V" : "GBK-EUC-H";
            ordering = "GB1", supplement = 2;
            pWidthArray->AddInteger(7716);
            _InsertWidthArray(hDC, 0x20, 0x20, pWidthArray);
            pWidthArray->AddInteger(814);
            _InsertWidthArray(hDC, 0x21, 0x7e, pWidthArray);
            break;
        case HANGEUL_CHARSET:
            cmap = bVert ? "KSCms-UHC-V" : "KSCms-UHC-H";
            ordering = "Korea1";
            supplement = 2;
            pWidthArray->AddInteger(1);
            _InsertWidthArray(hDC, 0x20, 0x7e, pWidthArray);
            break;
        case SHIFTJIS_CHARSET:
            cmap = bVert ? "90ms-RKSJ-V" : "90ms-RKSJ-H";
            ordering = "Japan1";
            supplement = 5;
            pWidthArray->AddInteger(231);
            _InsertWidthArray(hDC, 0x20, 0x7d, pWidthArray);
            pWidthArray->AddInteger(326);
            _InsertWidthArray(hDC, 0xa0, 0xa0, pWidthArray);
            pWidthArray->AddInteger(327);
            _InsertWidthArray(hDC, 0xa1, 0xdf, pWidthArray);
            pWidthArray->AddInteger(631);
            _InsertWidthArray(hDC, 0x7e, 0x7e, pWidthArray);
            break;
        }
        pBaseDict->SetAtName("Subtype", "Type0");
        pBaseDict->SetAtName("BaseFont", basefont);
        pBaseDict->SetAtName("Encoding", cmap);
        pFontDict->SetAt("W", pWidthArray);
        pFontDict->SetAtName("Type", "Font");
        pFontDict->SetAtName("Subtype", "CIDFontType2");
        pFontDict->SetAtName("BaseFont", basefont);
        CPDF_Dictionary* pCIDSysInfo = FX_NEW CPDF_Dictionary;
        pCIDSysInfo->SetAtString("Registry", "Adobe");
        pCIDSysInfo->SetAtString("Ordering", ordering);
        pCIDSysInfo->SetAtInteger("Supplement", supplement);
        pFontDict->SetAt("CIDSystemInfo", pCIDSysInfo);
        CPDF_Array* pArray = FX_NEW CPDF_Array;
        pBaseDict->SetAt("DescendantFonts", pArray);
        AddIndirectObject(pFontDict);
        pArray->AddReference(this, pFontDict);
    }
    AddIndirectObject(pBaseDict);
    CPDF_Dictionary* pFontDesc = FX_NEW CPDF_Dictionary;
    pFontDesc->SetAtName("Type", "FontDescriptor");
    pFontDesc->SetAtName("FontName", basefont);
    pFontDesc->SetAtInteger("Flags", flags);
    CPDF_Array* pBBox = FX_NEW CPDF_Array;
    for (int i = 0; i < 4; i ++) {
        pBBox->AddInteger(bbox[i]);
    }
    pFontDesc->SetAt("FontBBox", pBBox);
    pFontDesc->SetAtInteger("ItalicAngle", italicangle);
    pFontDesc->SetAtInteger("Ascent", ascend);
    pFontDesc->SetAtInteger("Descent", descend);
    pFontDesc->SetAtInteger("CapHeight", capheight);
    pFontDesc->SetAtInteger("StemV", pLogFont->lfWeight / 5);
    AddIndirectObject(pFontDesc);
    pFontDict->SetAtReference("FontDescriptor", this, pFontDesc);
    hFont = SelectObject(hDC, hFont);
    DeleteObject(hFont);
    DeleteDC(hDC);
    return LoadFont(pBaseDict);
}