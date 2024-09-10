void CanvasSizeCommand::onExecute(Context* context)
{
  const ContextReader reader(context);
  const Sprite* sprite(reader.sprite());

  if (context->isUiAvailable()) {
    // load the window widget
    base::UniquePtr<CanvasSizeWindow> window(new CanvasSizeWindow(0, 0, 0, 0));

    window->remapWindow();
    window->centerWindow();

    load_window_pos(window, "CanvasSize");
    window->setVisible(true);
    window->openWindowInForeground();
    save_window_pos(window, "CanvasSize");

    if (!window->pressedOk())
      return;

    m_left   = window->getLeft();
    m_right  = window->getRight();
    m_top    = window->getTop();
    m_bottom = window->getBottom();
  }

  // Resize canvas

  int x1 = -m_left;
  int y1 = -m_top;
  int x2 = sprite->width() + m_right;
  int y2 = sprite->height() + m_bottom;

  if (x2 <= x1) x2 = x1+1;
  if (y2 <= y1) y2 = y1+1;

  {
    ContextWriter writer(reader);
    Document* document = writer.document();
    Sprite* sprite = writer.sprite();
    UndoTransaction undoTransaction(writer.context(), "Canvas Size");
    DocumentApi api = document->getApi();
    raster::color_t bgcolor = color_utils::color_for_target(
      context->settings()->getBgColor(),
      ColorTarget(
        ColorTarget::BackgroundLayer,
        sprite->pixelFormat(),
        sprite->transparentColor()));

    api.cropSprite(sprite, gfx::Rect(x1, y1, x2-x1, y2-y1), bgcolor);
    undoTransaction.commit();

    document->generateMaskBoundaries();
    update_screen_for_document(document);
  }
}