void ImportSpriteSheetCommand::onExecute(Context* context)
{
  ImportSpriteSheetWindow window(context);

  window.openWindowInForeground();
  if (!window.ok())
    return;

  Doc* document = window.document();
  DocumentPreferences* docPref = window.docPref();
  gfx::Rect frameBounds = window.frameBounds();
  gfx::Size padThickness = window.paddingThickness();
  bool partialTiles = window.partialTilesValue();
  bool paddingEnable = window.paddingEnabledValue();
  auto sheetType = window.sheetTypeValue();

  ASSERT(document);
  if (!document)
    return;

  // The list of frames imported from the sheet
  std::vector<ImageRef> animation;

  try {
    Sprite* sprite = document->sprite();
    frame_t currentFrame = context->activeSite().frame();
    render::Render render;
    render.setNewBlend(Preferences::instance().experimental.newBlend());

    // Each sprite in the sheet
    std::vector<gfx::Rect> tileRects;
    int widthStop = sprite->width();
    int heightStop = sprite->height();
    if (partialTiles) {
      widthStop += frameBounds.w-1;
      heightStop += frameBounds.h-1;
    }

    switch (sheetType) {
      case app::SpriteSheetType::Horizontal:
        for (int x=frameBounds.x; x+frameBounds.w<=widthStop; x+=frameBounds.w+padThickness.w) {
          tileRects.push_back(gfx::Rect(x, frameBounds.y, frameBounds.w, frameBounds.h));
        }
        break;
      case app::SpriteSheetType::Vertical:
        for (int y=frameBounds.y; y+frameBounds.h<=heightStop; y+=frameBounds.h+padThickness.h) {
          tileRects.push_back(gfx::Rect(frameBounds.x, y, frameBounds.w, frameBounds.h));
        }
        break;
      case app::SpriteSheetType::Rows:
        for (int y=frameBounds.y; y+frameBounds.h<=heightStop; y+=frameBounds.h+padThickness.h) {
          for (int x=frameBounds.x; x+frameBounds.w<=widthStop; x+=frameBounds.w+padThickness.w) {
            tileRects.push_back(gfx::Rect(x, y, frameBounds.w, frameBounds.h));
          }
        }
        break;
      case app::SpriteSheetType::Columns:
        for (int x=frameBounds.x; x+frameBounds.w<=widthStop; x+=frameBounds.w+padThickness.w) {
          for (int y=frameBounds.y; y+frameBounds.h<=heightStop; y+=frameBounds.h+padThickness.h) {
            tileRects.push_back(gfx::Rect(x, y, frameBounds.w, frameBounds.h));
          }
        }
        break;
    }

    // As first step, we cut each tile and add them into "animation" list.
    for (const auto& tileRect : tileRects) {
      ImageRef resultImage(
        Image::create(
          sprite->pixelFormat(), tileRect.w, tileRect.h));

      // Render the portion of sheet.
      render.renderSprite(
        resultImage.get(), sprite, currentFrame,
        gfx::Clip(0, 0, tileRect));

      animation.push_back(resultImage);
    }

    if (animation.size() == 0) {
      Alert::show(Strings::alerts_empty_rect_importing_sprite_sheet());
      return;
    }

    // The following steps modify the sprite, so we wrap all
    // operations in a undo-transaction.
    ContextWriter writer(context);
    Tx tx(writer.context(), "Import Sprite Sheet", ModifyDocument);
    DocApi api = document->getApi(tx);

    // Add the layer in the sprite.
    LayerImage* resultLayer = api.newLayer(sprite->root(), "Sprite Sheet");

    // Add all frames+cels to the new layer
    for (size_t i=0; i<animation.size(); ++i) {
      // Create the cel.
      std::unique_ptr<Cel> resultCel(new Cel(frame_t(i), animation[i]));

      // Add the cel in the layer.
      api.addCel(resultLayer, resultCel.get());
      resultCel.release();
    }

    // Copy the list of layers (because we will modify it in the iteration).
    LayerList layers = sprite->root()->layers();

    // Remove all other layers
    for (Layer* child : layers) {
      if (child != resultLayer)
        api.removeLayer(child);
    }

    // Change the number of frames
    api.setTotalFrames(sprite, frame_t(animation.size()));

    // Set the size of the sprite to the tile size.
    api.setSpriteSize(sprite, frameBounds.w, frameBounds.h);

    tx.commit();

    ASSERT(docPref);
    if (docPref) {
      docPref->importSpriteSheet.type(sheetType);
      docPref->importSpriteSheet.bounds(frameBounds);
      docPref->importSpriteSheet.partialTiles(partialTiles);
      docPref->importSpriteSheet.paddingBounds(padThickness);
      docPref->importSpriteSheet.paddingEnabled(paddingEnable);
    }
  }
  catch (...) {
    throw;
  }

  update_screen_for_document(document);
}