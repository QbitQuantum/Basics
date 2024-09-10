void QFontEngineQPF::draw(QPaintEngine *p, qreal _x, qreal _y, const QTextItemInt &si)
{
    QPaintEngineState *pState = p->state;
    QRasterPaintEngine *paintEngine = static_cast<QRasterPaintEngine*>(p);

    QTransform matrix = pState->transform();
    matrix.translate(_x, _y);
    QFixed x = QFixed::fromReal(matrix.dx());
    QFixed y = QFixed::fromReal(matrix.dy());

    QVarLengthArray<QFixedPoint> positions;
    QVarLengthArray<glyph_t> glyphs;
    getGlyphPositions(si.glyphs, si.num_glyphs, matrix, si.flags, glyphs, positions);
    if (glyphs.size() == 0)
        return;

    for(int i = 0; i < glyphs.size(); i++) {
        const Glyph *glyph = findGlyph(glyphs[i]);
        if (!glyph)
            continue;

        const bool mono = false; // ###

        paintEngine->alphaPenBlt(reinterpret_cast<const uchar *>(glyph) + sizeof(Glyph), glyph->bytesPerLine, mono,
                                     qRound(positions[i].x) + glyph->x,
                                     qRound(positions[i].y) + glyph->y,
                                     glyph->width, glyph->height);
    }
}