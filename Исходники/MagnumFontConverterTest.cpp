void MagnumFontConverterTest::exportFont() {
    /* Remove previously created files */
    Utility::Directory::rm(Utility::Directory::join(MAGNUMFONTCONVERTER_TEST_WRITE_DIR, "font.conf"));
    Utility::Directory::rm(Utility::Directory::join(MAGNUMFONTCONVERTER_TEST_WRITE_DIR, "font.tga"));

    /* Open font */
    FreeTypeFont font;
    CORRADE_VERIFY(font.openFile(Utility::Directory::join(FREETYPEFONT_TEST_DIR, "Oxygen.ttf"), 16.0f));

    /* Create fake cache */
    MAGNUM_ASSERT_EXTENSION_SUPPORTED(Extensions::GL::ARB::texture_rg);
    GlyphCache cache(TextureFormat::R8, Vector2i(1536), Vector2i(256), Vector2i(24));
    cache.insert(font.glyphId(U'W'), {25, 34}, {{0, 8}, {16, 128}});
    cache.insert(font.glyphId(U'e'), {25, 12}, {{16, 4}, {64, 32}});

    /* Convert the file */
    MagnumFontConverter converter;
    converter.exportFontToFile(font, cache, Utility::Directory::join(MAGNUMFONTCONVERTER_TEST_WRITE_DIR, "font"), "Wave");

    /* Verify font parameters */
    /** @todo This might behave differently elsewhere due to unspecified order of glyphs in cache */
    CORRADE_COMPARE_AS(Utility::Directory::join(MAGNUMFONTCONVERTER_TEST_WRITE_DIR, "font.conf"),
                       Utility::Directory::join(MAGNUMFONT_TEST_DIR, "font.conf"),
                       TestSuite::Compare::File);

    /* Verify font image, no need to test image contents, as the image is garbage anyway */
    Trade::TgaImporter importer;
    CORRADE_VERIFY(importer.openFile(Utility::Directory::join(MAGNUMFONTCONVERTER_TEST_WRITE_DIR, "font.tga")));
    std::optional<Trade::ImageData2D> image = importer.image2D(0);
    CORRADE_VERIFY(image);
    CORRADE_COMPARE(image->size(), Vector2i(256));
    CORRADE_COMPARE(image->format(), ImageFormat::Red);
    CORRADE_COMPARE(image->type(), ImageType::UnsignedByte);
}