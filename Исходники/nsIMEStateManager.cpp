nsresult
nsIMEStateManager::OnRemoveContent(nsPresContext* aPresContext,
                                   nsIContent* aContent)
{
  NS_ENSURE_ARG_POINTER(aPresContext);

  // First, if there is a composition in the aContent, clean up it.
  if (sTextCompositions) {
    TextComposition* compositionInContent =
      sTextCompositions->GetCompositionInContent(aPresContext, aContent);

    if (compositionInContent) {
      // Store the composition before accessing the native IME.
      TextComposition storedComposition = *compositionInContent;
      // Try resetting the native IME state.  Be aware, typically, this method
      // is called during the content being removed.  Then, the native
      // composition events which are caused by following APIs are ignored due
      // to unsafe to run script (in PresShell::HandleEvent()).
      nsCOMPtr<nsIWidget> widget = aPresContext->GetNearestWidget();
      if (widget) {
        nsresult rv =
          storedComposition.NotifyIME(REQUEST_TO_CANCEL_COMPOSITION);
        if (NS_FAILED(rv)) {
          storedComposition.NotifyIME(REQUEST_TO_COMMIT_COMPOSITION);
        }
        // By calling the APIs, the composition may have been finished normally.
        compositionInContent =
          sTextCompositions->GetCompositionFor(
                               storedComposition.GetPresContext(),
                               storedComposition.GetEventTargetNode());
      }
    }

    // If the compositionInContent is still available, we should finish the
    // composition just on the content forcibly.
    if (compositionInContent) {
      compositionInContent->SynthesizeCommit(true);
    }
  }

  if (!sPresContext || !sContent ||
      !nsContentUtils::ContentIsDescendantOf(sContent, aContent)) {
    return NS_OK;
  }

  // Current IME transaction should commit
  nsCOMPtr<nsIWidget> widget = sPresContext->GetNearestWidget();
  if (widget) {
    IMEState newState = GetNewIMEState(sPresContext, nullptr);
    InputContextAction action(InputContextAction::CAUSE_UNKNOWN,
                              InputContextAction::LOST_FOCUS);
    SetIMEState(newState, nullptr, widget, action);
  }

  NS_IF_RELEASE(sContent);
  sPresContext = nullptr;

  return NS_OK;
}