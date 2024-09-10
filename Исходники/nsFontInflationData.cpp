static nscoord
ComputeDescendantWidth(const nsHTMLReflowState& aAncestorReflowState,
                       nsIFrame *aDescendantFrame)
{
  nsIFrame *ancestorFrame = aAncestorReflowState.frame->FirstInFlow();
  if (aDescendantFrame == ancestorFrame) {
    return aAncestorReflowState.ComputedWidth();
  }

  AutoInfallibleTArray<nsIFrame*, 16> frames;
  for (nsIFrame *f = aDescendantFrame; f != ancestorFrame;
       f = f->GetParent()->FirstInFlow()) {
    frames.AppendElement(f);
  }

  // This ignores the width contributions made by scrollbars, though in
  // reality we don't have any scrollbars on the sorts of devices on
  // which we use font inflation, so it's not a problem.  But it may
  // occasionally cause problems when writing tests on desktop.

  uint32_t len = frames.Length();
  nsHTMLReflowState *reflowStates = static_cast<nsHTMLReflowState*>
                                (moz_xmalloc(sizeof(nsHTMLReflowState) * len));
  nsPresContext *presContext = aDescendantFrame->PresContext();
  for (uint32_t i = 0; i < len; ++i) {
    const nsHTMLReflowState &parentReflowState =
      (i == 0) ? aAncestorReflowState : reflowStates[i - 1];
    nsIFrame *frame = frames[len - i - 1];
    WritingMode wm = frame->GetWritingMode();
    LogicalSize availSize = parentReflowState.ComputedSize(wm);
    availSize.BSize(wm) = NS_UNCONSTRAINEDSIZE;
    MOZ_ASSERT(frame->GetParent()->FirstInFlow() ==
                 parentReflowState.frame->FirstInFlow(),
               "bad logic in this function");
    new (reflowStates + i) nsHTMLReflowState(presContext, parentReflowState,
                                             frame, availSize);
  }

  MOZ_ASSERT(reflowStates[len - 1].frame == aDescendantFrame,
             "bad logic in this function");
  nscoord result = reflowStates[len - 1].ComputedWidth();

  for (uint32_t i = len; i-- != 0; ) {
    reflowStates[i].~nsHTMLReflowState();
  }
  moz_free(reflowStates);

  return result;
}