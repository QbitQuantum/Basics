// Draws the brush cursor in the specified absolute mouse position
// given in 'pos' param.  Warning: You should clean the cursor before
// to use this routine with other editor.
void BrushPreview::show(const gfx::Point& screenPos)
{
  if (m_onScreen)
    hide();

  app::Document* document = m_editor->document();
  Sprite* sprite = m_editor->sprite();
  Layer* layer = m_editor->layer();
  ASSERT(sprite);

  // Get drawable region
  m_editor->getDrawableRegion(m_clippingRegion, ui::Widget::kCutTopWindows);

  // Remove the invalidated region in the editor.
  m_clippingRegion.createSubtraction(m_clippingRegion,
                                     m_editor->getUpdateRegion());

  // Get cursor color
  const auto& pref = Preferences::instance();
  app::Color app_cursor_color = pref.editor.cursorColor();
  gfx::Color ui_cursor_color = color_utils::color_for_ui(app_cursor_color);
  m_blackAndWhiteNegative = (app_cursor_color.getType() == app::Color::MaskType);

  // Cursor in the screen (view)
  m_screenPosition = screenPos;

  // Get cursor position in the editor
  gfx::Point spritePos = m_editor->screenToEditor(screenPos);

  // Get the current tool
  tools::Ink* ink = m_editor->getCurrentEditorInk();

  bool isFloodfill = m_editor->getCurrentEditorTool()->getPointShape(0)->isFloodFill();

  // Setup the cursor type depending on several factors (current tool,
  // foreground color, layer transparency, brush size, etc.).
  Brush* brush = getCurrentBrush();
  color_t brush_color = getBrushColor(sprite, layer);
  color_t mask_index = sprite->transparentColor();

  if (ink->isSelection() || ink->isSlice()) {
    m_type = SELECTION_CROSS;
  }
  else if (
    (brush->type() == kImageBrushType ||
     brush->size() > 1.0 / m_editor->zoom().scale()) &&
    (// Use cursor bounds for inks that are effects (eraser, blur, etc.)
     (ink->isEffect()) ||
     // or when the brush color is transparent and we are not in the background layer
     (!ink->isShading() &&
      (layer && !layer->isBackground()) &&
      ((sprite->pixelFormat() == IMAGE_INDEXED && brush_color == mask_index) ||
       (sprite->pixelFormat() == IMAGE_RGB && rgba_geta(brush_color) == 0) ||
       (sprite->pixelFormat() == IMAGE_GRAYSCALE && graya_geta(brush_color) == 0))))) {
    m_type = BRUSH_BOUNDARIES;
  }
  else {
    m_type = CROSS;
  }

  bool usePreview = false;

  auto brushPreview = pref.editor.brushPreview();
  if (!m_editor->docPref().show.brushPreview())
    brushPreview = app::gen::BrushPreview::NONE;

  switch (brushPreview) {
    case app::gen::BrushPreview::NONE:
      m_type = CROSS;
      break;
    case app::gen::BrushPreview::EDGES:
      m_type = BRUSH_BOUNDARIES;
      break;
    case app::gen::BrushPreview::FULL:
      usePreview = m_editor->getState()->requireBrushPreview();
      break;
  }

  // For cursor type 'bounds' we have to generate cursor boundaries
  if (m_type & BRUSH_BOUNDARIES)
    generateBoundaries();

  // Draw pixel/brush preview
  if ((m_type & CROSS) && usePreview) {
    gfx::Rect origBrushBounds = (isFloodfill ? gfx::Rect(0, 0, 1, 1): brush->bounds());
    gfx::Rect brushBounds = origBrushBounds;
    brushBounds.offset(spritePos);

    // Create the extra cel to show the brush preview
    Site site = m_editor->getSite();
    Cel* cel = site.cel();

    int t, opacity = 255;
    if (cel) opacity = MUL_UN8(opacity, cel->opacity(), t);
    if (layer) opacity = MUL_UN8(opacity, static_cast<LayerImage*>(layer)->opacity(), t);

    if (!m_extraCel)
      m_extraCel.reset(new ExtraCel);
    m_extraCel->create(document->sprite(), brushBounds, site.frame(), opacity);
    m_extraCel->setType(render::ExtraType::NONE);
    m_extraCel->setBlendMode(
      (layer ? static_cast<LayerImage*>(layer)->blendMode():
               BlendMode::NORMAL));

    document->setExtraCel(m_extraCel);

    Image* extraImage = m_extraCel->image();
    extraImage->setMaskColor(mask_index);
    clear_image(extraImage,
                (extraImage->pixelFormat() == IMAGE_INDEXED ? mask_index: 0));

    if (layer) {
      render::Render().renderLayer(
        extraImage, layer, site.frame(),
        gfx::Clip(0, 0, brushBounds),
        BlendMode::SRC);

      // This extra cel is a patch for the current layer/frame
      m_extraCel->setType(render::ExtraType::PATCH);
    }

    {
      base::UniquePtr<tools::ToolLoop> loop(
        create_tool_loop_preview(
          m_editor, extraImage,
          brushBounds.origin()));
      if (loop) {
        loop->getInk()->prepareInk(loop);
        loop->getIntertwine()->prepareIntertwine();
        loop->getController()->prepareController(ui::kKeyNoneModifier);
        loop->getPointShape()->preparePointShape(loop);
        loop->getPointShape()->transformPoint(
          loop, -origBrushBounds.x, -origBrushBounds.y);
      }
    }

    document->notifySpritePixelsModified(
      sprite, gfx::Region(m_lastBounds = brushBounds),
      m_lastFrame = site.frame());

    m_withRealPreview = true;
  }

  // Save area and draw the cursor
  {
    ui::ScreenGraphics g;
    ui::SetClip clip(&g, gfx::Rect(0, 0, g.width(), g.height()));

    forEachBrushPixel(&g, m_screenPosition, spritePos, ui_cursor_color, &BrushPreview::savePixelDelegate);
    forEachBrushPixel(&g, m_screenPosition, spritePos, ui_cursor_color, &BrushPreview::drawPixelDelegate);
  }

  // Cursor in the editor (model)
  m_onScreen = true;
  m_editorPosition = spritePos;

  // Save the clipping-region to know where to clean the pixels
  m_oldClippingRegion = m_clippingRegion;
}