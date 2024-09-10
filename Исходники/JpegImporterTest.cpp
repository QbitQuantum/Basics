void JpegImporterTest::gray() {
    JpegImporter importer;
    CORRADE_VERIFY(importer.openFile(Utility::Directory::join(JPEGIMPORTER_TEST_DIR, "gray.jpg")));

    std::optional<Trade::ImageData2D> image = importer.image2D(0);
    CORRADE_VERIFY(image);
    CORRADE_COMPARE(image->size(), Vector2i(3, 2));
    #ifndef MAGNUM_TARGET_GLES2
    CORRADE_COMPARE(image->format(), PixelFormat::Red);
    #else
    CORRADE_COMPARE(image->format(), PixelFormat::Luminance);
    #endif
    CORRADE_COMPARE(image->type(), PixelType::UnsignedByte);

    /* The image has four-byte aligned rows, clear the padding to deterministic
       values */
    CORRADE_COMPARE(image->data().size(), 8);
    image->data()[3] = image->data()[7] = 0;

    CORRADE_COMPARE_AS(image->data(), Containers::Array<char>::from(
        '\xff', '\x88', '\x00', 0,
        '\x88', '\x00', '\xff', 0),
        TestSuite::Compare::Container<Containers::ArrayView<const char>>);
}