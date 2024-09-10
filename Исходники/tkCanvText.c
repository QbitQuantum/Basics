static void
ComputeTextBbox(
    Tk_Canvas canvas,		/* Canvas that contains item. */
    TextItem *textPtr)		/* Item whose bbox is to be recomputed. */
{
    Tk_CanvasTextInfo *textInfoPtr;
    int leftX, topY, width, height, fudge, i;
    Tk_State state = textPtr->header.state;
    double x[4], y[4], dx[4], dy[4], sinA, cosA, tmp;

    if (state == TK_STATE_NULL) {
	state = Canvas(canvas)->canvas_state;
    }

    Tk_FreeTextLayout(textPtr->textLayout);
    textPtr->textLayout = Tk_ComputeTextLayout(textPtr->tkfont,
	    textPtr->text, textPtr->numChars, textPtr->width,
	    textPtr->justify, 0, &width, &height);

    if (state == TK_STATE_HIDDEN || textPtr->color == NULL) {
	width = height = 0;
    }

    /*
     * Use overall geometry information to compute the top-left corner of the
     * bounding box for the text item.
     */

    leftX = ROUND(textPtr->x);
    topY = ROUND(textPtr->y);
    for (i=0 ; i<4 ; i++) {
	dx[i] = dy[i] = 0.0;
    }
    switch (textPtr->anchor) {
    case TK_ANCHOR_NW:
    case TK_ANCHOR_N:
    case TK_ANCHOR_NE:
	break;

    case TK_ANCHOR_W:
    case TK_ANCHOR_CENTER:
    case TK_ANCHOR_E:
	topY -= height / 2;
	for (i=0 ; i<4 ; i++) {
	    dy[i] = -height / 2;
	}
	break;

    case TK_ANCHOR_SW:
    case TK_ANCHOR_S:
    case TK_ANCHOR_SE:
	topY -= height;
	for (i=0 ; i<4 ; i++) {
	    dy[i] = -height;
	}
	break;
    }
    switch (textPtr->anchor) {
    case TK_ANCHOR_NW:
    case TK_ANCHOR_W:
    case TK_ANCHOR_SW:
	break;

    case TK_ANCHOR_N:
    case TK_ANCHOR_CENTER:
    case TK_ANCHOR_S:
	leftX -= width / 2;
	for (i=0 ; i<4 ; i++) {
	    dx[i] = -width / 2;
	}
	break;

    case TK_ANCHOR_NE:
    case TK_ANCHOR_E:
    case TK_ANCHOR_SE:
	leftX -= width;
	for (i=0 ; i<4 ; i++) {
	    dx[i] = -width;
	}
	break;
    }

    textPtr->actualWidth = width;

    sinA = textPtr->sine;
    cosA = textPtr->cosine;
    textPtr->drawOrigin[0] = textPtr->x + dx[0]*cosA + dy[0]*sinA;
    textPtr->drawOrigin[1] = textPtr->y + dy[0]*cosA - dx[0]*sinA;

    /*
     * Last of all, update the bounding box for the item. The item's bounding
     * box includes the bounding box of all its lines, plus an extra fudge
     * factor for the cursor border (which could potentially be quite large).
     */

    textInfoPtr = textPtr->textInfoPtr;
    fudge = (textInfoPtr->insertWidth + 1) / 2;
    if (textInfoPtr->selBorderWidth > fudge) {
	fudge = textInfoPtr->selBorderWidth;
    }

    /*
     * Apply the rotation before computing the bounding box.
     */

    dx[0] -= fudge;
    dx[1] += width + fudge;
    dx[2] += width + fudge;
    dy[2] += height;
    dx[3] -= fudge;
    dy[3] += height;
    for (i=0 ; i<4 ; i++) {
	x[i] = textPtr->x + dx[i] * cosA + dy[i] * sinA;
	y[i] = textPtr->y + dy[i] * cosA - dx[i] * sinA;
    }

    /*
     * Convert to a rectilinear bounding box.
     */

    for (i=1,tmp=x[0] ; i<4 ; i++) {
	if (x[i] < tmp) {
	    tmp = x[i];
	}
    }
    textPtr->header.x1 = ROUND(tmp);
    for (i=1,tmp=y[0] ; i<4 ; i++) {
	if (y[i] < tmp) {
	    tmp = y[i];
	}
    }
    textPtr->header.y1 = ROUND(tmp);
    for (i=1,tmp=x[0] ; i<4 ; i++) {
	if (x[i] > tmp) {
	    tmp = x[i];
	}
    }
    textPtr->header.x2 = ROUND(tmp);
    for (i=1,tmp=y[0] ; i<4 ; i++) {
	if (y[i] > tmp) {
	    tmp = y[i];
	}
    }
    textPtr->header.y2 = ROUND(tmp);
}