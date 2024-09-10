void SourceItemDelegate::paintArrows(QPainter *p,
				     const QStyleOptionViewItem &option,
				     const QModelIndex &index) const
{
    QTreeWidget *lv = _parent;
    if ( !lv ) return;
    SourceView* sv = (SourceView*) lv;
    SourceItem* item = static_cast<SourceItem*>(index.internalPointer());
    const QRect& rect = option.rect;
    int height = rect.height();

    p->save();
    drawBackground(p, option, index);
    p->translate(rect.topLeft());

    int marg = 1;
    int yy = height/2, y1, y2;
    QColor c;

    int start = -1, end = -1;

    TraceLineJump* lineJump = item->lineJump();
    uint lineno = item->lineno();
    TraceLineCall* lineCall = item->lineCall();

    // draw line borders, detect start/stop of a line
    for(int i=0; i< item->jumpCount(); i++) {
        TraceLineJump* jump = item->jump(i);
        if (jump == 0) continue;

        y1 = 0;
        y2 = height;
        if (lineJump &&
            (lineJump->lineTo() == jump->lineTo()) &&
            (jump->lineFrom()->lineno() == lineno)) {

            if (start<0) start = i;
            if (lineJump == jump) {
                if (jump->lineTo()->lineno() <= lineno)
                    y2 = yy;
                else
                    y1 = yy;
            }
        }
        else if (!lineJump && !lineCall &&
                 (jump->lineTo()->lineno() == lineno)) {
            if (end<0) end = i;
            if (jump->lineFrom()->lineno() < lineno)
                y2 = yy;
            else
                y1 = yy;
        }

        c = jump->isCondJump() ? Qt::red : Qt::blue;
        p->fillRect( marg + 6*i, y1, 4, y2, c);
        p->setPen(c.light());
        p->drawLine( marg + 6*i, y1, marg + 6*i, y2);
        p->setPen(c.dark());
        p->drawLine( marg + 6*i +3, y1, marg + 6*i +3, y2);
    }

    // draw start/stop horizontal line
    int x, y = yy-2, w, h = 4;
    if (start >= 0) {
        c = item->jump(start)->isCondJump() ? Qt::red : Qt::blue;
        x = marg + 6*start;
        w = 6*(sv->arrowLevels() - start) + 10;
        p->fillRect( x, y, w, h, c);
        p->setPen(c.light());
        p->drawLine(x, y, x+w-1, y);
        p->drawLine(x, y, x, y+h-1);
        p->setPen(c.dark());
        p->drawLine(x+w-1, y, x+w-1, y+h-1);
        p->drawLine(x+1, y+h-1, x+w-1, y+h-1);
    }
    if (end >= 0) {
        c = item->jump(end)->isCondJump() ? Qt::red : Qt::blue;
        x = marg + 6*end;
        w = 6*(sv->arrowLevels() - end) + 10;

        QPolygon a;
        a.putPoints(0, 8, x,y+h,
                    x,y, x+w-8,y, x+w-8,y-2,
                    x+w,yy,
                    x+w-8,y+h+2, x+w-8,y+h,
                    x,y+h);
        p->setBrush(c);
        p->drawConvexPolygon(a);

        p->setPen(c.light());
        p->drawPolyline(a.constData(), 5);
        p->setPen(c.dark());
        p->drawPolyline(a.constData() + 4, 2);
        p->setPen(c.light());
        p->drawPolyline(a.constData() + 5, 2);
        p->setPen(c.dark());
        p->drawPolyline(a.constData() + 6, 2);
    }

    // draw inner vertical line for start/stop
    // this overwrites borders of horizontal line
    for(int i=0;i< item->jumpCount();i++) {
        TraceLineJump* jump = item->jump(i);
        if (jump == 0) continue;

        c = jump->isCondJump() ? Qt::red : Qt::blue;

        if (jump->lineFrom()->lineno() == lineno) {
            bool drawUp = true;
            if (jump->lineTo()->lineno() == lineno)
                if (start<0) drawUp = false;
            if (jump->lineTo()->lineno() > lineno) drawUp = false;
            if (drawUp)
                p->fillRect( marg + 6*i +1, 0, 2, yy, c);
            else
                p->fillRect( marg + 6*i +1, yy, 2, height-yy, c);
        }
        else if (jump->lineTo()->lineno() == lineno) {
            if (end<0) end = i;
            if (jump->lineFrom()->lineno() < lineno)
                p->fillRect( marg + 6*i +1, 0, 2, yy, c);
            else
                p->fillRect( marg + 6*i +1, yy, 2, height-yy, c);
        }
    }
    p->restore();
}