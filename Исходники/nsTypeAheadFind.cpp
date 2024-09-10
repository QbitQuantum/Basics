NS_IMETHODIMP
nsTypeAheadFind::Find(const nsAString& aSearchString, bool aLinksOnly,
                      uint16_t* aResult)
{
  *aResult = FIND_NOTFOUND;

  nsCOMPtr<nsIPresShell> presShell (GetPresShell());
  if (!presShell) {
    nsCOMPtr<nsIDocShell> ds (do_QueryReferent(mDocShell));
    NS_ENSURE_TRUE(ds, NS_ERROR_FAILURE);

    presShell = ds->GetPresShell();
    NS_ENSURE_TRUE(presShell, NS_ERROR_FAILURE);
    mPresShell = do_GetWeakReference(presShell);
  }

  nsCOMPtr<nsISelection> selection;
  nsCOMPtr<nsISelectionController> selectionController =
    do_QueryReferent(mSelectionController);
  if (!selectionController) {
    GetSelection(presShell, getter_AddRefs(selectionController),
                 getter_AddRefs(selection)); // cache for reuse
    mSelectionController = do_GetWeakReference(selectionController);
  } else {
    selectionController->GetSelection(
      nsISelectionController::SELECTION_NORMAL, getter_AddRefs(selection));
  }

  if (selection)
    selection->CollapseToStart();

  if (aSearchString.IsEmpty()) {
    mTypeAheadBuffer.Truncate();

    // These will be initialized to their true values after the first character
    // is typed
    mStartFindRange = nullptr;
    mSelectionController = nullptr;

    *aResult = FIND_FOUND;
    return NS_OK;
  }

  bool atEnd = false;    
  if (mTypeAheadBuffer.Length()) {
    const nsAString& oldStr = Substring(mTypeAheadBuffer, 0, mTypeAheadBuffer.Length());
    const nsAString& newStr = Substring(aSearchString, 0, mTypeAheadBuffer.Length());
    if (oldStr.Equals(newStr))
      atEnd = true;
  
    const nsAString& newStr2 = Substring(aSearchString, 0, aSearchString.Length());
    const nsAString& oldStr2 = Substring(mTypeAheadBuffer, 0, aSearchString.Length());
    if (oldStr2.Equals(newStr2))
      atEnd = true;
    
    if (!atEnd)
      mStartFindRange = nullptr;
  }

  if (!mIsSoundInitialized && !mNotFoundSoundURL.IsEmpty()) {
    // This makes sure system sound library is loaded so that
    // there's no lag before the first sound is played
    // by waiting for the first keystroke, we still get the startup time benefits.
    mIsSoundInitialized = true;
    mSoundInterface = do_CreateInstance("@mozilla.org/sound;1");
    if (mSoundInterface && !mNotFoundSoundURL.EqualsLiteral("beep")) {
      mSoundInterface->Init();
    }
  }

#ifdef XP_WIN
  // After each keystroke, ensure sound object is destroyed, to free up memory 
  // allocated for error sound, otherwise Windows' nsISound impl 
  // holds onto the last played sound, using up memory.
  mSoundInterface = nullptr;
#endif

  int32_t bufferLength = mTypeAheadBuffer.Length();

  mTypeAheadBuffer = aSearchString;

  bool isFirstVisiblePreferred = false;

  // --------- Initialize find if 1st char ----------
  if (bufferLength == 0) {
    // If you can see the selection (not collapsed or thru caret browsing),
    // or if already focused on a page element, start there.
    // Otherwise we're going to start at the first visible element
    bool isSelectionCollapsed = true;
    if (selection)
      selection->GetIsCollapsed(&isSelectionCollapsed);

    // If true, we will scan from top left of visible area
    // If false, we will scan from start of selection
    isFirstVisiblePreferred = !atEnd && !mCaretBrowsingOn && isSelectionCollapsed;
    if (isFirstVisiblePreferred) {
      // Get the focused content. If there is a focused node, ensure the
      // selection is at that point. Otherwise, we will just want to start
      // from the caret position or the beginning of the document.
      nsPresContext* presContext = presShell->GetPresContext();
      NS_ENSURE_TRUE(presContext, NS_OK);

      nsCOMPtr<nsIDocument> document =
        do_QueryInterface(presShell->GetDocument());
      if (!document)
        return NS_ERROR_UNEXPECTED;

      nsCOMPtr<nsIFocusManager> fm = do_GetService(FOCUSMANAGER_CONTRACTID);
      if (fm) {
        nsPIDOMWindowOuter* window = document->GetWindow();
        nsCOMPtr<nsIDOMElement> focusedElement;
        nsCOMPtr<mozIDOMWindowProxy> focusedWindow;
        fm->GetFocusedElementForWindow(window, false,
                                       getter_AddRefs(focusedWindow),
                                       getter_AddRefs(focusedElement));
        // If the root element is focused, then it's actually the document
        // that has the focus, so ignore this.
        if (focusedElement &&
            !SameCOMIdentity(focusedElement, document->GetRootElement())) {
          fm->MoveCaretToFocus(window);
          isFirstVisiblePreferred = false;
        }
      }
    }
  }

  // ----------- Find the text! ---------------------
  // Beware! This may flush notifications via synchronous
  // ScrollSelectionIntoView.
  nsresult rv = FindItNow(nullptr, aLinksOnly, isFirstVisiblePreferred,
                          false, aResult);

  // ---------Handle success or failure ---------------
  if (NS_SUCCEEDED(rv)) {
    if (mTypeAheadBuffer.Length() == 1) {
      // If first letter, store where the first find succeeded
      // (mStartFindRange)

      mStartFindRange = nullptr;
      if (selection) {
        nsCOMPtr<nsIDOMRange> startFindRange;
        selection->GetRangeAt(0, getter_AddRefs(startFindRange));
        if (startFindRange)
          startFindRange->CloneRange(getter_AddRefs(mStartFindRange));
      }
    }
  }
  else {
    // Error sound
    if (mTypeAheadBuffer.Length() > mLastFindLength)
      PlayNotFoundSound();
  }

  SaveFind();
  return NS_OK;
}