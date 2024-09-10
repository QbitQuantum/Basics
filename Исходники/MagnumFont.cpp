std::pair<Float, Float> MagnumFont::doOpenFile(const std::string& filename, Float) {
    /* Open the configuration file */
    Utility::Configuration conf(filename, Utility::Configuration::Flag::ReadOnly|Utility::Configuration::Flag::SkipComments);
    if(!conf.isValid() || conf.isEmpty()) {
        Error() << "Text::MagnumFont::openFile(): cannot open file" << filename << conf.isValid();
        return {};
    }

    /* Check version */
    if(conf.value<UnsignedInt>("version") != 1) {
        Error() << "Text::MagnumFont::openFile(): unsupported file version, expected 1 but got"
                << conf.value<UnsignedInt>("version");
        return {};
    }

    /* Open and load image file */
    const std::string imageFilename = Utility::Directory::join(Utility::Directory::path(filename), conf.value("image"));
    Trade::TgaImporter importer;
    if(!importer.openFile(imageFilename)) {
        Error() << "Text::MagnumFont::openFile(): cannot open image file" << imageFilename;
        return {};
    }
    std::optional<Trade::ImageData2D> image = importer.image2D(0);
    if(!image) {
        Error() << "Text::MagnumFont::openFile(): cannot load image file";
        return {};
    }

    return openInternal(std::move(conf), std::move(*image));
}