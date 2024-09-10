bool CPDF_ShadingPattern::Load() {
  if (m_ShadingType != kInvalidShading)
    return true;

  CPDF_Dictionary* pShadingDict =
      m_pShadingObj ? m_pShadingObj->GetDict() : nullptr;
  if (!pShadingDict)
    return false;

  m_pFunctions.clear();
  CPDF_Object* pFunc = pShadingDict->GetDirectObjectFor("Function");
  if (pFunc) {
    if (CPDF_Array* pArray = pFunc->AsArray()) {
      m_pFunctions.resize(std::min<size_t>(pArray->GetCount(), 4));
      for (size_t i = 0; i < m_pFunctions.size(); ++i)
        m_pFunctions[i] = CPDF_Function::Load(pArray->GetDirectObjectAt(i));
    } else {
      m_pFunctions.push_back(CPDF_Function::Load(pFunc));
    }
  }
  CPDF_Object* pCSObj = pShadingDict->GetDirectObjectFor("ColorSpace");
  if (!pCSObj)
    return false;

  CPDF_DocPageData* pDocPageData = m_pDocument->GetPageData();
  m_pCS = pDocPageData->GetColorSpace(pCSObj, nullptr);
  if (m_pCS)
    m_pCountedCS = pDocPageData->FindColorSpacePtr(m_pCS->GetArray());

  m_ShadingType = ToShadingType(pShadingDict->GetIntegerFor("ShadingType"));

  // We expect to have a stream if our shading type is a mesh.
  if (IsMeshShading() && !ToStream(m_pShadingObj))
    return false;

  return true;
}