FX_BOOL CPDF_RenderStatus::ProcessType3Text(const CPDF_TextObject* textobj, const CFX_AffineMatrix* pObj2Device)
{
    CPDF_Type3Font* pType3Font = textobj->m_TextState.GetFont()->GetType3Font();
    for (int j = 0; j < m_Type3FontCache.GetSize(); j++)
        if ((CPDF_Type3Font*)m_Type3FontCache.GetAt(j) == pType3Font) {
            return TRUE;
        }
    CFX_Matrix dCTM = m_pDevice->GetCTM();
    FX_FLOAT sa = FXSYS_fabs(dCTM.a);
    FX_FLOAT sd = FXSYS_fabs(dCTM.d);
    CFX_AffineMatrix text_matrix;
    textobj->GetTextMatrix(&text_matrix);
    CFX_AffineMatrix char_matrix = pType3Font->GetFontMatrix();
    FX_FLOAT font_size = textobj->m_TextState.GetFontSize();
    char_matrix.Scale(font_size, font_size);
    FX_ARGB fill_argb = GetFillArgb(textobj, TRUE);
    int fill_alpha = FXARGB_A(fill_argb);
    int device_class = m_pDevice->GetDeviceClass();
    FXTEXT_GLYPHPOS* pGlyphAndPos = NULL;
    if (device_class == FXDC_DISPLAY) {
        pGlyphAndPos = FX_Alloc(FXTEXT_GLYPHPOS, textobj->m_nChars);
    } else if (fill_alpha < 255) {
        return FALSE;
    }
    CPDF_RefType3Cache refTypeCache(pType3Font);
    FX_DWORD *pChars = textobj->m_pCharCodes;
    if (textobj->m_nChars == 1) {
        pChars = (FX_DWORD*)(&textobj->m_pCharCodes);
    }
    for (int iChar = 0; iChar < textobj->m_nChars; iChar ++) {
        FX_DWORD charcode = pChars[iChar];
        if (charcode == (FX_DWORD) - 1) {
            continue;
        }
        CPDF_Type3Char* pType3Char = pType3Font->LoadChar(charcode);
        if (pType3Char == NULL) {
            continue;
        }
        CFX_AffineMatrix matrix = char_matrix;
        matrix.e += iChar ? textobj->m_pCharPos[iChar - 1] : 0;
        matrix.Concat(text_matrix);
        matrix.Concat(*pObj2Device);
        if (!pType3Char->LoadBitmap(m_pContext)) {
            if (pGlyphAndPos) {
                for (int i = 0; i < iChar; i ++) {
                    FXTEXT_GLYPHPOS& glyph = pGlyphAndPos[i];
                    if (glyph.m_pGlyph == NULL) {
                        continue;
                    }
                    m_pDevice->SetBitMask(&glyph.m_pGlyph->m_Bitmap,
                                          glyph.m_OriginX + glyph.m_pGlyph->m_Left,
                                          glyph.m_OriginY - glyph.m_pGlyph->m_Top, fill_argb);
                }
                FX_Free(pGlyphAndPos);
                pGlyphAndPos = NULL;
            }
            CPDF_GraphicStates* pStates = CloneObjStates(textobj, FALSE);
            CPDF_RenderOptions Options = m_Options;
            Options.m_Flags |= RENDER_FORCE_HALFTONE | RENDER_RECT_AA;
            Options.m_Flags &= ~RENDER_FORCE_DOWNSAMPLE;
            CPDF_Dictionary* pFormResource = NULL;
            if (pType3Char->m_pForm && pType3Char->m_pForm->m_pFormDict) {
                pFormResource = pType3Char->m_pForm->m_pFormDict->GetDict(FX_BSTRC("Resources"));
            }
            if (fill_alpha == 255) {
                CPDF_RenderStatus status;
                status.Initialize(m_Level + 1, m_pContext, m_pDevice, NULL, NULL, this, pStates, &Options,
                                  pType3Char->m_pForm->m_Transparency, m_bDropObjects, pFormResource, FALSE, pType3Char, fill_argb);
                status.m_Type3FontCache.Append(m_Type3FontCache);
                status.m_Type3FontCache.Add(pType3Font);
                m_pDevice->SaveState();
                status.RenderObjectList(pType3Char->m_pForm, &matrix);
                m_pDevice->RestoreState();
            } else {
                CFX_FloatRect rect_f = pType3Char->m_pForm->CalcBoundingBox();
                rect_f.Transform(&matrix);
                FX_RECT rect = rect_f.GetOutterRect();
                CFX_FxgeDevice bitmap_device;
                if (!bitmap_device.Create((int)(rect.Width() * sa), (int)(rect.Height() * sd), FXDIB_Argb)) {
                    return TRUE;
                }
                bitmap_device.GetBitmap()->Clear(0);
                CPDF_RenderStatus status;
                status.Initialize(m_Level + 1, m_pContext, &bitmap_device, NULL, NULL, this, pStates, &Options,
                                  pType3Char->m_pForm->m_Transparency, m_bDropObjects, pFormResource, FALSE, pType3Char, fill_argb);
                status.m_Type3FontCache.Append(m_Type3FontCache);
                status.m_Type3FontCache.Add(pType3Font);
                matrix.TranslateI(-rect.left, -rect.top);
                matrix.Scale(sa, sd);
                status.RenderObjectList(pType3Char->m_pForm, &matrix);
                m_pDevice->SetDIBits(bitmap_device.GetBitmap(), rect.left, rect.top);
            }
            delete pStates;
        } else if (pType3Char->m_pBitmap) {
            if (device_class == FXDC_DISPLAY) {
                CPDF_Type3Cache* pCache = GetCachedType3(pType3Font);
                refTypeCache.m_dwCount++;
                CFX_GlyphBitmap* pBitmap = pCache->LoadGlyph(charcode, &matrix, sa, sd);
                if (pBitmap == NULL) {
                    continue;
                }
                int origin_x = FXSYS_round(matrix.e);
                int origin_y = FXSYS_round(matrix.f);
                if (pGlyphAndPos) {
                    pGlyphAndPos[iChar].m_pGlyph = pBitmap;
                    pGlyphAndPos[iChar].m_OriginX = origin_x;
                    pGlyphAndPos[iChar].m_OriginY = origin_y;
                } else {
                    m_pDevice->SetBitMask(&pBitmap->m_Bitmap, origin_x + pBitmap->m_Left, origin_y - pBitmap->m_Top, fill_argb);
                }
            } else {
                CFX_AffineMatrix image_matrix = pType3Char->m_ImageMatrix;
                image_matrix.Concat(matrix);
                CPDF_ImageRenderer renderer;
                if (renderer.Start(this, pType3Char->m_pBitmap, fill_argb, 255, &image_matrix, 0, FALSE)) {
                    renderer.Continue(NULL);
                }
                if (!renderer.m_Result) {
                    return FALSE;
                }
            }
        }
    }
    if (pGlyphAndPos) {
        FX_RECT rect = FXGE_GetGlyphsBBox(pGlyphAndPos, textobj->m_nChars, 0, sa, sd);
        CFX_DIBitmap bitmap;
        if (!bitmap.Create((int)(rect.Width() * sa), (int)(rect.Height() * sd), FXDIB_8bppMask)) {
            FX_Free(pGlyphAndPos);
            return TRUE;
        }
        bitmap.Clear(0);
        for (int iChar = 0; iChar < textobj->m_nChars; iChar ++) {
            FXTEXT_GLYPHPOS& glyph = pGlyphAndPos[iChar];
            if (glyph.m_pGlyph == NULL) {
                continue;
            }
            bitmap.TransferBitmap((int)((glyph.m_OriginX + glyph.m_pGlyph->m_Left - rect.left) * sa),
                                  (int)((glyph.m_OriginY - glyph.m_pGlyph->m_Top - rect.top) * sd),
                                  glyph.m_pGlyph->m_Bitmap.GetWidth(), glyph.m_pGlyph->m_Bitmap.GetHeight(),
                                  &glyph.m_pGlyph->m_Bitmap, 0, 0);
        }
        m_pDevice->SetBitMask(&bitmap, rect.left, rect.top, fill_argb);
        FX_Free(pGlyphAndPos);
    }
    return TRUE;
}