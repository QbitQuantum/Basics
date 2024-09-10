void
HTMLTextAreaElement::SetRangeText(const nsAString& aReplacement,
                                  uint32_t aStart, uint32_t aEnd,
                                  const SelectionMode& aSelectMode,
                                  ErrorResult& aRv, int32_t aSelectionStart,
                                  int32_t aSelectionEnd)
{
  if (aStart > aEnd) {
    aRv.Throw(NS_ERROR_DOM_INDEX_SIZE_ERR);
    return;
  }

  nsAutoString value;
  GetValueInternal(value, false);
  uint32_t inputValueLength = value.Length();

  if (aStart > inputValueLength) {
    aStart = inputValueLength;
  }

  if (aEnd > inputValueLength) {
    aEnd = inputValueLength;
  }

  if (aSelectionStart == -1 && aSelectionEnd == -1) {
    aRv = GetSelectionRange(&aSelectionStart, &aSelectionEnd);
    if (aRv.Failed()) {
      if (mState.IsSelectionCached()) {
        aSelectionStart = mState.GetSelectionProperties().GetStart();
        aSelectionEnd = mState.GetSelectionProperties().GetEnd();
        aRv = NS_OK;
      }
    }
  }

  if (aStart <= aEnd) {
    value.Replace(aStart, aEnd - aStart, aReplacement);
    nsresult rv =
      SetValueInternal(value, nsTextEditorState::eSetValue_ByContent);
    if (NS_FAILED(rv)) {
      aRv.Throw(rv);
      return;
    }
  }

  uint32_t newEnd = aStart + aReplacement.Length();
  int32_t delta =  aReplacement.Length() - (aEnd - aStart);

  switch (aSelectMode) {
    case mozilla::dom::SelectionMode::Select:
    {
      aSelectionStart = aStart;
      aSelectionEnd = newEnd;
    }
    break;
    case mozilla::dom::SelectionMode::Start:
    {
      aSelectionStart = aSelectionEnd = aStart;
    }
    break;
    case mozilla::dom::SelectionMode::End:
    {
      aSelectionStart = aSelectionEnd = newEnd;
    }
    break;
    case mozilla::dom::SelectionMode::Preserve:
    {
      if ((uint32_t)aSelectionStart > aEnd) {
        aSelectionStart += delta;
      } else if ((uint32_t)aSelectionStart > aStart) {
        aSelectionStart = aStart;
      }

      if ((uint32_t)aSelectionEnd > aEnd) {
        aSelectionEnd += delta;
      } else if ((uint32_t)aSelectionEnd > aStart) {
        aSelectionEnd = newEnd;
      }
    }
    break;
    default:
      MOZ_CRASH("Unknown mode!");
  }

  Optional<nsAString> direction;
  SetSelectionRange(aSelectionStart, aSelectionEnd, direction, aRv);
}