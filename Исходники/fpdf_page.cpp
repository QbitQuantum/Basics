void CPDF_Page::Load(CPDF_Document* pDocument, CPDF_Dictionary* pPageDict, FX_BOOL bPageCache)
{
    m_pDocument = (CPDF_Document*)pDocument;
    m_pFormDict = pPageDict;
    if (bPageCache) {
        m_pPageRender = CPDF_ModuleMgr::Get()->GetRenderModule()->CreatePageCache(this);
    }
    if (pPageDict == NULL) {
        m_PageWidth = m_PageHeight = 100 * 1.0f;
        m_pPageResources = m_pResources = NULL;
        return;
    }
    CPDF_Object* pageAttr = GetPageAttr(FX_BSTRC("Resources"));
    m_pResources = pageAttr ? pageAttr->GetDict() : NULL;
    m_pPageResources = m_pResources;
    CPDF_Object* pRotate = GetPageAttr(FX_BSTRC("Rotate"));
    int rotate = 0;
    if (pRotate) {
        rotate = pRotate->GetInteger() / 90 % 4;
    }
    if (rotate < 0) {
        rotate += 4;
    }
    CPDF_Array* pMediaBox, *pCropBox;
    pMediaBox = (CPDF_Array*)GetPageAttr(FX_BSTRC("MediaBox"));
    CFX_FloatRect mediabox;
    if (pMediaBox) {
        mediabox = pMediaBox->GetRect();
        mediabox.Normalize();
    }
    if (mediabox.IsEmpty()) {
        mediabox = CFX_FloatRect(0, 0, 612, 792);
    }
    pCropBox = (CPDF_Array*)GetPageAttr(FX_BSTRC("CropBox"));
    if (pCropBox) {
        m_BBox = pCropBox->GetRect();
        m_BBox.Normalize();
    }
    if (m_BBox.IsEmpty()) {
        m_BBox = mediabox;
    } else {
        m_BBox.Intersect(mediabox);
    }
    if (rotate % 2) {
        m_PageHeight = m_BBox.right - m_BBox.left;
        m_PageWidth = m_BBox.top - m_BBox.bottom;
    } else {
        m_PageWidth = m_BBox.right - m_BBox.left;
        m_PageHeight = m_BBox.top - m_BBox.bottom;
    }
    switch (rotate) {
    case 0:
        m_PageMatrix.Set(1.0f, 0, 0, 1.0f, -m_BBox.left, -m_BBox.bottom);
        break;
    case 1:
        m_PageMatrix.Set(0, -1.0f, 1.0f, 0, -m_BBox.bottom, m_BBox.right);
        break;
    case 2:
        m_PageMatrix.Set(-1.0f, 0, 0, -1.0f, m_BBox.right, m_BBox.top);
        break;
    case 3:
        m_PageMatrix.Set(0, 1.0f, -1.0f, 0, m_BBox.top, -m_BBox.left);
        break;
    }
    m_Transparency = PDFTRANS_ISOLATED;
    LoadTransInfo();
}