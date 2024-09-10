namespace Magnum { namespace Text { namespace Test {

class MagnumFontConverterGLTest: public Magnum::Test::AbstractOpenGLTester {
    public:
        explicit MagnumFontConverterGLTest();

        void exportFont();
};

MagnumFontConverterGLTest::MagnumFontConverterGLTest() {
    addTests({&MagnumFontConverterGLTest::exportFont});
}

void MagnumFontConverterGLTest::exportFont() {
    /* Remove previously created files */
    Utility::Directory::rm(Utility::Directory::join(MAGNUMFONTCONVERTER_TEST_WRITE_DIR, "font.conf"));
    Utility::Directory::rm(Utility::Directory::join(MAGNUMFONTCONVERTER_TEST_WRITE_DIR, "font.tga"));

    /* Fake font with fake cache */
    class FakeFont: public Text::AbstractFont {
        public:
            explicit FakeFont(): _opened(false) {}

        private:
            void doClose() { _opened = false; }
            bool doIsOpened() const { return _opened; }
            std::pair<Float, Float> doOpenFile(const std::string&, Float) {
                _opened = true;
                return {16.0f, 39.7333f};
            }
            Features doFeatures() const { return {}; }
            std::unique_ptr<AbstractLayouter> doLayout(const GlyphCache&, Float, const std::string&) { return nullptr; }

            UnsignedInt doGlyphId(const char32_t character) {
                switch(character) {
                    case 'W': return 2;
                    case 'e': return 1;
                }

                return 0;
            }

            Vector2 doGlyphAdvance(const UnsignedInt glyph) {
                switch(glyph) {
                    case 0: return {8, 0};
                    case 1: return {12, 0};
                    case 2: return {23, 0};
                }

                CORRADE_ASSERT_UNREACHABLE();
            }

            bool _opened;
    } font;
    font.openFile({}, {});

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
    CORRADE_COMPARE(image->format(), ColorFormat::Red);
    CORRADE_COMPARE(image->type(), ColorType::UnsignedByte);
}

}}}