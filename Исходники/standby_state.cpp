bool StandbyState::onUpdateStatusBar(Editor* editor)
{
  tools::Tool* current_tool = editor->getCurrentEditorTool();
  Sprite* sprite = editor->getSprite();
  int x, y;

  editor->screenToEditor(jmouse_x(0), jmouse_y(0), &x, &y);

  if (!sprite) {
    app_get_statusbar()->clearText();
  }
  // For eye-dropper
  else if (current_tool->getInk(0)->isEyedropper()) {
    int imgtype = sprite->getImgType();
    uint32_t pixel = sprite->getPixel(x, y);
    Color color = Color::fromImage(imgtype, pixel);

    int alpha = 255;
    switch (imgtype) {
      case IMAGE_RGB: alpha = _rgba_geta(pixel); break;
      case IMAGE_GRAYSCALE: alpha = _graya_geta(pixel); break;
    }

    char buf[256];
    usprintf(buf, "- Pos %d %d", x, y);

    app_get_statusbar()->showColor(0, buf, color, alpha);
  }
  else {
    Mask* mask = editor->getDocument()->getMask();

    app_get_statusbar()->setStatusText
      (0, "Pos %d %d, Size %d %d, Frame %d",
       x, y,
       ((mask && mask->bitmap)? mask->w: sprite->getWidth()),
       ((mask && mask->bitmap)? mask->h: sprite->getHeight()),
       sprite->getCurrentFrame()+1);
  }

  return true;
}