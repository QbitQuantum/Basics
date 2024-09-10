static void drawTextCommon(GraphicsContext* ctx, const TextRun& run, const FloatPoint& point, int from, int to, const QFont& font, bool isComplexText)
{
    if (to < 0)
        to = run.length();

    QPainter *p = ctx->platformContext();

    QPen textFillPen;
    if (ctx->textDrawingMode() & cTextFill) {
        if (ctx->fillGradient()) {
            QBrush brush(*ctx->fillGradient()->platformGradient());
            brush.setTransform(ctx->fillGradient()->gradientSpaceTransform());
            textFillPen = QPen(brush, 0);
        } else if (ctx->fillPattern()) {
            AffineTransform affine;
            textFillPen = QPen(QBrush(ctx->fillPattern()->createPlatformPattern(affine)), 0);
        } else
            textFillPen = QPen(QColor(ctx->fillColor()));
    }

    QPen textStrokePen;
    if (ctx->textDrawingMode() & cTextStroke) {
        if (ctx->strokeGradient()) {
            QBrush brush(*ctx->strokeGradient()->platformGradient());
            brush.setTransform(ctx->strokeGradient()->gradientSpaceTransform());
            textStrokePen = QPen(brush, ctx->strokeThickness());
        } else if (ctx->strokePattern()) {
            AffineTransform affine;
            QBrush brush(ctx->strokePattern()->createPlatformPattern(affine));
            textStrokePen = QPen(brush, ctx->strokeThickness());
        } else
            textStrokePen = QPen(QColor(ctx->strokeColor()), ctx->strokeThickness());
    }

    String sanitized = Font::normalizeSpaces(String(run.characters(), run.length()));
    QString string = fromRawDataWithoutRef(sanitized);
    QPointF pt(point.x(), point.y());

    // text shadow
    IntSize shadowSize;
    int shadowBlur;
    Color shadowColor;
    bool hasShadow = ctx->textDrawingMode() == cTextFill && ctx->getShadow(shadowSize, shadowBlur, shadowColor);

    if (from > 0 || to < run.length()) {
        if (isComplexText) {
            QTextLayout layout(string, font);
            QTextLine line = setupLayout(&layout, run);
            float x1 = line.cursorToX(from);
            float x2 = line.cursorToX(to);
            if (x2 < x1)
                qSwap(x1, x2);

            QFontMetrics fm(font);
            int ascent = fm.ascent();
            QRectF clip(fm.boundingRect(string));

            if (hasShadow) {
                // TODO: when blur support is added, the clip will need to account
                // for the blur radius
                qreal dx1 = 0, dx2 = 0, dy1 = 0, dy2 = 0;
                if (shadowSize.width() > 0)
                    dx2 = shadowSize.width();
                else
                    dx1 = -shadowSize.width();
                if (shadowSize.height() > 0)
                    dy2 = shadowSize.height();
                else
                    dy1 = -shadowSize.height();
                // expand the clip rect to include the text shadow as well
                clip.adjust(dx1, dx2, dy1, dy2);
            }
            p->save();
            //p->setClipRect(clip.toRect(), Qt::IntersectClip);
            pt.setY(pt.y() - ascent);
            if (hasShadow) {
                p->save();
                p->setPen(QColor(shadowColor));
                p->translate(shadowSize.width(), shadowSize.height());
                line.draw(p, pt);
                p->restore();
            }
            p->setPen(textFillPen);
            line.draw(p, pt);
            p->restore();
            return;
        }
#if QT_VERSION >= QT_VERSION_CHECK(4, 7, 0)
        int skipWidth = QFontMetrics(font).width(string, from, Qt::TextBypassShaping);
        pt.setX(pt.x() + skipWidth);
        string = fromRawDataWithoutRef(sanitized, from, to - from);
#endif
    }

    p->setFont(font);

    int flags = run.rtl() ? Qt::TextForceRightToLeft : Qt::TextForceLeftToRight;
#if QT_VERSION >= QT_VERSION_CHECK(4, 7, 0)
    // See QWebPagePrivate::QWebPagePrivate() where the default path is set to Complex for Qt 4.6 and earlier.
    if (!isComplexText)
        flags |= Qt::TextBypassShaping;
#endif

    QFontMetrics fm(font);
    QRectF clip(pt.x(), pt.y()-fm.ascent(), fm.width(string, -1, flags), fm.height());

    if (hasShadow) {
        // TODO: text shadow blur support
        p->save();
        p->translate(shadowSize.width(), shadowSize.height());
        //p->setClipRect(clip, Qt::IntersectClip);
        p->setPen(QColor(shadowColor));
        p->drawText(pt, string, flags, run.padding());
        p->restore();
    }
    if (ctx->textDrawingMode() & cTextStroke) {
        QPainterPath path;
        path.addText(pt, font, string);
        p->save();
        //p->setClipRect(clip, Qt::IntersectClip);
        p->setPen(textStrokePen);
        p->strokePath(path, p->pen());
        p->restore();
    }
    if (ctx->textDrawingMode() & cTextFill) {
        p->save();
        //p->setClipRect(clip, Qt::IntersectClip);
        p->setPen(textFillPen);
        p->drawText(pt, string, flags, run.padding());
        p->restore();
    }
}