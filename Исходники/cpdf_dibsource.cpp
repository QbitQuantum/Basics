bool CPDF_DIBSource::LoadColorInfo(const CPDF_Dictionary* pFormResources,
                                   const CPDF_Dictionary* pPageResources) {
  m_bpc_orig = m_pDict->GetIntegerFor("BitsPerComponent");
  if (m_pDict->GetIntegerFor("ImageMask"))
    m_bImageMask = true;

  if (m_bImageMask || !m_pDict->KeyExist("ColorSpace")) {
    if (!m_bImageMask) {
      CPDF_Object* pFilter = m_pDict->GetDirectObjectFor("Filter");
      if (pFilter) {
        CFX_ByteString filter;
        if (pFilter->IsName()) {
          filter = pFilter->GetString();
        } else if (CPDF_Array* pArray = pFilter->AsArray()) {
          filter = pArray->GetStringAt(pArray->GetCount() - 1);
        }

        if (filter == "JPXDecode") {
          m_bDoBpcCheck = false;
          return true;
        }
      }
    }
    m_bImageMask = true;
    m_bpc = m_nComponents = 1;
    CPDF_Array* pDecode = m_pDict->GetArrayFor("Decode");
    m_bDefaultDecode = !pDecode || !pDecode->GetIntegerAt(0);
    return true;
  }

  CPDF_Object* pCSObj = m_pDict->GetDirectObjectFor("ColorSpace");
  if (!pCSObj)
    return false;

  CPDF_DocPageData* pDocPageData = m_pDocument->GetPageData();
  if (pFormResources)
    m_pColorSpace = pDocPageData->GetColorSpace(pCSObj, pFormResources);
  if (!m_pColorSpace)
    m_pColorSpace = pDocPageData->GetColorSpace(pCSObj, pPageResources);
  if (!m_pColorSpace)
    return false;

  m_Family = m_pColorSpace->GetFamily();
  m_nComponents = m_pColorSpace->CountComponents();
  if (m_Family == PDFCS_ICCBASED && pCSObj->IsName()) {
    CFX_ByteString cs = pCSObj->GetString();
    if (cs == "DeviceGray") {
      m_nComponents = 1;
    } else if (cs == "DeviceRGB") {
      m_nComponents = 3;
    } else if (cs == "DeviceCMYK") {
      m_nComponents = 4;
    }
  }
  ValidateDictParam();
  m_pCompData = GetDecodeAndMaskArray(m_bDefaultDecode, m_bColorKey);
  return !!m_pCompData;
}