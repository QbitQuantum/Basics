void TgaImporterTest::file() {
    TgaImporter importer;
    const char data[] = {
        0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 3, 0, 8, 0,
        1, 2,
        3, 4,
        5, 6
    };
    CORRADE_VERIFY(importer.openFile(Utility::Directory::join(TGAIMPORTER_TEST_DIR, "file.tga")));

    std::optional<Trade::ImageData2D> image = importer.image2D(0);
    CORRADE_VERIFY(image);
    #ifndef MAGNUM_TARGET_GLES2
    CORRADE_COMPARE(image->format(), ColorFormat::Red);
    #else
    CORRADE_COMPARE(image->format(), ColorFormat::Luminance);
    #endif
    CORRADE_COMPARE(image->size(), Vector2i(2, 3));
    CORRADE_COMPARE(image->type(), ColorType::UnsignedByte);
    CORRADE_COMPARE((std::string{image->data(), 2*3}),
                    (std::string{data + 18, 2*3}));
}