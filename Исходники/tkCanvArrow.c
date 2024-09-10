PathPoint TkPathConfigureArrow(PathPoint pf, PathPoint pl, ArrowDescr *arrowDescr,
        Tk_PathStyle *lineStyle, int updateFirstPoint)
{
    if (arrowDescr->arrowEnabled) {
        PathPoint p0;
        double lineWidth = lineStyle->strokeWidth;
        double shapeLength = arrowDescr->arrowLength;
        double shapeWidth = arrowDescr->arrowWidth;
        double shapeFill = arrowDescr->arrowFillRatio;
        double dx, dy, length, sinTheta, cosTheta;
        double backup;          /* Distance to backup end points so the line
                                 * ends in the middle of the arrowhead. */
        double minsShapeFill;
        PathPoint *poly = arrowDescr->arrowPointsPtr;
        int capStyle = lineStyle->capStyle;    /*  CapButt, CapProjecting, or CapRound. */

        if (!poly) {
            Tcl_Panic("Internal error: PathPoint list is NULL pointer\n");
        }
        if (shapeWidth < lineWidth) {
            shapeWidth = lineWidth;
        }
        minsShapeFill = lineWidth*shapeLength/shapeWidth;
        if (shapeFill > 0.0 && fabs(shapeLength*shapeFill) < fabs(minsShapeFill))
            shapeFill = 1.1*minsShapeFill / shapeLength;

        backup = 0.0;
        if (lineWidth > 1.0) {
            backup = (capStyle == CapProjecting) ? 0.5 * lineWidth : 0.0;
            if (shapeFill > 0.0 && shapeLength != 0.0) {
                backup += 0.5 * lineWidth * shapeLength / shapeWidth;
            }
        }

        dx = pf.x - pl.x;
        dy = pf.y - pl.y;
        length = hypot(dx, dy);
        if (length == 0) {
            sinTheta = cosTheta = 0.0;
        } else {
            sinTheta = dy/length;
            cosTheta = dx/length;
        }

        p0.x = pf.x - shapeLength * cosTheta;
        p0.y = pf.y - shapeLength * sinTheta;
        if (shapeFill > 0.0 && shapeLength != 0.0) {
            poly[0].x = pf.x - shapeLength * shapeFill * cosTheta;
            poly[0].y = pf.y - shapeLength * shapeFill * sinTheta;
            poly[4] = poly[0];
        } else {
            poly[0].x = poly[0].y = poly[4].x = poly[4].y = NaN;
        }
        poly[1].x = p0.x - shapeWidth * sinTheta;
        poly[1].y = p0.y + shapeWidth * cosTheta;
        poly[2].x = pf.x;
        poly[2].y = pf.y;
        poly[3].x = p0.x + shapeWidth * sinTheta;
        poly[3].y = p0.y - shapeWidth * cosTheta;
        /*
         * Polygon done. Now move the first point towards the second so that
         * the corners at the end of the line are inside the arrowhead.
         */

        poly[LINE_PT_IN_ARROW] = poly[ORIG_PT_IN_ARROW];
        if (updateFirstPoint) {
            poly[LINE_PT_IN_ARROW].x -= backup*cosTheta;
            poly[LINE_PT_IN_ARROW].y -= backup*sinTheta;
        }

        return poly[LINE_PT_IN_ARROW];
    }
    return pf;
}