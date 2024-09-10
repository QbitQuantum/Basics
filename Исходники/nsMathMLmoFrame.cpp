// NOTE: aDesiredStretchSize is an IN/OUT parameter
//       On input  - it contains our current size
//       On output - the same size or the new size that we want
NS_IMETHODIMP
nsMathMLmoFrame::Stretch(nsRenderingContext& aRenderingContext,
                         nsStretchDirection   aStretchDirection,
                         nsBoundingMetrics&   aContainerSize,
                         nsHTMLReflowMetrics& aDesiredStretchSize)
{
  if (NS_MATHML_STRETCH_WAS_DONE(mPresentationData.flags)) {
    NS_WARNING("it is wrong to fire stretch more than once on a frame");
    return NS_OK;
  }
  mPresentationData.flags |= NS_MATHML_STRETCH_DONE;

  nsIFrame* firstChild = mFrames.FirstChild();

  // get the axis height;
  float fontSizeInflation = nsLayoutUtils::FontSizeInflationFor(this);
  nsRefPtr<nsFontMetrics> fm;
  nsLayoutUtils::GetFontMetricsForFrame(this, getter_AddRefs(fm),
                                        fontSizeInflation);
  nscoord axisHeight, height;
  GetAxisHeight(aRenderingContext, fm, axisHeight);

  // get the leading to be left at the top and the bottom of the stretched char
  // this seems more reliable than using fm->GetLeading() on suspicious fonts
  nscoord em;
  GetEmHeight(fm, em);
  nscoord leading = NSToCoordRound(0.2f * em);

  // Operators that are stretchy, or those that are to be centered
  // to cater for fonts that are not math-aware, are handled by the MathMLChar
  // ('form' is reset if stretch fails -- i.e., we don't bother to stretch next time)
  bool useMathMLChar = UseMathMLChar();

  nsBoundingMetrics charSize;
  nsBoundingMetrics container = aDesiredStretchSize.mBoundingMetrics;
  bool isVertical = false;

  if (((aStretchDirection == NS_STRETCH_DIRECTION_VERTICAL) ||
       (aStretchDirection == NS_STRETCH_DIRECTION_DEFAULT))  &&
      (mEmbellishData.direction == NS_STRETCH_DIRECTION_VERTICAL)) {
    isVertical = true;
  }

  uint32_t stretchHint =
    GetStretchHint(mFlags, mPresentationData, isVertical, StyleFont());

  if (useMathMLChar) {
    nsBoundingMetrics initialSize = aDesiredStretchSize.mBoundingMetrics;

    if (stretchHint != NS_STRETCH_NONE) {

      container = aContainerSize;

      // some adjustments if the operator is symmetric and vertical

      if (isVertical && NS_MATHML_OPERATOR_IS_SYMMETRIC(mFlags)) {
        // we need to center about the axis
        nscoord delta = std::max(container.ascent - axisHeight,
                               container.descent + axisHeight);
        container.ascent = delta + axisHeight;
        container.descent = delta - axisHeight;

        // get ready in case we encounter user-desired min-max size
        delta = std::max(initialSize.ascent - axisHeight,
                       initialSize.descent + axisHeight);
        initialSize.ascent = delta + axisHeight;
        initialSize.descent = delta - axisHeight;
      }

      // check for user-desired min-max size

      if (mMaxSize != NS_MATHML_OPERATOR_SIZE_INFINITY && mMaxSize > 0.0f) {
        // if we are here, there is a user defined maxsize ...
        //XXX Set stretchHint = NS_STRETCH_NORMAL? to honor the maxsize as close as possible?
        if (NS_MATHML_OPERATOR_MAXSIZE_IS_ABSOLUTE(mFlags)) {
          // there is an explicit value like maxsize="20pt"
          // try to maintain the aspect ratio of the char
          float aspect = mMaxSize / float(initialSize.ascent + initialSize.descent);
          container.ascent =
            std::min(container.ascent, nscoord(initialSize.ascent * aspect));
          container.descent =
            std::min(container.descent, nscoord(initialSize.descent * aspect));
          // below we use a type cast instead of a conversion to avoid a VC++ bug
          // see http://support.microsoft.com/support/kb/articles/Q115/7/05.ASP
          container.width =
            std::min(container.width, (nscoord)mMaxSize);
        }
        else { // multiplicative value
          container.ascent =
            std::min(container.ascent, nscoord(initialSize.ascent * mMaxSize));
          container.descent =
            std::min(container.descent, nscoord(initialSize.descent * mMaxSize));
          container.width =
            std::min(container.width, nscoord(initialSize.width * mMaxSize));
        }

        if (isVertical && !NS_MATHML_OPERATOR_IS_SYMMETRIC(mFlags)) {
          // re-adjust to align the char with the bottom of the initial container
          height = container.ascent + container.descent;
          container.descent = aContainerSize.descent;
          container.ascent = height - container.descent;
        }
      }

      if (mMinSize > 0.0f) {
        // if we are here, there is a user defined minsize ...
        // always allow the char to stretch in its natural direction,
        // even if it is different from the caller's direction 
        if (aStretchDirection != NS_STRETCH_DIRECTION_DEFAULT &&
            aStretchDirection != mEmbellishData.direction) {
          aStretchDirection = NS_STRETCH_DIRECTION_DEFAULT;
          // but when we are not honoring the requested direction
          // we should not use the caller's container size either
          container = initialSize;
        }
        if (NS_MATHML_OPERATOR_MINSIZE_IS_ABSOLUTE(mFlags)) {
          // there is an explicit value like minsize="20pt"
          // try to maintain the aspect ratio of the char
          float aspect = mMinSize / float(initialSize.ascent + initialSize.descent);
          container.ascent =
            std::max(container.ascent, nscoord(initialSize.ascent * aspect));
          container.descent =
            std::max(container.descent, nscoord(initialSize.descent * aspect));
          container.width =
            std::max(container.width, (nscoord)mMinSize);
        }
        else { // multiplicative value
          container.ascent =
            std::max(container.ascent, nscoord(initialSize.ascent * mMinSize));
          container.descent =
            std::max(container.descent, nscoord(initialSize.descent * mMinSize));
          container.width =
            std::max(container.width, nscoord(initialSize.width * mMinSize));
        }

        if (isVertical && !NS_MATHML_OPERATOR_IS_SYMMETRIC(mFlags)) {
          // re-adjust to align the char with the bottom of the initial container
          height = container.ascent + container.descent;
          container.descent = aContainerSize.descent;
          container.ascent = height - container.descent;
        }
      }
    }

    // let the MathMLChar stretch itself...
    nsresult res = mMathMLChar.Stretch(PresContext(), aRenderingContext,
                                       fontSizeInflation,
                                       aStretchDirection, container, charSize,
                                       stretchHint,
                                       StyleVisibility()->mDirection);
    if (NS_FAILED(res)) {
      // gracefully handle cases where stretching the char failed (i.e., GetBoundingMetrics failed)
      // clear our 'form' to behave as if the operator wasn't in the dictionary
      mFlags &= ~NS_MATHML_OPERATOR_FORM;
      useMathMLChar = false;
    }
  }

  // Place our children using the default method
  // This will allow our child text frame to get its DidReflow()
  nsresult rv = Place(aRenderingContext, true, aDesiredStretchSize);
  if (NS_MATHML_HAS_ERROR(mPresentationData.flags) || NS_FAILED(rv)) {
    // Make sure the child frames get their DidReflow() calls.
    DidReflowChildren(mFrames.FirstChild());
  }

  if (useMathMLChar) {
    // update our bounding metrics... it becomes that of our MathML char
    mBoundingMetrics = charSize;

    // if the returned direction is 'unsupported', the char didn't actually change. 
    // So we do the centering only if necessary
    if (mMathMLChar.GetStretchDirection() != NS_STRETCH_DIRECTION_UNSUPPORTED ||
        NS_MATHML_OPERATOR_IS_CENTERED(mFlags)) {

      bool largeopOnly =
        (NS_STRETCH_LARGEOP & stretchHint) != 0 &&
        (NS_STRETCH_VARIABLE_MASK & stretchHint) == 0;

      if (isVertical || NS_MATHML_OPERATOR_IS_CENTERED(mFlags)) {
        // the desired size returned by mMathMLChar maybe different
        // from the size of the container.
        // the mMathMLChar.mRect.y calculation is subtle, watch out!!!

        height = mBoundingMetrics.ascent + mBoundingMetrics.descent;
        if (NS_MATHML_OPERATOR_IS_SYMMETRIC(mFlags) ||
            NS_MATHML_OPERATOR_IS_CENTERED(mFlags)) {
          // For symmetric and vertical operators, or for operators that are always
          // centered ('+', '*', etc) we want to center about the axis of the container
          mBoundingMetrics.descent = height/2 - axisHeight;
        } else if (!largeopOnly) {
          // Align the center of the char with the center of the container
          mBoundingMetrics.descent = height/2 +
            (container.ascent + container.descent)/2 - container.ascent;
        } // else align the baselines
        mBoundingMetrics.ascent = height - mBoundingMetrics.descent;
      }
    }
  }

  // Fixup for the final height.
  // On one hand, our stretchy height can sometimes be shorter than surrounding
  // ASCII chars, e.g., arrow symbols have |mBoundingMetrics.ascent + leading|
  // that is smaller than the ASCII's ascent, hence when painting the background
  // later, it won't look uniform along the line.
  // On the other hand, sometimes we may leave too much gap when our glyph happens
  // to come from a font with tall glyphs. For example, since CMEX10 has very tall
  // glyphs, its natural font metrics are large, even if we pick a small glyph
  // whose size is comparable to the size of a normal ASCII glyph.
  // So to avoid uneven spacing in either of these two cases, we use the height
  // of the ASCII font as a reference and try to match it if possible.

  // special case for accents... keep them short to improve mouse operations...
  // an accent can only be the non-first child of <mover>, <munder>, <munderover>
  bool isAccent =
    NS_MATHML_EMBELLISH_IS_ACCENT(mEmbellishData.flags);
  if (isAccent) {
    nsEmbellishData parentData;
    GetEmbellishDataFrom(GetParent(), parentData);
    isAccent =
       (NS_MATHML_EMBELLISH_IS_ACCENTOVER(parentData.flags) ||
        NS_MATHML_EMBELLISH_IS_ACCENTUNDER(parentData.flags)) &&
       parentData.coreFrame != this;
  }
  if (isAccent && firstChild) {
    // see bug 188467 for what is going on here
    nscoord dy = aDesiredStretchSize.BlockStartAscent() -
      (mBoundingMetrics.ascent + leading);
    aDesiredStretchSize.SetBlockStartAscent(mBoundingMetrics.ascent + leading);
    aDesiredStretchSize.Height() = aDesiredStretchSize.BlockStartAscent() +
                                   mBoundingMetrics.descent;

    firstChild->SetPosition(firstChild->GetPosition() - nsPoint(0, dy));
  }
  else if (useMathMLChar) {
    nscoord ascent = fm->MaxAscent();
    nscoord descent = fm->MaxDescent();
    aDesiredStretchSize.SetBlockStartAscent(std::max(mBoundingMetrics.ascent + leading, ascent));
    aDesiredStretchSize.Height() = aDesiredStretchSize.BlockStartAscent() +
                                 std::max(mBoundingMetrics.descent + leading, descent);
  }
  aDesiredStretchSize.Width() = mBoundingMetrics.width;
  aDesiredStretchSize.mBoundingMetrics = mBoundingMetrics;
  mReference.x = 0;
  mReference.y = aDesiredStretchSize.BlockStartAscent();
  // Place our mMathMLChar, its origin is in our coordinate system
  if (useMathMLChar) {
    nscoord dy = aDesiredStretchSize.BlockStartAscent() - mBoundingMetrics.ascent;
    mMathMLChar.SetRect(nsRect(0, dy, charSize.width, charSize.ascent + charSize.descent));
  }

  // Before we leave... there is a last item in the check-list:
  // If our parent is not embellished, it means we are the outermost embellished
  // container and so we put the spacing, otherwise we don't include the spacing,
  // the outermost embellished container will take care of it.

  if (!NS_MATHML_OPERATOR_HAS_EMBELLISH_ANCESTOR(mFlags)) {

    // Account the spacing if we are not an accent with explicit attributes
    nscoord leadingSpace = mEmbellishData.leadingSpace;
    if (isAccent && !NS_MATHML_OPERATOR_HAS_LSPACE_ATTR(mFlags)) {
      leadingSpace = 0;
    }
    nscoord trailingSpace = mEmbellishData.trailingSpace;
    if (isAccent && !NS_MATHML_OPERATOR_HAS_RSPACE_ATTR(mFlags)) {
      trailingSpace = 0;
    }

    mBoundingMetrics.width += leadingSpace + trailingSpace;
    aDesiredStretchSize.Width() = mBoundingMetrics.width;
    aDesiredStretchSize.mBoundingMetrics.width = mBoundingMetrics.width;

    nscoord dx = (StyleVisibility()->mDirection ?
                  trailingSpace : leadingSpace);
    if (dx) {
      // adjust the offsets
      mBoundingMetrics.leftBearing += dx;
      mBoundingMetrics.rightBearing += dx;
      aDesiredStretchSize.mBoundingMetrics.leftBearing += dx;
      aDesiredStretchSize.mBoundingMetrics.rightBearing += dx;

      if (useMathMLChar) {
        nsRect rect;
        mMathMLChar.GetRect(rect);
        mMathMLChar.SetRect(nsRect(rect.x + dx, rect.y,
                                   rect.width, rect.height));
      }
      else {
        nsIFrame* childFrame = firstChild;
        while (childFrame) {
          childFrame->SetPosition(childFrame->GetPosition() +
                                  nsPoint(dx, 0));
          childFrame = childFrame->GetNextSibling();
        }
      }
    }
  }

  // Finished with these:
  ClearSavedChildMetrics();
  // Set our overflow area
  GatherAndStoreOverflow(&aDesiredStretchSize);

  // There used to be code here to change the height of the child frame to
  // change the caret height, but the text frame that manages the caret is now
  // not a direct child but wrapped in a block frame.  See also bug 412033.

  return NS_OK;
}