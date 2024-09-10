void FreeTypeFontTest::layout() {
    FreeTypeFont font;
    CORRADE_VERIFY(font.openFile(Utility::Directory::join(FREETYPEFONT_TEST_DIR, "Oxygen.ttf"), 16.0f));

    /* Fill the cache with some fake glyphs */
    GlyphCache cache(Vector2i(256));
    cache.insert(font.glyphId(U'W'), {25, 34}, {{0, 8}, {16, 128}});
    cache.insert(font.glyphId(U'e'), {25, 12}, {{16, 4}, {64, 32}});

    std::unique_ptr<AbstractLayouter> layouter = font.layout(cache, 0.5f, "Wave");
    CORRADE_VERIFY(layouter);
    CORRADE_COMPARE(layouter->glyphCount(), 4);

    Vector2 cursorPosition;
    Rectangle rectangle;
    Rectangle position;
    Rectangle textureCoordinates;

    /* 'W' */
    std::tie(position, textureCoordinates) = layouter->renderGlyph(0, cursorPosition = {}, rectangle);
    CORRADE_COMPARE(position, Rectangle({0.78125f, 1.0625f}, {1.28125f, 4.8125f}));
    CORRADE_COMPARE(textureCoordinates, Rectangle({0, 0.03125f}, {0.0625f, 0.5f}));
    CORRADE_COMPARE(cursorPosition, Vector2(0.71875f, 0.0f));

    /* 'a' (not in cache) */
    std::tie(position, textureCoordinates) = layouter->renderGlyph(1, cursorPosition = {}, rectangle);
    CORRADE_COMPARE(position, Rectangle());
    CORRADE_COMPARE(textureCoordinates, Rectangle());
    CORRADE_COMPARE(cursorPosition, Vector2(0.34375f, 0.0f));

    /* 'v' (not in cache) */
    std::tie(position, textureCoordinates) = layouter->renderGlyph(2, cursorPosition = {}, rectangle);
    CORRADE_COMPARE(position, Rectangle());
    CORRADE_COMPARE(textureCoordinates, Rectangle());
    CORRADE_COMPARE(cursorPosition, Vector2(0.34375f, 0.0f));

    /* 'e' */
    std::tie(position, textureCoordinates) = layouter->renderGlyph(3, cursorPosition = {}, rectangle);
    CORRADE_COMPARE(position, Rectangle({0.78125f, 0.375f}, {2.28125f, 1.25f}));
    CORRADE_COMPARE(textureCoordinates, Rectangle({0.0625f, 0.015625f}, {0.25f, 0.125f}));
    CORRADE_COMPARE(cursorPosition, Vector2(0.375f, 0.0f));
}