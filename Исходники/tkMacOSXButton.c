void
TkpComputeButtonGeometry(
    TkButton *butPtr)		/* Button whose geometry may have changed. */
{
    int width = 0, height = 0, charWidth = 1, haveImage = 0, haveText = 0;
    int txtWidth = 0, txtHeight = 0;
    MacButton *mbPtr = (MacButton*)butPtr;
    Tk_FontMetrics fm;
    DrawParams drawParams;

    /*
     * First figure out the size of the contents of the button.
     */

    TkMacOSXComputeButtonParams(butPtr, &mbPtr->btnkind, &mbPtr->drawinfo);

    /*
     * If the indicator is on, get its size.
     */

    if ( butPtr->indicatorOn ) {
      switch (butPtr->type) {
      case TYPE_RADIO_BUTTON:
	GetThemeMetric(kThemeMetricRadioButtonWidth, &butPtr->indicatorDiameter);
	  break;
      case TYPE_CHECK_BUTTON:
	GetThemeMetric(kThemeMetricCheckBoxWidth, &butPtr->indicatorDiameter);
	  break;
      default:
	break;
      }
      /* Allow 2px extra space next to the indicator. */
      butPtr->indicatorSpace = butPtr->indicatorDiameter + 2;
    } else {
      butPtr->indicatorSpace = 0;
      butPtr->indicatorDiameter = 0;
    }

    if (butPtr->image != NULL) {
	Tk_SizeOfImage(butPtr->image, &width, &height);
	haveImage = 1;
    } else if (butPtr->bitmap != None) {
	Tk_SizeOfBitmap(butPtr->display, butPtr->bitmap, &width, &height);
	haveImage = 1;
    }

    if (haveImage == 0 || butPtr->compound != COMPOUND_NONE) {
	Tk_FreeTextLayout(butPtr->textLayout);
	butPtr->textLayout = Tk_ComputeTextLayout(butPtr->tkfont,
		Tcl_GetString(butPtr->textPtr), -1, butPtr->wrapLength,
		butPtr->justify, 0, &butPtr->textWidth, &butPtr->textHeight);

	txtWidth = butPtr->textWidth;
	txtHeight = butPtr->textHeight;
	charWidth = Tk_TextWidth(butPtr->tkfont, "0", 1);
	Tk_GetFontMetrics(butPtr->tkfont, &fm);
	haveText = (txtWidth != 0 && txtHeight != 0);
    }

    if (haveImage && haveText) { /* Image and Text */
	switch ((enum compound) butPtr->compound) {
	    case COMPOUND_TOP:
	    case COMPOUND_BOTTOM:
		/*
		 * Image is above or below text.
		 */

		height += txtHeight + butPtr->padY;
		width = (width > txtWidth ? width : txtWidth);
		break;
	    case COMPOUND_LEFT:
	    case COMPOUND_RIGHT:
		/*
		 * Image is left or right of text.
		 */

		width += txtWidth + butPtr->padX;
		height = (height > txtHeight ? height : txtHeight);
		break;
	    case COMPOUND_CENTER:
		/*
		 * Image and text are superimposed.
		 */

		width = (width > txtWidth ? width : txtWidth);
		height = (height > txtHeight ? height : txtHeight);
		break;
	    default:
		break;
	}
	width += butPtr->indicatorSpace;

    } else if (haveImage) { /* Image only */
      width = butPtr->width > 0 ? butPtr->width : width + butPtr->indicatorSpace;
      height = butPtr->height > 0 ? butPtr->height : height;

    } else { /* Text only */
        width = txtWidth + butPtr->indicatorSpace;
	height = txtHeight;
	if (butPtr->width > 0) {
	   width = butPtr->width * charWidth;
	}
	if (butPtr->height > 0) {
	  height = butPtr->height * fm.linespace;
	}
    }

    /* Add padding */
    width  += 2 * butPtr->padX;
    height += 2 * butPtr->padY;

    /*
     * Now figure out the size of the border decorations for the button.
     */

    if (butPtr->highlightWidth < 0) {
	butPtr->highlightWidth = 0;
    }

    butPtr->inset = 0;
    butPtr->inset += butPtr->highlightWidth;
    
    if (TkMacOSXComputeButtonDrawParams(butPtr,&drawParams)) {
        HIRect tmpRect;
    	HIRect contBounds;
        int paddingx = 0;
        int paddingy = 0;

    	tmpRect = CGRectMake(0, 0, width, height);

        HIThemeGetButtonContentBounds(&tmpRect, &mbPtr->drawinfo, &contBounds);
        /* If the content region has a minimum height, match it. */
        if (height < contBounds.size.height) {
    	  height = contBounds.size.height;
        }

        /* If the content region has a minimum width, match it. */
        if (width < contBounds.size.width) {
    	  width = contBounds.size.width;
        }

        /* Pad to fill difference between content bounds and button bounds. */
    	paddingx = contBounds.origin.x;
    	paddingy = contBounds.origin.y;

        if (height < paddingx - 4) {
            /* can't have buttons much shorter than button side diameter. */
            height = paddingx - 4;
    	}

    } else {
        height += butPtr->borderWidth*2;
        width += butPtr->borderWidth*2;
    }

    width += butPtr->inset*2;
    height += butPtr->inset*2;

    Tk_GeometryRequest(butPtr->tkwin, width, height);
    Tk_SetInternalBorder(butPtr->tkwin, butPtr->inset);
}