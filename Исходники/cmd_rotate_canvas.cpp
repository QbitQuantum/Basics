  /**
   * [working thread]
   */
  virtual void onJob()
  {
    UndoTransaction undoTransaction(m_writer.context(), "Rotate Canvas");
    DocumentApi api = m_document->getApi();

    // get all sprite cels
    CelList cels;
    m_sprite->getCels(cels);

    // for each cel...
    for (CelIterator it = cels.begin(); it != cels.end(); ++it) {
      Cel* cel = *it;
      Image* image = m_sprite->getStock()->getImage(cel->getImage());

      // change it location
      switch (m_angle) {
        case 180:
          api.setCelPosition(m_sprite, cel,
                             m_sprite->getWidth() - cel->getX() - image->getWidth(),
                             m_sprite->getHeight() - cel->getY() - image->getHeight());
          break;
        case 90:
          api.setCelPosition(m_sprite, cel,
                             m_sprite->getHeight() - cel->getY() - image->getHeight(),
                             cel->getX());
          break;
        case -90:
          api.setCelPosition(m_sprite, cel,
                             cel->getY(),
                             m_sprite->getWidth() - cel->getX() - image->getWidth());
          break;
      }
    }

    // for each stock's image
    for (int i=0; i<m_sprite->getStock()->size(); ++i) {
      Image* image = m_sprite->getStock()->getImage(i);
      if (!image)
        continue;

      // rotate the image
      Image* new_image = Image::create(image->getPixelFormat(),
                                       m_angle == 180 ? image->getWidth(): image->getHeight(),
                                       m_angle == 180 ? image->getHeight(): image->getWidth());
      raster::rotate_image(image, new_image, m_angle);

      api.replaceStockImage(m_sprite, i, new_image);

      jobProgress((float)i / m_sprite->getStock()->size());

      // cancel all the operation?
      if (isCanceled())
        return;        // UndoTransaction destructor will undo all operations
    }

    // rotate mask
    if (m_document->isMaskVisible()) {
      Mask* origMask = m_document->getMask();
      base::UniquePtr<Mask> new_mask(new Mask());
      const gfx::Rect& origBounds = origMask->getBounds();
      int x = 0, y = 0;

      switch (m_angle) {
        case 180:
          x = m_sprite->getWidth() - origBounds.x - origBounds.w;
          y = m_sprite->getHeight() - origBounds.y - origBounds.h;
          break;
        case 90:
          x = m_sprite->getHeight() - origBounds.y - origBounds.h;
          y = origBounds.x;
          break;
        case -90:
          x = origBounds.y;
          y = m_sprite->getWidth() - origBounds.x - origBounds.w;
          break;
      }

      // create the new rotated mask
      new_mask->replace(x, y,
                        m_angle == 180 ? origBounds.w: origBounds.h,
                        m_angle == 180 ? origBounds.h: origBounds.w);
      raster::rotate_image(origMask->getBitmap(), new_mask->getBitmap(), m_angle);

      // Copy new mask
      api.copyToCurrentMask(new_mask);

      // Regenerate mask
      m_document->resetTransformation();
      m_document->generateMaskBoundaries();
    }

    // change the sprite's size
    if (m_angle != 180)
      api.setSpriteSize(m_sprite, m_sprite->getHeight(), m_sprite->getWidth());

    // commit changes
    undoTransaction.commit();
  }