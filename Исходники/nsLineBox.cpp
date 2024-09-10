NS_IMETHODIMP
nsLineIterator::GetLine(PRInt32 aLineNumber,
                        nsIFrame** aFirstFrameOnLine,
                        PRInt32* aNumFramesOnLine,
                        nsRect& aLineBounds,
                        PRUint32* aLineFlags)
{
  NS_ENSURE_ARG_POINTER(aFirstFrameOnLine);
  NS_ENSURE_ARG_POINTER(aNumFramesOnLine);
  NS_ENSURE_ARG_POINTER(aLineFlags);

  if ((aLineNumber < 0) || (aLineNumber >= mNumLines)) {
    *aFirstFrameOnLine = nsnull;
    *aNumFramesOnLine = 0;
    aLineBounds.SetRect(0, 0, 0, 0);
    return NS_OK;
  }
  nsLineBox* line = mLines[aLineNumber];
  *aFirstFrameOnLine = line->mFirstChild;
  *aNumFramesOnLine = line->GetChildCount();
  aLineBounds = line->mBounds;

  PRUint32 flags = 0;
  if (line->IsBlock()) {
    flags |= NS_LINE_FLAG_IS_BLOCK;
  }
  else {
    if (line->HasBreakAfter())
      flags |= NS_LINE_FLAG_ENDS_IN_BREAK;
  }
  *aLineFlags = flags;

  return NS_OK;
}