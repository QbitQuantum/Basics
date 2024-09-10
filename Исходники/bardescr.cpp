// -----------------------------------------------------------------------------
/// Merges this gadgets and sourceBarDescr gadgets and inserts them into
/// destWindow's gadgets.
bool
TBarDescr::Merge(const TBarDescr& srcBarDescr, TGadgetWindow& destWindow)
{
  if (BarRes && BarRes->IsOK()){

    RemoveGadgets(destWindow);

    if(!srcBarDescr.Gadgets->Size())
      CreateGadgets(srcBarDescr.Gadgets, *((TBarDescr&)srcBarDescr).GetBuilder(), 
                    srcBarDescr.BarRes);

    TCelArray& cellArray = destWindow.GetCelArray();

    cellArray.RemoveAll();

    int gdIndex1 = 0;
    int gdIndex2 = 0;
    int cellIndex = 0;
    int cellIndex1 = 0;
    int cellIndex2 = 0;

    for (int g = 0; g < NumGroups; g++){
      if (srcBarDescr.GroupCount[g] > 0){
         for (int i=0; i < srcBarDescr.GroupCount[g]; i++){
          __TBarDescrGdNode* node = (*srcBarDescr.Gadgets)[gdIndex1];
          destWindow.Insert(*node->Gadget);
          if(node->UseGlyph){
            cellArray.Add(*srcBarDescr.CelArray, cellIndex1);
            TButtonGadget* bg = TYPESAFE_DOWNCAST(node->Gadget, TButtonGadget);
            if(bg)
              bg->SetGlyphIndex(cellIndex);
            cellIndex++;
            cellIndex1++;
          }
          gdIndex1++;
        }
      }
      else if (srcBarDescr.GroupCount[g] == 0 && GroupCount[g] > 0) {
         for (int i=0; i < GroupCount[g]; i++){
          __TBarDescrGdNode* node = (*Gadgets)[gdIndex2];
          destWindow.Insert(*node->Gadget);
          if(node->UseGlyph){
            cellArray.Add(*CelArray, cellIndex2);
            TButtonGadget* bg = TYPESAFE_DOWNCAST(node->Gadget, TButtonGadget);
            if(bg)
              bg->SetGlyphIndex(cellIndex);
            cellIndex++;
            cellIndex2++;
          }
          gdIndex2++;
        }
      }
    }
    destWindow.Invalidate();
    destWindow.LayoutSession();
    destWindow.UpdateWindow();
    return true;
  }
  return false;
}