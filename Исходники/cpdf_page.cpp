CPDF_Page::CPDF_Page(CPDF_Document* pDocument,
                     CPDF_Dictionary* pPageDict,
                     bool bPageCache)
    : m_PageWidth(100),
      m_PageHeight(100),
      m_pView(nullptr),
      m_pPageRender(bPageCache ? new CPDF_PageRenderCache(this) : nullptr) {
  m_pFormDict = pPageDict;
  m_pDocument = pDocument;
  if (!pPageDict)
    return;

  CPDF_Object* pageAttr = GetPageAttr("Resources");
  m_pResources = pageAttr ? pageAttr->GetDict() : nullptr;
  m_pPageResources = m_pResources;
  CPDF_Object* pRotate = GetPageAttr("Rotate");
  int rotate = pRotate ? pRotate->GetInteger() / 90 % 4 : 0;
  if (rotate < 0)
    rotate += 4;

  CPDF_Array* pMediaBox = ToArray(GetPageAttr("MediaBox"));
  CFX_FloatRect mediabox;
  if (pMediaBox) {
    mediabox = pMediaBox->GetRect();
    mediabox.Normalize();
  }
  if (mediabox.IsEmpty())
    mediabox = CFX_FloatRect(0, 0, 612, 792);

  CPDF_Array* pCropBox = ToArray(GetPageAttr("CropBox"));
  if (pCropBox) {
    m_BBox = pCropBox->GetRect();
    m_BBox.Normalize();
  }
  if (m_BBox.IsEmpty())
    m_BBox = mediabox;
  else
    m_BBox.Intersect(mediabox);

  m_PageWidth = m_BBox.right - m_BBox.left;
  m_PageHeight = m_BBox.top - m_BBox.bottom;
  if (rotate % 2)
    std::swap(m_PageWidth, m_PageHeight);

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