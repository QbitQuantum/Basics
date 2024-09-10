  // [working thread]
  void onJob() override {
    DocumentApi api = writer().document()->getApi(transaction());

    int cels_count = 0;
    for (Cel* cel : sprite()->uniqueCels()) { // TODO add size() member function to CelsRange
      (void)cel;
      ++cels_count;
    }

    // For each cel...
    int progress = 0;
    for (Cel* cel : sprite()->uniqueCels()) {
      // Get cel's image
      Image* image = cel->image();
      if (image && !cel->link()) {
        // Resize the cel bounds only if it's from a reference layer
        if (cel->layer()->isReference()) {
          gfx::RectF newBounds = scale_rect<double>(cel->boundsF());
          transaction().execute(new cmd::SetCelBoundsF(cel, newBounds));
        }
        else {
          // Change its location
          api.setCelPosition(sprite(), cel, scale_x(cel->x()), scale_y(cel->y()));

          // Resize the image
          int w = scale_x(image->width());
          int h = scale_y(image->height());
          ImageRef new_image(Image::create(image->pixelFormat(), MAX(1, w), MAX(1, h)));
          new_image->setMaskColor(image->maskColor());

          doc::algorithm::fixup_image_transparent_colors(image);
          doc::algorithm::resize_image(
            image, new_image.get(),
            m_resize_method,
            sprite()->palette(cel->frame()),
            sprite()->rgbMap(cel->frame()),
            (cel->layer()->isBackground() ? -1: sprite()->transparentColor()));

          api.replaceImage(sprite(), cel->imageRef(), new_image);
        }
      }

      jobProgress((float)progress / cels_count);
      ++progress;

      // Cancel all the operation?
      if (isCanceled())
        return;        // Transaction destructor will undo all operations
    }

    // Resize mask
    if (document()->isMaskVisible()) {
      ImageRef old_bitmap
        (crop_image(document()->mask()->bitmap(), -1, -1,
                    document()->mask()->bitmap()->width()+2,
                    document()->mask()->bitmap()->height()+2, 0));

      int w = scale_x(old_bitmap->width());
      int h = scale_y(old_bitmap->height());
      base::UniquePtr<Mask> new_mask(new Mask);
      new_mask->replace(
        gfx::Rect(
          scale_x(document()->mask()->bounds().x-1),
          scale_y(document()->mask()->bounds().y-1), MAX(1, w), MAX(1, h)));
      algorithm::resize_image(
        old_bitmap.get(), new_mask->bitmap(),
        m_resize_method,
        sprite()->palette(0), // Ignored
        sprite()->rgbMap(0),  // Ignored
        -1);                  // Ignored

      // Reshrink
      new_mask->intersect(new_mask->bounds());

      // Copy new mask
      api.copyToCurrentMask(new_mask);

      // Regenerate mask
      document()->resetTransformation();
      document()->generateMaskBoundaries();
    }

    // Resize slices
    for (auto& slice : sprite()->slices()) {
      for (auto& k : *slice) {
        const SliceKey& key = *k.value();
        if (key.isEmpty())
          continue;

        SliceKey newKey = key;
        newKey.setBounds(scale_rect(newKey.bounds()));

        if (newKey.hasCenter())
          newKey.setCenter(scale_rect(newKey.center()));

        if (newKey.hasPivot())
          newKey.setPivot(gfx::Point(scale_x(newKey.pivot().x),
                                     scale_y(newKey.pivot().y)));

        transaction().execute(
          new cmd::SetSliceKey(slice, k.frame(), newKey));
      }
    }

    // Resize Sprite
    api.setSpriteSize(sprite(), m_new_width, m_new_height);
  }