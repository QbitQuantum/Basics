void CPWL_Edit::GeneratePageObjects(CPDF_PageObjects* pPageObjects,
                                    const CPDF_Point& ptOffset) {
  CFX_ArrayTemplate<CPDF_TextObject*> ObjArray;
  IFX_Edit::GeneratePageObjects(
      pPageObjects, m_pEdit, ptOffset, NULL,
      CPWL_Utils::PWLColorToFXColor(GetTextColor(), GetTransparency()),
      ObjArray);
}