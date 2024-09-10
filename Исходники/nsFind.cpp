//
// Find:
// Take nodes out of the tree with NextNode,
// until null (NextNode will return 0 at the end of our range).
//
NS_IMETHODIMP
nsFind::Find(const PRUnichar *aPatText, nsIDOMRange* aSearchRange,
             nsIDOMRange* aStartPoint, nsIDOMRange* aEndPoint,
             nsIDOMRange** aRangeRet)
{
#ifdef DEBUG_FIND
  printf("============== nsFind::Find('%s'%s, %p, %p, %p)\n",
         NS_LossyConvertUTF16toASCII(aPatText).get(),
         mFindBackward ? " (backward)" : " (forward)",
         (void*)aSearchRange, (void*)aStartPoint, (void*)aEndPoint);
#endif

  NS_ENSURE_ARG(aSearchRange);
  NS_ENSURE_ARG(aStartPoint);
  NS_ENSURE_ARG(aEndPoint);
  NS_ENSURE_ARG_POINTER(aRangeRet);
  *aRangeRet = 0;

  if (!aPatText)
    return NS_ERROR_NULL_POINTER;

  ResetAll();

  nsAutoString patAutoStr(aPatText);
  if (!mCaseSensitive)
    ToLowerCase(patAutoStr);

  // Ignore soft hyphens in the pattern  
  static const char kShy[] = { CH_SHY, 0 };
  patAutoStr.StripChars(kShy);

  const PRUnichar* patStr = patAutoStr.get();
  PRInt32 patLen = patAutoStr.Length() - 1;

  // current offset into the pattern -- reset to beginning/end:
  PRInt32 pindex = (mFindBackward ? patLen : 0);

  // Current offset into the fragment
  PRInt32 findex = 0;

  // Direction to move pindex and ptr*
  int incr = (mFindBackward ? -1 : 1);

  nsCOMPtr<nsIContent> tc;
  const nsTextFragment *frag = nsnull;
  PRInt32 fragLen = 0;

  // Pointers into the current fragment:
  const PRUnichar *t2b = nsnull;
  const char      *t1b = nsnull;

  // Keep track of when we're in whitespace:
  // (only matters when we're matching)
  PRBool inWhitespace = PR_FALSE;

  // Have we extended a search past the endpoint?
  PRBool continuing = PR_FALSE;

  // Place to save the range start point in case we find a match:
  nsCOMPtr<nsIDOMNode> matchAnchorNode;
  PRInt32 matchAnchorOffset = 0;

  // Get the end point, so we know when to end searches:
  nsCOMPtr<nsIDOMNode> endNode;
  PRInt32 endOffset;
  aEndPoint->GetEndContainer(getter_AddRefs(endNode));
  aEndPoint->GetEndOffset(&endOffset);

  PRUnichar prevChar = 0;
  while (1)
  {
#ifdef DEBUG_FIND
    printf("Loop ...\n");
#endif

    // If this is our first time on a new node, reset the pointers:
    if (!frag)
    {

      tc = nsnull;
      NextNode(aSearchRange, aStartPoint, aEndPoint, PR_FALSE);
      if (!mIterNode)    // Out of nodes
      {
        // Are we in the middle of a match?
        // If so, try again with continuation.
        if (matchAnchorNode && !continuing)
          NextNode(aSearchRange, aStartPoint, aEndPoint, PR_TRUE);

        // Reset the iterator, so this nsFind will be usable if
        // the user wants to search again (from beginning/end).
        ResetAll();
        return NS_OK;
      }

      // We have a new text content.  If its block parent is different
      // from the block parent of the last text content, then we
      // need to clear the match since we don't want to find
      // across block boundaries.
      nsCOMPtr<nsIDOMNode> blockParent;
      GetBlockParent(mIterNode, getter_AddRefs(blockParent));
#ifdef DEBUG_FIND
      printf("New node: old blockparent = %p, new = %p\n",
             (void*)mLastBlockParent.get(), (void*)blockParent.get());
#endif
      if (blockParent != mLastBlockParent)
      {
#ifdef DEBUG_FIND
        printf("Different block parent!\n");
#endif
        mLastBlockParent = blockParent;
        // End any pending match:
        matchAnchorNode = nsnull;
        matchAnchorOffset = 0;
        pindex = (mFindBackward ? patLen : 0);
        inWhitespace = PR_FALSE;
      }
 
      // Get the text content:
      tc = do_QueryInterface(mIterNode);
      if (!tc || !(frag = tc->GetText())) // Out of nodes
      {
        mIterator = nsnull;
        mLastBlockParent = 0;
        ResetAll();
        return NS_OK;
      }

      fragLen = frag->GetLength();

      // Set our starting point in this node.
      // If we're going back to the anchor node, which means that we
      // just ended a partial match, use the saved offset:
      if (mIterNode == matchAnchorNode)
        findex = matchAnchorOffset + (mFindBackward ? 1 : 0);

      // mIterOffset, if set, is the range's idea of an offset,
      // and points between characters.  But when translated
      // to a string index, it points to a character.  If we're
      // going backward, this is one character too late and
      // we'll match part of our previous pattern.
      else if (mIterOffset >= 0)
        findex = mIterOffset - (mFindBackward ? 1 : 0);

      // Otherwise, just start at the appropriate end of the fragment:
      else if (mFindBackward)
        findex = fragLen - 1;
      else
        findex = 0;

      // Offset can only apply to the first node:
      mIterOffset = -1;

      // If this is outside the bounds of the string, then skip this node:
      if (findex < 0 || findex > fragLen-1)
      {
#ifdef DEBUG_FIND
        printf("At the end of a text node -- skipping to the next\n");
#endif
        frag = 0;
        continue;
      }

#ifdef DEBUG_FIND
      printf("Starting from offset %d\n", findex);
#endif
      if (frag->Is2b())
      {
        t2b = frag->Get2b();
        t1b = nsnull;
#ifdef DEBUG_FIND
        nsAutoString str2(t2b, fragLen);
        printf("2 byte, '%s'\n", NS_LossyConvertUTF16toASCII(str2).get());
#endif
      }
      else
      {
        t1b = frag->Get1b();
        t2b = nsnull;
#ifdef DEBUG_FIND
        nsCAutoString str1(t1b, fragLen);
        printf("1 byte, '%s'\n", str1.get());
#endif
      }
    }
    else // still on the old node
    {
      // Still on the old node.  Advance the pointers,
      // then see if we need to pull a new node.
      findex += incr;
#ifdef DEBUG_FIND
      printf("Same node -- (%d, %d)\n", pindex, findex);
#endif
      if (mFindBackward ? (findex < 0) : (findex >= fragLen))
      {
#ifdef DEBUG_FIND
        printf("Will need to pull a new node: mAO = %d, frag len=%d\n",
               matchAnchorOffset, fragLen);
#endif
        // Done with this node.  Pull a new one.
        frag = nsnull;
        continue;
      }
    }

    // Have we gone past the endpoint yet?
    // If we have, and we're not in the middle of a match, return.
    if (mIterNode == endNode && !continuing &&
        ((mFindBackward && (findex < endOffset)) ||
         (!mFindBackward && (findex > endOffset))))
    {
      ResetAll();
      return NS_OK;
    }

    // The two characters we'll be comparing:
    PRUnichar c = (t2b ? t2b[findex] : CHAR_TO_UNICHAR(t1b[findex]));
    PRUnichar patc = patStr[pindex];

#ifdef DEBUG_FIND
    printf("Comparing '%c'=%x to '%c' (%d of %d), findex=%d%s\n",
           (char)c, (int)c, patc, pindex, patLen, findex,
           inWhitespace ? " (inWhitespace)" : "");
#endif

    // Do we need to go back to non-whitespace mode?
    // If inWhitespace, then this space in the pat str
    // has already matched at least one space in the document.
    if (inWhitespace && !IsSpace(c))
    {
      inWhitespace = PR_FALSE;
      pindex += incr;
#ifdef DEBUG
      // This shouldn't happen -- if we were still matching, and we
      // were at the end of the pat string, then we should have
      // caught it in the last iteration and returned success.
      if (OVERFLOW_PINDEX)
        NS_ASSERTION(PR_FALSE, "Missed a whitespace match\n");
#endif
      patc = patStr[pindex];
    }
    if (!inWhitespace && IsSpace(patc))
      inWhitespace = PR_TRUE;

    // convert to lower case if necessary
    else if (!inWhitespace && !mCaseSensitive && IsUpperCase(c))
      c = ToLowerCase(c);

    // ignore soft hyphens in the document
    if (c == CH_SHY)
      continue;

    // a '\n' between CJ characters is ignored
    if (pindex != (mFindBackward ? patLen : 0) && c != patc && !inWhitespace) {
      if (c == '\n' && t2b && IS_CJ_CHAR(prevChar)) {
        PRInt32 nindex = findex + incr;
        if (mFindBackward ? (nindex >= 0) : (nindex < fragLen)) {
          if (IS_CJ_CHAR(t2b[nindex]))
            continue;
        }
      }
    }

    // Compare
    if ((c == patc) || (inWhitespace && IsSpace(c)))
    {
      prevChar = c;
#ifdef DEBUG_FIND
      if (inWhitespace)
        printf("YES (whitespace)(%d of %d)\n", pindex, patLen);
      else
        printf("YES! '%c' == '%c' (%d of %d)\n", c, patc, pindex, patLen);
#endif

      // Save the range anchors if we haven't already:
      if (!matchAnchorNode) {
        matchAnchorNode = mIterNode;
        matchAnchorOffset = findex;
      }

      // Are we done?
      if (DONE_WITH_PINDEX)
        // Matched the whole string!
      {
#ifdef DEBUG_FIND
        printf("Found a match!\n");
#endif

        // Make the range:
        nsCOMPtr<nsIDOMNode> startParent;
        nsCOMPtr<nsIDOMNode> endParent;
        nsCOMPtr<nsIDOMRange> range = CreateRange();
        if (range)
        {
          PRInt32 matchStartOffset, matchEndOffset;
          // convert char index to range point:
          PRInt32 mao = matchAnchorOffset + (mFindBackward ? 1 : 0);
          if (mFindBackward)
          {
            startParent = do_QueryInterface(tc);
            endParent = matchAnchorNode;
            matchStartOffset = findex;
            matchEndOffset = mao;
          }
          else
          {
            startParent = matchAnchorNode;
            endParent = do_QueryInterface(tc);
            matchStartOffset = mao;
            matchEndOffset = findex+1;
          }
          if (startParent && endParent && 
              IsVisibleNode(startParent) && IsVisibleNode(endParent))
          {
            range->SetStart(startParent, matchStartOffset);
            range->SetEnd(endParent, matchEndOffset);
            *aRangeRet = range.get();
            NS_ADDREF(*aRangeRet);
          }
          else {
            startParent = nsnull; // This match is no good -- invisible or bad range
          }
        }

        if (startParent) {
          // If startParent == nsnull, we didn't successfully make range
          // or, we didn't make a range because the start or end node were invisible
          // Reset the offset to the other end of the found string:
          mIterOffset = findex + (mFindBackward ? 1 : 0);
  #ifdef DEBUG_FIND
          printf("mIterOffset = %d, mIterNode = ", mIterOffset);
          DumpNode(mIterNode);
  #endif

          ResetAll();
          return NS_OK;
        }
        matchAnchorNode = nsnull;  // This match is no good, continue on in document
      }

      if (matchAnchorNode) {
        // Not done, but still matching.
        // Advance and loop around for the next characters.
        // But don't advance from a space to a non-space:
        if (!inWhitespace || DONE_WITH_PINDEX || IsSpace(patStr[pindex+incr]))
        {
          pindex += incr;
          inWhitespace = PR_FALSE;
#ifdef DEBUG_FIND
          printf("Advancing pindex to %d\n", pindex);
#endif
        }
      
        continue;
      }
    }

#ifdef DEBUG_FIND
    printf("NOT: %c == %c\n", c, patc);
#endif
    // If we were continuing, then this ends our search.
    if (continuing) {
      ResetAll();
      return NS_OK;
    }

    // If we didn't match, go back to the beginning of patStr,
    // and set findex back to the next char after
    // we started the current match.
    if (matchAnchorNode)    // we're ending a partial match
    {
      findex = matchAnchorOffset;
      mIterOffset = matchAnchorOffset;
          // +incr will be added to findex when we continue

      // Are we going back to a previous node?
      if (matchAnchorNode != mIterNode)
      {
        nsCOMPtr<nsIContent> content (do_QueryInterface(matchAnchorNode));
        nsresult rv = NS_ERROR_UNEXPECTED;
        if (content)
          rv = mIterator->PositionAt(content);
        frag = 0;
        NS_ASSERTION(NS_SUCCEEDED(rv), "Text content wasn't nsIContent!");
#ifdef DEBUG_FIND
        printf("Repositioned anchor node\n");
#endif
      }
#ifdef DEBUG_FIND
      printf("Ending a partial match; findex -> %d, mIterOffset -> %d\n",
             findex, mIterOffset);
#endif
    }
    matchAnchorNode = nsnull;
    matchAnchorOffset = 0;
    inWhitespace = PR_FALSE;
    pindex = (mFindBackward ? patLen : 0);
#ifdef DEBUG_FIND
    printf("Setting findex back to %d, pindex to %d\n", findex, pindex);
           
#endif
  } // end while loop

  // Out of nodes, and didn't match.
  ResetAll();
  return NS_OK;
}