// The text that should be displayed for this counter.
void
nsCounterUseNode::GetText(nsString& aResult)
{
  aResult.Truncate();

  AutoTArray<nsCounterNode*, 8> stack;
  stack.AppendElement(static_cast<nsCounterNode*>(this));

  if (mAllCounters && mScopeStart) {
    for (nsCounterNode* n = mScopeStart; n->mScopePrev; n = n->mScopeStart) {
      stack.AppendElement(n->mScopePrev);
    }
  }

  WritingMode wm = mPseudoFrame ?
    mPseudoFrame->GetWritingMode() : WritingMode();
  for (uint32_t i = stack.Length() - 1;; --i) {
    nsCounterNode* n = stack[i];
    nsAutoString text;
    bool isTextRTL;
    mCounterStyle->GetCounterText(n->mValueAfter, wm, text, isTextRTL);
    aResult.Append(text);
    if (i == 0) {
      break;
    }
    aResult.Append(mSeparator);
  }
}