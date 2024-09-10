void
InfoBoxPreview::on_paint(Canvas &canvas)
{
  const unsigned i = this - previews;
  const bool is_current = i == current_preview;

  if (is_current)
    canvas.clear(COLOR_BLACK);
  else
    canvas.clear_white();

  canvas.hollow_brush();
  canvas.black_pen();
  canvas.rectangle(0, 0, canvas.get_width() - 1, canvas.get_height() - 1);

  unsigned type = data.contents[i];
  const TCHAR *caption = type < InfoBoxFactory::NUM_TYPES
    ? InfoBoxFactory::GetCaption(type)
    : NULL;
  if (caption == NULL)
    caption = _("Invalid");
  else
    caption = gettext(caption);

  canvas.select(Fonts::Title);
  canvas.background_transparent();
  canvas.set_text_color(is_current ? COLOR_WHITE : COLOR_BLACK);
  canvas.text(2, 2, caption);
}