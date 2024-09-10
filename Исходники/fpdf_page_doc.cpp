CPDF_ColorSpace* CPDF_DocPageData::GetColorSpace(CPDF_Object* pCSObj, CPDF_Dictionary* pResources)
{
    if (!pCSObj) {
        return NULL;
    }
    if (pCSObj->GetType() == PDFOBJ_NAME) {
        CFX_ByteString name = pCSObj->GetConstString();
        CPDF_ColorSpace* pCS = _CSFromName(name);
        if (!pCS && pResources) {
            CPDF_Dictionary* pList = pResources->GetDict(FX_BSTRC("ColorSpace"));
            if (pList) {
                pCSObj = pList->GetElementValue(name);
                return GetColorSpace(pCSObj, NULL);
            }
        }
        if (pCS == NULL || pResources == NULL) {
            return pCS;
        }
        CPDF_Dictionary* pColorSpaces = pResources->GetDict(FX_BSTRC("ColorSpace"));
        if (pColorSpaces == NULL) {
            return pCS;
        }
        CPDF_Object* pDefaultCS = NULL;
        switch (pCS->GetFamily()) {
        case PDFCS_DEVICERGB:
            pDefaultCS = pColorSpaces->GetElementValue(FX_BSTRC("DefaultRGB"));
            break;
        case PDFCS_DEVICEGRAY:
            pDefaultCS = pColorSpaces->GetElementValue(FX_BSTRC("DefaultGray"));
            break;
        case PDFCS_DEVICECMYK:
            pDefaultCS = pColorSpaces->GetElementValue(FX_BSTRC("DefaultCMYK"));
            break;
        }
        if (pDefaultCS == NULL) {
            return pCS;
        }
        return GetColorSpace(pDefaultCS, NULL);
    }
    if (pCSObj->GetType() != PDFOBJ_ARRAY) {
        return NULL;
    }
    CPDF_Array* pArray = (CPDF_Array*)pCSObj;
    if (pArray->GetCount() == 0) {
        return NULL;
    }
    if (pArray->GetCount() == 1) {
        return GetColorSpace(pArray->GetElementValue(0), pResources);
    }
    CPDF_CountedObject<CPDF_ColorSpace*>* csData = NULL;
    if (m_ColorSpaceMap.Lookup(pCSObj, csData)) {
        if (csData->m_Obj) {
            csData->m_nCount++;
            return csData->m_Obj;
        }
    }
    FX_BOOL bNew = FALSE;
    if (!csData) {
        csData = FX_NEW CPDF_CountedObject<CPDF_ColorSpace*>;
        if (!csData) {
            return NULL;
        }
        bNew = TRUE;
    }
    CPDF_ColorSpace* pCS = CPDF_ColorSpace::Load(m_pPDFDoc, pArray);
    if (!pCS) {
        if (bNew) {
            delete csData;
        }
        return NULL;
    }
    csData->m_nCount = 2;
    csData->m_Obj = pCS;
    m_ColorSpaceMap.SetAt(pCSObj, csData);
    return pCS;
}