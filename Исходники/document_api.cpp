void DocumentApi::backgroundFromLayer(LayerImage* layer, int bgcolor)
{
  ASSERT(layer);
  ASSERT(layer->isImage());
  ASSERT(layer->isReadable());
  ASSERT(layer->isWritable());
  ASSERT(layer->getSprite() != NULL);
  ASSERT(layer->getSprite()->getBackgroundLayer() == NULL);

  DocumentUndo* undo = m_document->getUndo();
  Sprite* sprite = layer->getSprite();

  // create a temporary image to draw each frame of the new
  // `Background' layer
  UniquePtr<Image> bg_image_wrap(Image::create(sprite->getPixelFormat(),
                                               sprite->getWidth(),
                                               sprite->getHeight()));
  Image* bg_image = bg_image_wrap.get();

  CelIterator it = layer->getCelBegin();
  CelIterator end = layer->getCelEnd();

  for (; it != end; ++it) {
    Cel* cel = *it;
    ASSERT((cel->getImage() > 0) &&
           (cel->getImage() < sprite->getStock()->size()));

    // get the image from the sprite's stock of images
    Image* cel_image = sprite->getStock()->getImage(cel->getImage());
    ASSERT(cel_image);

    image_clear(bg_image, bgcolor);
    image_merge(bg_image, cel_image,
                cel->getX(),
                cel->getY(),
                MID(0, cel->getOpacity(), 255),
                layer->getBlendMode());

    // now we have to copy the new image (bg_image) to the cel...
    setCelPosition(sprite, cel, 0, 0);

    // same size of cel-image and bg-image
    if (bg_image->w == cel_image->w &&
        bg_image->h == cel_image->h) {
      if (undo->isEnabled())
        m_undoers->pushUndoer(new undoers::ImageArea(getObjects(),
            cel_image, 0, 0, cel_image->w, cel_image->h));

      image_copy(cel_image, bg_image, 0, 0);
    }
    else {
      replaceStockImage(sprite, cel->getImage(), Image::createCopy(bg_image));
    }
  }

  // Fill all empty cels with a flat-image filled with bgcolor
  for (FrameNumber frame(0); frame<sprite->getTotalFrames(); ++frame) {
    Cel* cel = layer->getCel(frame);
    if (!cel) {
      Image* cel_image = Image::create(sprite->getPixelFormat(), sprite->getWidth(), sprite->getHeight());
      image_clear(cel_image, bgcolor);

      // Add the new image in the stock
      int image_index = addImageInStock(sprite, cel_image);

      // Create the new cel and add it to the new background layer
      cel = new Cel(frame, image_index);
      addCel(layer, cel);
    }
  }

  configureLayerAsBackground(layer);
}