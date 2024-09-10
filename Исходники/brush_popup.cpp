// static
she::Surface* BrushPopup::createSurfaceForBrush(const BrushRef& origBrush)
{
  Image* image = nullptr;
  BrushRef brush = origBrush;
  if (brush) {
    if (brush->type() != kImageBrushType && brush->size() > 10) {
      brush.reset(new Brush(*brush));
      brush->setSize(10);
    }
    image = brush->image();
  }

  she::Surface* surface = she::instance()->createRgbaSurface(
    std::min(10, image ? image->width(): 4),
    std::min(10, image ? image->height(): 4));

  if (image) {
    Palette* palette = get_current_palette();
    if (image->pixelFormat() == IMAGE_BITMAP) {
      palette = new Palette(frame_t(0), 2);
      palette->setEntry(0, rgba(0, 0, 0, 0));
      palette->setEntry(1, rgba(0, 0, 0, 255));
    }

    convert_image_to_surface(
      image, palette, surface,
      0, 0, 0, 0, image->width(), image->height());

    if (image->pixelFormat() == IMAGE_BITMAP)
      delete palette;
  }
  else {
    she::ScopedSurfaceLock lock(surface);
    lock->clear();
  }

  return surface;
}