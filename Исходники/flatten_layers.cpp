void FlattenLayers::onExecute()
{
  Sprite* sprite = this->sprite();
  auto doc = static_cast<Doc*>(sprite->document());

  // Create a temporary image.
  ImageRef image(Image::create(sprite->pixelFormat(),
      sprite->width(),
      sprite->height()));

  LayerImage* flatLayer;  // The layer onto which everything will be flattened.
  color_t     bgcolor;    // The background color to use for flatLayer.

  flatLayer = sprite->backgroundLayer();
  if (flatLayer && flatLayer->isVisible()) {
    // There exists a visible background layer, so we will flatten onto that.
    bgcolor = doc->bgColor(flatLayer);
  }
  else {
    // Create a new transparent layer to flatten everything onto.
    flatLayer = new LayerImage(sprite);
    ASSERT(flatLayer->isVisible());
    executeAndAdd(new cmd::AddLayer(sprite->root(), flatLayer, nullptr));
    executeAndAdd(new cmd::SetLayerName(flatLayer, "Flattened"));
    bgcolor = sprite->transparentColor();
  }

  render::Render render;
  render.setBgType(render::BgType::NONE);

  // Copy all frames to the background.
  for (frame_t frame(0); frame<sprite->totalFrames(); ++frame) {
    // Clear the image and render this frame.
    clear_image(image.get(), bgcolor);
    render.renderSprite(image.get(), sprite, frame);

    // TODO Keep cel links when possible

    ImageRef cel_image;
    Cel* cel = flatLayer->cel(frame);
    if (cel) {
      if (cel->links())
        executeAndAdd(new cmd::UnlinkCel(cel));

      cel_image = cel->imageRef();
      ASSERT(cel_image);

      executeAndAdd(new cmd::CopyRect(cel_image.get(), image.get(),
          gfx::Clip(0, 0, image->bounds())));
    }
    else {
      cel_image.reset(Image::createCopy(image.get()));
      cel = new Cel(frame, cel_image);
      flatLayer->addCel(cel);
    }
  }

  // Delete old layers.
  LayerList layers = sprite->root()->layers();
  for (Layer* layer : layers)
    if (layer != flatLayer)
      executeAndAdd(new cmd::RemoveLayer(layer));
}