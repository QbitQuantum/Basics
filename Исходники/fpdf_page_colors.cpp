FX_BOOL CPDF_IndexedCS::v_Load(CPDF_Document* pDoc, CPDF_Array* pArray) {
  if (pArray->GetCount() < 4) {
    return FALSE;
  }
  CPDF_Object* pBaseObj = pArray->GetElementValue(1);
  if (pBaseObj == m_pArray) {
    return FALSE;
  }
  CPDF_DocPageData* pDocPageData = pDoc->GetPageData();
  m_pBaseCS = pDocPageData->GetColorSpace(pBaseObj, NULL);
  if (!m_pBaseCS) {
    return FALSE;
  }
  m_pCountedBaseCS = pDocPageData->FindColorSpacePtr(m_pBaseCS->GetArray());
  m_nBaseComponents = m_pBaseCS->CountComponents();
  m_pCompMinMax = FX_Alloc2D(FX_FLOAT, m_nBaseComponents, 2);
  FX_FLOAT defvalue;
  for (int i = 0; i < m_nBaseComponents; i++) {
    m_pBaseCS->GetDefaultValue(i, defvalue, m_pCompMinMax[i * 2],
                               m_pCompMinMax[i * 2 + 1]);
    m_pCompMinMax[i * 2 + 1] -= m_pCompMinMax[i * 2];
  }
  m_MaxIndex = pArray->GetInteger(2);

  CPDF_Object* pTableObj = pArray->GetElementValue(3);
  if (!pTableObj)
    return FALSE;

  if (CPDF_String* pString = pTableObj->AsString()) {
    m_Table = pString->GetString();
  } else if (CPDF_Stream* pStream = pTableObj->AsStream()) {
    CPDF_StreamAcc acc;
    acc.LoadAllData(pStream, FALSE);
    m_Table = CFX_ByteStringC(acc.GetData(), acc.GetSize());
  }
  return TRUE;
}