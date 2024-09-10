DLLEXPORT void STDCALL FPDFPage_InsertClipPath(FPDF_PAGE page,
                                               FPDF_CLIPPATH clipPath) {
  CPDF_Page* pPage = CPDFPageFromFPDFPage(page);
  if (!pPage)
    return;

  CPDF_Dictionary* pPageDic = pPage->m_pFormDict;
  CPDF_Object* pContentObj =
      pPageDic ? pPageDic->GetObjectFor("Contents") : nullptr;
  if (!pContentObj)
    pContentObj = pPageDic ? pPageDic->GetArrayFor("Contents") : nullptr;
  if (!pContentObj)
    return;

  CFX_ByteTextBuf strClip;
  CPDF_ClipPath* pClipPath = (CPDF_ClipPath*)clipPath;
  uint32_t i;
  for (i = 0; i < pClipPath->GetPathCount(); i++) {
    CPDF_Path path = pClipPath->GetPath(i);
    int iClipType = pClipPath->GetClipType(i);
    if (path.GetPoints().empty()) {
      // Empty clipping (totally clipped out)
      strClip << "0 0 m W n ";
    } else {
      OutputPath(strClip, path);
      if (iClipType == FXFILL_WINDING)
        strClip << "W n\n";
      else
        strClip << "W* n\n";
    }
  }
  CPDF_Document* pDoc = pPage->m_pDocument;
  if (!pDoc)
    return;

  CPDF_Stream* pStream = pDoc->NewIndirect<CPDF_Stream>(
      nullptr, 0,
      pdfium::MakeUnique<CPDF_Dictionary>(pDoc->GetByteStringPool()));
  pStream->SetData(strClip.GetBuffer(), strClip.GetSize());

  CPDF_Array* pArray = ToArray(pContentObj);
  if (pArray) {
    pArray->InsertNewAt<CPDF_Reference>(0, pDoc, pStream->GetObjNum());
    return;
  }
  CPDF_Reference* pReference = ToReference(pContentObj);
  if (!pReference)
    return;

  CPDF_Object* pDirectObj = pReference->GetDirect();
  if (!pDirectObj)
    return;

  CPDF_Array* pObjArray = pDirectObj->AsArray();
  if (pObjArray) {
    pObjArray->InsertNewAt<CPDF_Reference>(0, pDoc, pStream->GetObjNum());
    return;
  }
  if (pDirectObj->IsStream()) {
    CPDF_Array* pContentArray = pDoc->NewIndirect<CPDF_Array>();
    pContentArray->AddNew<CPDF_Reference>(pDoc, pStream->GetObjNum());
    pContentArray->AddNew<CPDF_Reference>(pDoc, pDirectObj->GetObjNum());
    pPageDic->SetNewFor<CPDF_Reference>("Contents", pDoc,
                                        pContentArray->GetObjNum());
  }
}