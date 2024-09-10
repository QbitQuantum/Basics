void PaintPlugin::paintMouse(int x, int y) {
    //TODO do not paint outside the drawing surface

    //create the paint color
    ANPPaint* fillPaint = gPaintI.newPaint();
    gPaintI.setFlags(fillPaint, gPaintI.getFlags(fillPaint) | kAntiAlias_ANPPaintFlag);
    gPaintI.setStyle(fillPaint, kFill_ANPPaintStyle);
    gPaintI.setColor(fillPaint, m_activePaintColor);

    // handle the simple "mouse" paint (draw a point)
    ANPRectF point;
    point.left =   (float) x-3;
    point.top =    (float) y-3;
    point.right =  (float) x+3;
    point.bottom = (float) y+3;

    // get a canvas that is only locked around the point and draw it
    ANPCanvas* canvas = getCanvas(&point);
    gCanvasI.drawOval(canvas, &point, fillPaint);

    // clean up
    releaseCanvas(canvas);
    gPaintI.deletePaint(fillPaint);
}