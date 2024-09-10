DLLEXPORT void STDCALL FPDFPage_TransformAnnots(FPDF_PAGE page,
                                                double a,
                                                double b,
                                                double c,
                                                double d,
                                                double e,
                                                double f) {
  CPDF_Page* pPage = CPDFPageFromFPDFPage(page);
  if (!pPage)
    return;

  CPDF_AnnotList AnnotList(pPage);
  for (size_t i = 0; i < AnnotList.Count(); ++i) {
    CPDF_Annot* pAnnot = AnnotList.GetAt(i);
    // transformAnnots Rectangle
    CFX_FloatRect rect = pAnnot->GetRect();
    CFX_Matrix matrix((FX_FLOAT)a, (FX_FLOAT)b, (FX_FLOAT)c, (FX_FLOAT)d,
                      (FX_FLOAT)e, (FX_FLOAT)f);
    rect.Transform(&matrix);
    CPDF_Array* pRectArray = pAnnot->GetAnnotDict()->GetArrayBy("Rect");
    if (!pRectArray)
      pRectArray = new CPDF_Array;
    pRectArray->SetAt(0, new CPDF_Number(rect.left));
    pRectArray->SetAt(1, new CPDF_Number(rect.bottom));
    pRectArray->SetAt(2, new CPDF_Number(rect.right));
    pRectArray->SetAt(3, new CPDF_Number(rect.top));
    pAnnot->GetAnnotDict()->SetAt("Rect", pRectArray);

    // Transform AP's rectangle
    // To Do
  }
}