void GlyphArrangement::draw (const Graphics& g, const AffineTransform& transform) const
{
    for (int i = 0; i < glyphs.size(); ++i)
    {
        const PositionedGlyph* const pg = glyphs.getUnchecked(i);

        if (pg->font.isUnderlined())
        {
            const float lineThickness = (pg->font.getDescent()) * 0.3f;

            float nextX = pg->x + pg->w;

            if (i < glyphs.size() - 1 && glyphs.getUnchecked (i + 1)->y == pg->y)
                nextX = glyphs.getUnchecked (i + 1)->x;

            Path p;
            p.addLineSegment (Line<float> (pg->x, pg->y + lineThickness * 2.0f,
                                           nextX, pg->y + lineThickness * 2.0f),
                              lineThickness);

            g.fillPath (p, transform);
        }

        pg->draw (g, transform);
    }
}