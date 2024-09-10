void DrasculaEngine::moveCharacters() {
	int curPos[6];
	int r;

	if (characterMoved == 1 && stepX == STEP_X) {
		for (r = 0; r < stepX; r++) {
			if (currentChapter != 2) {
				if (trackProtagonist == 0 && roomX - r == curX + curWidth / 2) {
					characterMoved = 0;
					stepX = STEP_X;
					stepY = STEP_Y;
				}
				if (trackProtagonist == 1 && roomX + r == curX + curWidth / 2) {
					characterMoved = 0;
					stepX = STEP_X;
					stepY = STEP_Y;
					curX = roomX - curWidth / 2;
					curY = roomY - curHeight;
				}
			} else if (currentChapter == 2) {
				if (trackProtagonist == 0 && roomX - r == curX) {
					characterMoved = 0;
					stepX = STEP_X;
					stepY = STEP_Y;
				}
				if (trackProtagonist == 1 && roomX + r == curX + curWidth) {
					characterMoved = 0;
					stepX = STEP_X;
					stepY = STEP_Y;
					curX = roomX - curWidth + 4;
					curY = roomY - curHeight;
				}
			}
		}
	}
	if (characterMoved == 1 && stepY == STEP_Y) {
		for (r = 0; r < stepY; r++) {
			if (trackProtagonist == 2 && roomY - r == curY + curHeight) {
				characterMoved = 0;
				stepX = STEP_X;
				stepY = STEP_Y;
			}
			if (trackProtagonist == 3 && roomY + r == curY + curHeight) {
				characterMoved = 0;
				stepX = STEP_X;
				stepY = STEP_Y;
			}
		}
	}

	if (currentChapter != 2 && currentChapter != 3) {
		if (characterVisible == 0) {
			increaseFrameNum();
			return;
		}
	}

	if (characterMoved == 0) {
		curPos[0] = 0;
		curPos[1] = DIF_MASK_HARE;
		curPos[2] = curX;
		curPos[3] = curY;
		if (currentChapter == 2) {
			curPos[4] = curWidth;
			curPos[5] = curHeight;
		} else {
			curPos[4] = CHARACTER_WIDTH;
			curPos[5] = CHARACTER_HEIGHT;
		}

		if (trackProtagonist == 0) {
			curPos[1] = 0;
			if (currentChapter == 2)
				copyRect(curPos[0], curPos[1], curPos[2], curPos[3], curPos[4], curPos[5],
						 extraSurface, screenSurface);
			else
				reduce_hare_chico(curPos[0], curPos[1], curPos[2], curPos[3], curPos[4], curPos[5],
									factor_red[curY + curHeight], extraSurface, screenSurface);
		} else if (trackProtagonist == 1) {
			if (currentChapter == 2)
				copyRect(curPos[0], curPos[1], curPos[2], curPos[3], curPos[4], curPos[5],
						 extraSurface, screenSurface);
			else
				reduce_hare_chico(curPos[0], curPos[1], curPos[2], curPos[3], curPos[4], curPos[5],
									factor_red[curY + curHeight], extraSurface, screenSurface);
		} else if (trackProtagonist == 2) {
			if (currentChapter == 2)
				copyRect(curPos[0], curPos[1], curPos[2], curPos[3], curPos[4], curPos[5],
						 backSurface, screenSurface);
			else
				reduce_hare_chico(curPos[0], curPos[1], curPos[2], curPos[3], curPos[4], curPos[5],
									factor_red[curY + curHeight], backSurface, screenSurface);
		} else {
			if (currentChapter == 2)
				copyRect(curPos[0], curPos[1], curPos[2], curPos[3], curPos[4], curPos[5],
						 frontSurface, screenSurface);
			else
				reduce_hare_chico(curPos[0], curPos[1], curPos[2], curPos[3], curPos[4], curPos[5],
									factor_red[curY + curHeight], frontSurface, screenSurface);
		}
	} else if (characterMoved == 1) {
		curPos[0] = _frameX[_characterFrame];
		curPos[1] = frame_y + DIF_MASK_HARE;
		curPos[2] = curX;
		curPos[3] = curY;
		if (currentChapter == 2) {
			curPos[4] = curWidth;
			curPos[5] = curHeight;
		} else {
			curPos[4] = CHARACTER_WIDTH;
			curPos[5] = CHARACTER_HEIGHT;
		}
		if (trackProtagonist == 0) {
			curPos[1] = 0;
			if (currentChapter == 2)
				copyRect(curPos[0], curPos[1], curPos[2], curPos[3], curPos[4], curPos[5],
						 extraSurface, screenSurface);
			else
				reduce_hare_chico(curPos[0], curPos[1], curPos[2], curPos[3], curPos[4], curPos[5],
									factor_red[curY + curHeight], extraSurface, screenSurface);
		} else if (trackProtagonist == 1) {
			if (currentChapter == 2)
				copyRect(curPos[0], curPos[1], curPos[2], curPos[3], curPos[4], curPos[5],
						 extraSurface, screenSurface);
			else
				reduce_hare_chico(curPos[0], curPos[1], curPos[2], curPos[3], curPos[4], curPos[5],
									factor_red[curY + curHeight], extraSurface, screenSurface);
		} else if (trackProtagonist == 2) {
			if (currentChapter == 2)
				copyRect(curPos[0], curPos[1], curPos[2], curPos[3], curPos[4], curPos[5],
						 backSurface, screenSurface);
			else
				reduce_hare_chico(curPos[0], curPos[1], curPos[2], curPos[3], curPos[4], curPos[5],
									factor_red[curY + curHeight], backSurface, screenSurface);
		} else {
			if (currentChapter == 2)
				copyRect(curPos[0], curPos[1], curPos[2], curPos[3], curPos[4], curPos[5],
						 frontSurface, screenSurface);
			else
				reduce_hare_chico(curPos[0], curPos[1], curPos[2], curPos[3], curPos[4], curPos[5],
									factor_red[curY + curHeight], frontSurface, screenSurface);
		}
		increaseFrameNum();
	}
}