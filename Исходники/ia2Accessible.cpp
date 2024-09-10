STDMETHODIMP
ia2Accessible::get_selectionRanges(IA2Range** aRanges,
                                   long *aNRanges)
{
  if (!aRanges || !aNRanges)
    return E_INVALIDARG;

  *aNRanges = 0;

  AccessibleWrap* acc = static_cast<AccessibleWrap*>(this);
  if (acc->IsDefunct())
    return CO_E_OBJNOTCONNECTED;

  AutoTArray<TextRange, 1> ranges;
  acc->Document()->SelectionRanges(&ranges);
  uint32_t len = ranges.Length();
  for (uint32_t idx = 0; idx < len; idx++) {
    if (!ranges[idx].Crop(acc)) {
      ranges.RemoveElementAt(idx);
    }
  }

  *aNRanges = ranges.Length();
  *aRanges = static_cast<IA2Range*>(
    ::CoTaskMemAlloc(sizeof(IA2Range) * *aNRanges));
  if (!*aRanges)
    return E_OUTOFMEMORY;

  for (uint32_t idx = 0; idx < static_cast<uint32_t>(*aNRanges); idx++) {
    AccessibleWrap* anchor =
      static_cast<AccessibleWrap*>(ranges[idx].StartContainer());
    (*aRanges)[idx].anchor = static_cast<IAccessible2*>(anchor);
    anchor->AddRef();

    (*aRanges)[idx].anchorOffset = ranges[idx].StartOffset();

    AccessibleWrap* active =
      static_cast<AccessibleWrap*>(ranges[idx].EndContainer());
    (*aRanges)[idx].active = static_cast<IAccessible2*>(active);
    active->AddRef();

    (*aRanges)[idx].activeOffset = ranges[idx].EndOffset();
  }

  return S_OK;
}