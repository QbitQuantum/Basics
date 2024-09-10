void GRCluster::OnDraw(VGDevice &hdc) const
{
    if (mDraw) {
        if (fNoteFormatColor) {
            VGColor color(fNoteFormatColor);
            hdc.PushPen(color, 1);

            if (!mColRef)
                hdc.PushFillColor(color);
        }

    	if (mColRef) {
            VGColor color(mColRef);
            hdc.PushFillColor(color);
            hdc.PushPenColor(color);
        }

    	// - Quarter notes and less
    	if (fDuration < DURATION_2) {
            const float xCoords [] = {
                mMapping.left,
                mMapping.right,
                mMapping.right,
                mMapping.left};
            const float yCoords [] = {
                mMapping.top,
                mMapping.top,
                mMapping.bottom,
                mMapping.bottom};

            hdc.Polygon(xCoords, yCoords, 4);
        }
	    else {
            const float xCoords1 [] = {
                mMapping.left,
                mMapping.right,
                mMapping.right,
                mMapping.left};
            const float yCoords1 [] = {
                mMapping.top,
                mMapping.top,
                mMapping.top + 6 * mTagSize * fsize,
                mMapping.top + 6 * mTagSize * fsize};
            const float xCoords2 [] = {
                mMapping.right - 6 * mTagSize * fsize,
                mMapping.right,
                mMapping.right,
                mMapping.right - 6 * mTagSize * fsize};
            const float yCoords2 [] = {
                mMapping.top,
                mMapping.top,
                mMapping.bottom,
                mMapping.bottom};
            const float xCoords3 [] = {
                mMapping.left,
                mMapping.right,
                mMapping.right,
                mMapping.left};
            const float yCoords3 [] = {
                mMapping.bottom - 6 * mTagSize * fsize,
                mMapping.bottom - 6 * mTagSize * fsize,
                mMapping.bottom,
                mMapping.bottom};
            const float xCoords4 [] = {
                mMapping.left,
                mMapping.left + 6 * mTagSize * fsize,
                mMapping.left + 6 * mTagSize * fsize,
                mMapping.left};
            const float yCoords4 [] = {
                mMapping.top,
                mMapping.top,
                mMapping.bottom,
                mMapping.bottom};

            hdc.Polygon(xCoords1, yCoords1, 4);
            hdc.Polygon(xCoords2, yCoords2, 4);
            hdc.Polygon(xCoords3, yCoords3, 4);
            hdc.Polygon(xCoords4, yCoords4, 4);
        }

	    // - Restore context
	    if (mColRef) {
            hdc.PopPenColor();
		    hdc.PopFillColor();
        }

        if (fNoteFormatColor) {
            if (!mColRef)
                hdc.PopFillColor();

            hdc.PopPen();
        }
	}
}