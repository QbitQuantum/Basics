nsresult
nsTextAttrsMgr::GetRange(const nsTArray<nsITextAttr*>& aTextAttrArray,
                         PRInt32 *aStartHTOffset, PRInt32 *aEndHTOffset)
{
  PRUint32 attrLen = aTextAttrArray.Length();

  // Navigate backward from anchor accessible to find start offset.
  for (PRInt32 childIdx = mOffsetAccIdx - 1; childIdx >= 0; childIdx--) {
    nsAccessible *currAcc = mHyperTextAcc->GetChildAt(childIdx);

    // Stop on embedded accessible since embedded accessibles are combined into
    // own range.
    if (nsAccUtils::IsEmbeddedObject(currAcc))
      break;

    nsIContent *currElm = nsCoreUtils::GetDOMElementFor(currAcc->GetContent());
    NS_ENSURE_STATE(currElm);

    bool offsetFound = false;
    for (PRUint32 attrIdx = 0; attrIdx < attrLen; attrIdx++) {
      nsITextAttr *textAttr = aTextAttrArray[attrIdx];
      if (!textAttr->Equal(currElm)) {
        offsetFound = true;
        break;
      }
    }

    if (offsetFound)
      break;

    *(aStartHTOffset) -= nsAccUtils::TextLength(currAcc);
  }

  // Navigate forward from anchor accessible to find end offset.
  PRInt32 childLen = mHyperTextAcc->GetChildCount();
  for (PRInt32 childIdx = mOffsetAccIdx + 1; childIdx < childLen; childIdx++) {
    nsAccessible *currAcc = mHyperTextAcc->GetChildAt(childIdx);
    if (nsAccUtils::IsEmbeddedObject(currAcc))
      break;

    nsIContent *currElm = nsCoreUtils::GetDOMElementFor(currAcc->GetContent());
    NS_ENSURE_STATE(currElm);

    bool offsetFound = false;
    for (PRUint32 attrIdx = 0; attrIdx < attrLen; attrIdx++) {
      nsITextAttr *textAttr = aTextAttrArray[attrIdx];

      // Alter the end offset when text attribute changes its value and stop
      // the search.
      if (!textAttr->Equal(currElm)) {
        offsetFound = true;
        break;
      }
    }

    if (offsetFound)
      break;

    (*aEndHTOffset) += nsAccUtils::TextLength(currAcc);
  }

  return NS_OK;
}