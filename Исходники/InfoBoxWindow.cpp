void
InfoBoxWindow::PaintValue(Canvas &canvas, Color background_color)
{
  if (data.value.empty())
    return;

  canvas.SetTextColor(look.GetValueColor(data.value_color));

  // Do text-based unit rendering on higher resolutions
  if (look.unit_font.IsDefined()) {
    canvas.Select(look.unit_font);
    PixelScalar unit_width =
        UnitSymbolRenderer::GetSize(canvas, data.value_unit).cx;

    canvas.Select(look.value_font);
    int ascent_height = look.value_font.GetAscentHeight();

    PixelSize value_size = canvas.CalcTextSize(data.value);
    if (value_size.cx + unit_width > value_rect.right - value_rect.left) {
      canvas.Select(look.small_value_font);
      ascent_height = look.small_value_font.GetAscentHeight();
      value_size = canvas.CalcTextSize(data.value);
    }

    PixelScalar x = std::max(PixelScalar(0),
                             PixelScalar((value_rect.left + value_rect.right
                                          - value_size.cx - unit_width) / 2));

    PixelScalar y = (value_rect.top + value_rect.bottom - value_size.cy) / 2;

    canvas.TextAutoClipped(x, y, data.value);

    if (unit_width != 0) {
      const int unit_height =
        UnitSymbolRenderer::GetAscentHeight(look.unit_font, data.value_unit);

      canvas.Select(look.unit_font);
      UnitSymbolRenderer::Draw(canvas,
                               { x + value_size.cx,
                                 y + ascent_height - unit_height },
                               data.value_unit, look.unit_fraction_pen);
    }
    return;
  }

  canvas.Select(look.value_font);
  UPixelScalar ascent_height = look.value_font.GetAscentHeight();
  UPixelScalar capital_height = look.value_font.GetCapitalHeight();

  PixelSize unit_size;
  const UnitSymbol *unit_symbol = units_look.GetSymbol(data.value_unit);
  if (unit_symbol != NULL) {
    unit_size = unit_symbol->GetSize();
  } else {
    unit_size.cx = 0;
    unit_size.cy = 0;
  }

  PixelSize value_size = canvas.CalcTextSize(data.value);
  if (value_size.cx + unit_size.cx > value_rect.right - value_rect.left) {
    canvas.Select(look.small_value_font);
    ascent_height = look.small_value_font.GetAscentHeight();
    capital_height = look.small_value_font.GetCapitalHeight();
    value_size = canvas.CalcTextSize(data.value);
  }

  PixelScalar x = std::max(PixelScalar(1),
                           PixelScalar((value_rect.left + value_rect.right
                                        - value_size.cx
                                        - Layout::FastScale(unit_size.cx)) / 2));

  PixelScalar y = value_rect.top + 1 - ascent_height +
    (value_rect.bottom - value_rect.top + capital_height) / 2;

  canvas.TextAutoClipped(x, y, data.value);

  if (unit_symbol != NULL) {
#ifndef HAVE_CLIPPING
    /* sort-of clipping */
    if (x + value_size.cx >= (int)canvas.GetWidth())
      return;
#endif

    unit_symbol->Draw(canvas, x + value_size.cx,
                      y + ascent_height - unit_symbol->GetScreenSize().cy,
                      background_color,
                      look.GetValueColor(data.value_color));
  }
}