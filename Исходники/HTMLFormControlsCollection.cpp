nsresult
HTMLFormControlsCollection::GetSortedControls(
  nsTArray<nsGenericHTMLFormElement*>& aControls) const
{
#ifdef DEBUG
  HTMLFormElement::AssertDocumentOrder(mElements, mForm);
  HTMLFormElement::AssertDocumentOrder(mNotInElements, mForm);
#endif

  aControls.Clear();

  // Merge the elements list and the not in elements list. Both lists are
  // already sorted.
  uint32_t elementsLen = mElements.Length();
  uint32_t notInElementsLen = mNotInElements.Length();
  aControls.SetCapacity(elementsLen + notInElementsLen);

  uint32_t elementsIdx = 0;
  uint32_t notInElementsIdx = 0;

  while (elementsIdx < elementsLen || notInElementsIdx < notInElementsLen) {
    // Check whether we're done with mElements
    if (elementsIdx == elementsLen) {
      NS_ASSERTION(notInElementsIdx < notInElementsLen,
                   "Should have remaining not-in-elements");
      // Append the remaining mNotInElements elements
      if (!aControls.AppendElements(mNotInElements.Elements() +
                                      notInElementsIdx,
                                    notInElementsLen -
                                      notInElementsIdx)) {
        return NS_ERROR_OUT_OF_MEMORY;
      }
      break;
    }
    // Check whether we're done with mNotInElements
    if (notInElementsIdx == notInElementsLen) {
      NS_ASSERTION(elementsIdx < elementsLen,
                   "Should have remaining in-elements");
      // Append the remaining mElements elements
      if (!aControls.AppendElements(mElements.Elements() +
                                      elementsIdx,
                                    elementsLen -
                                      elementsIdx)) {
        return NS_ERROR_OUT_OF_MEMORY;
      }
      break;
    }
    // Both lists have elements left.
    NS_ASSERTION(mElements[elementsIdx] &&
                 mNotInElements[notInElementsIdx],
                 "Should have remaining elements");
    // Determine which of the two elements should be ordered
    // first and add it to the end of the list.
    nsGenericHTMLFormElement* elementToAdd;
    if (HTMLFormElement::CompareFormControlPosition(
          mElements[elementsIdx], mNotInElements[notInElementsIdx], mForm) < 0) {
      elementToAdd = mElements[elementsIdx];
      ++elementsIdx;
    } else {
      elementToAdd = mNotInElements[notInElementsIdx];
      ++notInElementsIdx;
    }
    // Add the first element to the list.
    if (!aControls.AppendElement(elementToAdd)) {
      return NS_ERROR_OUT_OF_MEMORY;
    }
  }

  NS_ASSERTION(aControls.Length() == elementsLen + notInElementsLen,
               "Not all form controls were added to the sorted list");
#ifdef DEBUG
  HTMLFormElement::AssertDocumentOrder(aControls, mForm);
#endif

  return NS_OK;
}