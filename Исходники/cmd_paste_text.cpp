void PasteTextCommand::onExecute(Context* ctx)
{
  Editor* editor = current_editor;
  if (editor == NULL)
    return;

  Preferences& pref = Preferences::instance();
  PasteTextWindow window(pref.textTool.fontFace(),
                         pref.textTool.fontSize(),
                         pref.textTool.antialias(),
                         pref.colorBar.fgColor());

  window.userText()->setText(last_text_used);

  window.openWindowInForeground();
  if (window.closer() != window.ok())
    return;

  last_text_used = window.userText()->text();

  bool antialias = window.antialias()->isSelected();
  std::string faceName = window.faceValue();
  int size = window.sizeValue();
  size = MID(1, size, 999);
  pref.textTool.fontFace(faceName);
  pref.textTool.fontSize(size);
  pref.textTool.antialias(antialias);

  try {
    std::string text = window.userText()->text();
    app::Color appColor = window.fontColor()->getColor();
    doc::color_t color = doc::rgba(appColor.getRed(),
                                   appColor.getGreen(),
                                   appColor.getBlue(),
                                   appColor.getAlpha());

    doc::ImageRef image(render_text(faceName, size, text, color, antialias));
    if (image) {
      Sprite* sprite = editor->sprite();
      if (image->pixelFormat() != sprite->pixelFormat()) {
        RgbMap* rgbmap = sprite->rgbMap(editor->frame());
        image.reset(
          render::convert_pixel_format(
            image.get(), NULL, sprite->pixelFormat(),
            render::DitheringAlgorithm::None,
            render::DitheringMatrix(),
            rgbmap, sprite->palette(editor->frame()),
            false, 0));
      }

      editor->pasteImage(image.get());
    }
  }
  catch (const std::exception& ex) {
    ui::Alert::show(PACKAGE
                    "<<%s"
                    "||&OK", ex.what());
  }
}