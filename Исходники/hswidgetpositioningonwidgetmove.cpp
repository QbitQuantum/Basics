/*!
    Create the list of rects and flag if their sides are snappable from top or bottom or left or right,
    depending on other rects overlapping with the rect.
*/
void HsSnapToLines::createSnappableRectangles(const QList<QRectF> &inactiveRects)
{
    mInactiveSnapRects.clear();

    int i;
    for (i = 0; i<inactiveRects.count(); ++i) {
        QRectF rect = inactiveRects[i];
        HsSnapRectangle snapRectangle(rect);

        int j;
        for (j = 0; j<inactiveRects.count(); ++j) {
            QRectF rectToCompare = inactiveRects[j];
            if (rect != rectToCompare) {
                //Check if the rectangles being compared intersect each other
                if (rectToCompare.intersects(rect)) {
                    //As the widgets intersect, check which corner is contained,
                    //The corner that is contained is not snappable, when the moving widget is in the same position
                    if (rectToCompare.contains(rect.topLeft())) {
                        snapRectangle.isLeftSnapableForAbove = false;
                        snapRectangle.isTopSnapableForLeft = false;
                    }

                    if (rectToCompare.contains(rect.topRight())) {
                        snapRectangle.isRightSnapableForAbove = false;
                        snapRectangle.isTopSnapableForRight = false;
                    }

                    if (rectToCompare.contains(rect.bottomRight())) {
                        snapRectangle.isRightSnapableForBelow = false;
                        snapRectangle.isBottomSnapableForRight = false;
                    }

                    if (rectToCompare.contains(rect.bottomLeft())) {
                        snapRectangle.isLeftSnapableForBelow = false;
                        snapRectangle.isBottomSnapableForLeft = false;
                    }
                }
            }
        }
        if (snapRectangle.isLeftSnapableForAbove || snapRectangle.isLeftSnapableForBelow ||
            snapRectangle.isRightSnapableForAbove || snapRectangle.isRightSnapableForBelow ||
            snapRectangle.isTopSnapableForLeft || snapRectangle.isTopSnapableForRight ||
            snapRectangle.isBottomSnapableForLeft || snapRectangle.isBottomSnapableForRight) {
                mInactiveSnapRects.append(snapRectangle);
        }
    }
}