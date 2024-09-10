void CPDF_RenderStatus::DrawShading(CPDF_ShadingPattern* pPattern,
                                    CFX_Matrix* pMatrix,
                                    FX_RECT& clip_rect,
                                    int alpha,
                                    FX_BOOL bAlphaMode) {
  CPDF_Function** pFuncs = pPattern->m_pFunctions;
  int nFuncs = pPattern->m_nFuncs;
  CPDF_Dictionary* pDict = pPattern->m_pShadingObj->GetDict();
  CPDF_ColorSpace* pColorSpace = pPattern->m_pCS;
  if (!pColorSpace) {
    return;
  }
  FX_ARGB background = 0;
  if (!pPattern->m_bShadingObj &&
      pPattern->m_pShadingObj->GetDict()->KeyExist("Background")) {
    CPDF_Array* pBackColor =
        pPattern->m_pShadingObj->GetDict()->GetArray("Background");
    if (pBackColor &&
        pBackColor->GetCount() >= (FX_DWORD)pColorSpace->CountComponents()) {
      CFX_FixedBufGrow<FX_FLOAT, 16> comps(pColorSpace->CountComponents());
      for (int i = 0; i < pColorSpace->CountComponents(); i++) {
        comps[i] = pBackColor->GetNumber(i);
      }
      FX_FLOAT R = 0.0f, G = 0.0f, B = 0.0f;
      pColorSpace->GetRGB(comps, R, G, B);
      background = ArgbEncode(255, (int32_t)(R * 255), (int32_t)(G * 255),
                              (int32_t)(B * 255));
    }
  }
  if (pDict->KeyExist("BBox")) {
    CFX_FloatRect rect = pDict->GetRect("BBox");
    rect.Transform(pMatrix);
    clip_rect.Intersect(rect.GetOutterRect());
  }
  CPDF_DeviceBuffer buffer;
  buffer.Initialize(m_pContext, m_pDevice, &clip_rect, m_pCurObj, 150);
  CFX_Matrix FinalMatrix = *pMatrix;
  FinalMatrix.Concat(*buffer.GetMatrix());
  CFX_DIBitmap* pBitmap = buffer.GetBitmap();
  if (!pBitmap->GetBuffer()) {
    return;
  }
  pBitmap->Clear(background);
  int fill_mode = m_Options.m_Flags;
  switch (pPattern->m_ShadingType) {
    case kInvalidShading:
    case kMaxShading:
      return;
    case kFunctionBasedShading:
      DrawFuncShading(pBitmap, &FinalMatrix, pDict, pFuncs, nFuncs, pColorSpace,
                      alpha);
      break;
    case kAxialShading:
      DrawAxialShading(pBitmap, &FinalMatrix, pDict, pFuncs, nFuncs,
                       pColorSpace, alpha);
      break;
    case kRadialShading:
      DrawRadialShading(pBitmap, &FinalMatrix, pDict, pFuncs, nFuncs,
                        pColorSpace, alpha);
      break;
    case kFreeFormGouraudTriangleMeshShading: {
      DrawFreeGouraudShading(pBitmap, &FinalMatrix,
                             ToStream(pPattern->m_pShadingObj), pFuncs, nFuncs,
                             pColorSpace, alpha);
    } break;
    case kLatticeFormGouraudTriangleMeshShading: {
      DrawLatticeGouraudShading(pBitmap, &FinalMatrix,
                                ToStream(pPattern->m_pShadingObj), pFuncs,
                                nFuncs, pColorSpace, alpha);
    } break;
    case kCoonsPatchMeshShading:
    case kTensorProductPatchMeshShading: {
      DrawCoonPatchMeshes(
          pPattern->m_ShadingType == kTensorProductPatchMeshShading, pBitmap,
          &FinalMatrix, ToStream(pPattern->m_pShadingObj), pFuncs, nFuncs,
          pColorSpace, fill_mode, alpha);
    } break;
  }
  if (bAlphaMode) {
    pBitmap->LoadChannel(FXDIB_Red, pBitmap, FXDIB_Alpha);
  }
  if (m_Options.m_ColorMode == RENDER_COLOR_GRAY) {
    pBitmap->ConvertColorScale(m_Options.m_ForeColor, m_Options.m_BackColor);
  }
  buffer.OutputToDevice();
}