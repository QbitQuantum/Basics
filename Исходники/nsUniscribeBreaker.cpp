void
NS_GetComplexLineBreaks(const char16_t* aText, uint32_t aLength,
                        uint8_t* aBreakBefore)
{
  NS_ASSERTION(aText, "aText shouldn't be null"); 

  int outItems = 0;
  HRESULT result;
  AutoTArray<SCRIPT_ITEM, 64> items;
  char16ptr_t text = aText;

  memset(aBreakBefore, false, aLength);

  if (!items.AppendElements(64))
    return;

  do {
    result = ScriptItemize(text, aLength, items.Length(), nullptr, nullptr,
                           items.Elements(), &outItems);

    if (result == E_OUTOFMEMORY) {
      if (!items.AppendElements(items.Length()))
        return;
    }
  } while (result == E_OUTOFMEMORY);

  for (int iItem = 0; iItem < outItems; ++iItem)  {
    uint32_t endOffset = (iItem + 1 == outItems ? aLength : items[iItem + 1].iCharPos);
    uint32_t startOffset = items[iItem].iCharPos;
    AutoTArray<SCRIPT_LOGATTR, 64> sla;
    
    if (!sla.AppendElements(endOffset - startOffset))
      return;

    if (ScriptBreak(text + startOffset, endOffset - startOffset,
                    &items[iItem].a,  sla.Elements()) < 0) 
      return;

    for (uint32_t j=0; j+startOffset < endOffset; ++j) {
       aBreakBefore[j+startOffset] = sla[j].fSoftBreak;
    }
  }
}