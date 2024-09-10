void WavImporterTest::stereo8() {
    WavImporter importer;
    CORRADE_VERIFY(importer.openFile(Utility::Directory::join(WAVAUDIOIMPORTER_TEST_DIR, "stereo8.wav")));

    CORRADE_COMPARE(importer.format(), Buffer::Format::Stereo8);
    CORRADE_COMPARE(importer.frequency(), 96000);
    Containers::Array<unsigned char> data = importer.data();
    CORRADE_COMPARE(data.size(), 4);
    CORRADE_COMPARE(data[0], 0xde);
    CORRADE_COMPARE(data[1], 0xfe);
    CORRADE_COMPARE(data[2], 0xca);
    CORRADE_COMPARE(data[3], 0x7e);
}