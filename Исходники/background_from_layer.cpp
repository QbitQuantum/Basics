void BackgroundFromLayer::onExecute()
{
  Layer* layer = this->layer();
  Sprite* sprite = layer->sprite();
  app::Document* doc = static_cast<app::Document*>(sprite->document());
  color_t bgcolor = doc->bgColor();

  // create a temporary image to draw each frame of the new
  // `Background' layer
  ImageRef bg_image(Image::create(sprite->pixelFormat(),
      sprite->width(),
      sprite->height()));

  CelList cels;
  layer->getCels(cels);
  for (Cel* cel : cels) {
    // get the image from the sprite's stock of images
    Image* cel_image = cel->image();
    ASSERT(cel_image);

    clear_image(bg_image.get(), bgcolor);
    render::composite_image(
      bg_image.get(), cel_image,
      sprite->palette(cel->frame()),
      cel->x(), cel->y(),
      MID(0, cel->opacity(), 255),
      static_cast<LayerImage*>(layer)->blendMode());

    // now we have to copy the new image (bg_image) to the cel...
    executeAndAdd(new cmd::SetCelPosition(cel, 0, 0));

    // change opacity to 255
    if (cel->opacity() < 255)
      executeAndAdd(new cmd::SetCelOpacity(cel, 255));

    // same size of cel-image and bg-image
    if (bg_image->width() == cel_image->width() &&
        bg_image->height() == cel_image->height()) {
      executeAndAdd(new CopyRect(cel_image, bg_image.get(),
          gfx::Clip(0, 0, cel_image->bounds())));
    }
    else {
      ImageRef bg_image2(Image::createCopy(bg_image.get()));
      executeAndAdd(new cmd::ReplaceImage(sprite, cel->imageRef(), bg_image2));
    }
  }

  // Fill all empty cels with a flat-image filled with bgcolor
  for (frame_t frame(0); frame<sprite->totalFrames(); ++frame) {
    Cel* cel = layer->cel(frame);
    if (!cel) {
      ImageRef cel_image(Image::create(sprite->pixelFormat(),
          sprite->width(), sprite->height()));
      clear_image(cel_image.get(), bgcolor);

      // Create the new cel and add it to the new background layer
      cel = new Cel(frame, cel_image);
      executeAndAdd(new cmd::AddCel(layer, cel));
    }
  }

  executeAndAdd(new cmd::ConfigureBackground(layer));
}