static void modeMessageFast(DisplayInternalInfo& displayInternalInfo) {
  int boardId, i;

  HT1632Class& HT1632 = displayInternalInfo.ht1632;
  HT1632.clearAll();

  const int currColorEffect = modeMessageDataColorEffect % 3; 
  for (i=0; i < BUFFER_SECONDARY; ++i) {
    if (modeMessageData.blinkBlankInEffect) break;  // blinkBlankInEffect in effect? If so, write no chars

    switch (modeMessageData.displayColor) {
        case displayColorGreen: boardId = 0; break;
        case displayColorRed: boardId = 1; break;
        case displayColorYellow: boardId = i; break;
        case displayColorAlternate:  // fall thru
        default: boardId = currColorEffect == 2 ? i : currColorEffect; break;
    }

    HT1632.drawTarget(BUFFER_BOARD(boardId+1));

    // if bouncing, make sure sure y is within range
    const int wantedY = modeMessageData.currYFactor / INCREMENT_Y_SCALE;
    const int adjustedY = modeMessageData.incrementY ? getAdjustedTextY(modeMessageData.font, wantedY) : wantedY;

    HT1632.drawText(modeMessageData.msg,
		    modeMessageData.incrementX ? (OUT_SIZE - modeMessageData.currX) : modeMessageData.currX /*x*/,
		    adjustedY /*y*/,
		    getFontData(modeMessageData.font),
		    getFontWidth(modeMessageData.font),
		    getFontHeight(modeMessageData.font),
		    getFontGlyphStep(modeMessageData.font));

    if (modeMessageData.displayColor == displayColorAlternate && currColorEffect == 2) continue;
    if (modeMessageData.displayColor != displayColorYellow) break;
  }

  drawBackgroundMessages(displayInternalInfo);
  drawBackgroundImgs(displayInternalInfo);

  // confetti
  if (modeMessageData.confetti > 0) {
    for (boardId=0; boardId < BUFFER_SECONDARY; ++boardId) {
      HT1632.drawTarget(BUFFER_BOARD(boardId+1));
      for (int xx = 0, yy = (int) getRandomNumber(modeMessageData.confetti); xx <= yy ; ++xx) {
	HT1632.setPixel( (int) getRandomNumber(OUT_SIZE), (int) getRandomNumber(COM_SIZE));
      }
    }
  }

  HT1632.renderAll();

  // text wrap
  if (modeMessageData.incrementX && ++modeMessageData.currX >= (modeMessageData.wd + OUT_SIZE)) {
    modeMessageData.currX = 0;
    ++modeMessageDataColorEffect;

    if (modeMessageData.alternateFont) {
      modeMessageData.font = getNextFont(modeMessageData.font);
      modeMessageData.wd = HT1632.getTextWidth(modeMessageData.msg,
					       getFontWidth(modeMessageData.font),
					       getFontHeight(modeMessageData.font));
    }

    // repeats?
    if (modeMessageData.repeats != ~0) {
      // mode exit (1 of 2)
      if (--modeMessageData.repeats < 0) {
	modeMessageData.repeats = ~0;  // avoid getting here again...
	if (modeMessageData.completedCallback != nullptr) {
	  (*(modeMessageData.completedCallback))(displayInternalInfo, modeMessageData.completedCallbackParam);
	  return;
	}
      }
    }
  }

  // Y (bounce effect)
  if (modeMessageData.incrementY != 0) {
    modeMessageData.currYFactor += modeMessageData.incrementY;

    const int maxY = COM_SIZE - getFontHeight(modeMessageData.font);
    if (modeMessageData.incrementY < 0 && modeMessageData.currYFactor < 0) {
      modeMessageData.incrementY *= -1;
    } else if (modeMessageData.incrementY > 0 && (modeMessageData.currYFactor >= maxY * INCREMENT_Y_SCALE)) {
      modeMessageData.incrementY *= -1;

      if (!modeMessageData.incrementX) {
	++modeMessageDataColorEffect;
	if (modeMessageData.alternateFont) {
	  modeMessageData.font = getNextFont(modeMessageData.font);
	  // modeMessageData.wd = HT1632.getTextWidth(modeMessageData.msg,
	  //				  	   getFontWidth(modeMessageData.font),
	  //					   getFontHeight(modeMessageData.font));
	}
      }
    }
  }
}