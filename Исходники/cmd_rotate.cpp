  // [working thread]
  virtual void onJob()
  {
    Transaction transaction(m_writer.context(), "Rotate Canvas");
    DocumentApi api = m_document->getApi(transaction);

    // 1) Rotate cel positions
    for (Cel* cel : m_cels) {
      Image* image = cel->image();
      if (!image)
        continue;

      switch (m_angle) {
        case 180:
          api.setCelPosition(m_sprite, cel,
            m_sprite->width() - cel->x() - image->width(),
            m_sprite->height() - cel->y() - image->height());
          break;
        case 90:
          api.setCelPosition(m_sprite, cel,
            m_sprite->height() - cel->y() - image->height(),
            cel->x());
          break;
        case -90:
          api.setCelPosition(m_sprite, cel,
            cel->y(),
            m_sprite->width() - cel->x() - image->width());
          break;
      }
    }

    // 2) Rotate images
    int i = 0;
    for (Cel* cel : m_cels) {
      Image* image = cel->image();
      if (image) {
        ImageRef new_image(Image::create(image->pixelFormat(),
            m_angle == 180 ? image->width(): image->height(),
            m_angle == 180 ? image->height(): image->width()));
        doc::rotate_image(image, new_image.get(), m_angle);

        api.replaceImage(m_sprite, cel->imageRef(), new_image);
      }

      jobProgress((float)i / m_cels.size());
      ++i;

      // cancel all the operation?
      if (isCanceled())
        return;        // Transaction destructor will undo all operations
    }

    // rotate mask
    if (m_document->isMaskVisible()) {
      Mask* origMask = m_document->mask();
      base::UniquePtr<Mask> new_mask(new Mask());
      const gfx::Rect& origBounds = origMask->bounds();
      int x = 0, y = 0;

      switch (m_angle) {
        case 180:
          x = m_sprite->width() - origBounds.x - origBounds.w;
          y = m_sprite->height() - origBounds.y - origBounds.h;
          break;
        case 90:
          x = m_sprite->height() - origBounds.y - origBounds.h;
          y = origBounds.x;
          break;
        case -90:
          x = origBounds.y;
          y = m_sprite->width() - origBounds.x - origBounds.w;
          break;
      }

      // create the new rotated mask
      new_mask->replace(
        gfx::Rect(x, y,
          m_angle == 180 ? origBounds.w: origBounds.h,
          m_angle == 180 ? origBounds.h: origBounds.w));
      doc::rotate_image(origMask->bitmap(), new_mask->bitmap(), m_angle);

      // Copy new mask
      api.copyToCurrentMask(new_mask);

      // Regenerate mask
      m_document->resetTransformation();
      m_document->generateMaskBoundaries();
    }

    // change the sprite's size
    if (m_rotateSprite && m_angle != 180)
      api.setSpriteSize(m_sprite, m_sprite->height(), m_sprite->width());

    // commit changes
    transaction.commit();
  }