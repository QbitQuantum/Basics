ImagePtr MagickImageLoader::load(Magick::Image& image) {
    Magick::Blob blob;
    convertColorSpace(image);
    convertImageToDib(image, blob);
    ImagePtr res = makeImage(blob);
    res->setSize(Size(image.size().width(), image.size().height()));
    return res;
}