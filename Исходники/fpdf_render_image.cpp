CFX_DIBitmap* CPDF_RenderStatus::LoadSMask(CPDF_Dictionary* pSMaskDict,
        FX_RECT* pClipRect, const CFX_AffineMatrix* pMatrix)
{
    if (pSMaskDict == NULL) {
        return NULL;
    }
    CFX_DIBitmap* pMask = NULL;
    int width = pClipRect->right - pClipRect->left;
    int height = pClipRect->bottom - pClipRect->top;
    FX_BOOL bLuminosity = FALSE;
    bLuminosity = pSMaskDict->GetConstString(FX_BSTRC("S")) != FX_BSTRC("Alpha");
    CPDF_Stream* pGroup = pSMaskDict->GetStream(FX_BSTRC("G"));
    if (pGroup == NULL) {
        return NULL;
    }
    CPDF_Function* pFunc = NULL;
    CPDF_Object* pFuncObj = pSMaskDict->GetElementValue(FX_BSTRC("TR"));
    if (pFuncObj && (pFuncObj->GetType() == PDFOBJ_DICTIONARY || pFuncObj->GetType() == PDFOBJ_STREAM)) {
        pFunc = CPDF_Function::Load(pFuncObj);
    }
    CFX_AffineMatrix matrix = *pMatrix;
    matrix.TranslateI(-pClipRect->left, -pClipRect->top);
    CPDF_Form form(m_pContext->m_pDocument, m_pContext->m_pPageResources, pGroup);
    form.ParseContent(NULL, NULL, NULL, NULL);
    CFX_FxgeDevice bitmap_device;
#if _FXM_PLATFORM_  == _FXM_PLATFORM_APPLE_
    if (!bitmap_device.Create(width, height, bLuminosity ? FXDIB_Rgb32 : FXDIB_8bppMask)) {
        return NULL;
    }
#else
    if (!bitmap_device.Create(width, height, bLuminosity ? FXDIB_Rgb : FXDIB_8bppMask)) {
        return NULL;
    }
#endif
    CFX_DIBitmap& bitmap = *bitmap_device.GetBitmap();
    CPDF_Object* pCSObj = NULL;
    CPDF_ColorSpace* pCS = NULL;
    if (bLuminosity) {
        CPDF_Array* pBC = pSMaskDict->GetArray(FX_BSTRC("BC"));
        FX_ARGB back_color = 0xff000000;
        if (pBC) {
            pCSObj = pGroup->GetDict()->GetDict(FX_BSTRC("Group"))->GetElementValue(FX_BSTRC("CS"));
            pCS = m_pContext->m_pDocument->LoadColorSpace(pCSObj);
            if (pCS) {
                FX_FLOAT R, G, B;
                FX_DWORD num_floats = 8;
                if (pCS->CountComponents() > (FX_INT32)num_floats) {
                    num_floats = (FX_DWORD)pCS->CountComponents();
                }
                CFX_FixedBufGrow<FX_FLOAT, 8> float_array(num_floats);
                FX_FLOAT* pFloats = float_array;
                FXSYS_memset32(pFloats, 0, num_floats * sizeof(FX_FLOAT));
                int count = pBC->GetCount() > 8 ? 8 : pBC->GetCount();
                for (int i = 0; i < count; i ++) {
                    pFloats[i] = pBC->GetNumber(i);
                }
                pCS->GetRGB(pFloats, R, G, B);
                back_color = 0xff000000 | ((FX_INT32)(R * 255) << 16) | ((FX_INT32)(G * 255) << 8) | (FX_INT32)(B * 255);
                m_pContext->m_pDocument->GetPageData()->ReleaseColorSpace(pCSObj);
            }
        }
        bitmap.Clear(back_color);
    } else {
        bitmap.Clear(0);
    }
    CPDF_Dictionary* pFormResource = NULL;
    if (form.m_pFormDict) {
        pFormResource = form.m_pFormDict->GetDict(FX_BSTRC("Resources"));
    }
    CPDF_RenderOptions options;
    options.m_ColorMode = bLuminosity ? RENDER_COLOR_NORMAL : RENDER_COLOR_ALPHA;
    CPDF_RenderStatus status;
    status.Initialize(m_Level + 1, m_pContext, &bitmap_device, NULL, NULL, NULL, NULL,
                      &options, 0, m_bDropObjects, pFormResource, TRUE, NULL, 0, pCS ? pCS->GetFamily() : 0, bLuminosity);
    status.RenderObjectList(&form, &matrix);
    pMask = FX_NEW CFX_DIBitmap;
    if (!pMask->Create(width, height, FXDIB_8bppMask)) {
        delete pMask;
        return NULL;
    }
    FX_LPBYTE dest_buf = pMask->GetBuffer();
    int dest_pitch = pMask->GetPitch();
    FX_LPBYTE src_buf = bitmap.GetBuffer();
    int src_pitch = bitmap.GetPitch();
    FX_LPBYTE pTransfer = FX_Alloc(FX_BYTE, 256);
    if (pFunc) {
        CFX_FixedBufGrow<FX_FLOAT, 16> results(pFunc->CountOutputs());
        for (int i = 0; i < 256; i ++) {
            FX_FLOAT input = (FX_FLOAT)i / 255.0f;
            int nresult;
            pFunc->Call(&input, 1, results, nresult);
            pTransfer[i] = FXSYS_round(results[0] * 255);
        }
    } else {
        for (int i = 0; i < 256; i ++) {
            pTransfer[i] = i;
        }
    }
    if (bLuminosity) {
        int Bpp = bitmap.GetBPP() / 8;
        for (int row = 0; row < height; row ++) {
            FX_LPBYTE dest_pos = dest_buf + row * dest_pitch;
            FX_LPBYTE src_pos = src_buf + row * src_pitch;
            for (int col = 0; col < width; col ++) {
                *dest_pos ++ = pTransfer[FXRGB2GRAY(src_pos[2], src_pos[1], *src_pos)];
                src_pos += Bpp;
            }
        }
    } else if (pFunc) {
        int size = dest_pitch * height;
        for (int i = 0; i < size; i ++) {
            dest_buf[i] = pTransfer[src_buf[i]];
        }
    } else {
        FXSYS_memcpy32(dest_buf, src_buf, dest_pitch * height);
    }
    if (pFunc) {
        delete pFunc;
    }
    FX_Free(pTransfer);
    return pMask;
}