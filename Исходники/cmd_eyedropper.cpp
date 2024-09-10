void EyedropperCommand::onExecute(Context* context)
{
  Widget* widget = ui::Manager::getDefault()->getMouse();
  if (!widget || widget->type != editor_type())
    return;

  Editor* editor = static_cast<Editor*>(widget);
  Sprite* sprite = editor->getSprite();
  if (!sprite)
    return;

  // pixel position to get
  int x, y;
  editor->screenToEditor(jmouse_x(0), jmouse_y(0), &x, &y);

  // get the color from the image
  Color color = Color::fromImage(sprite->getPixelFormat(),
                                 sprite->getPixel(x, y));

  // TODO replace the color in the "context", not directly from the color-bar

  // set the color of the color-bar
  if (m_background)
    ColorBar::instance()->setBgColor(color);
  else
    ColorBar::instance()->setFgColor(color);
}