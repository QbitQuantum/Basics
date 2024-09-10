void ButtonSet::Item::onPaint(ui::PaintEvent& ev)
{
  SkinTheme* theme = static_cast<SkinTheme*>(getTheme());
  Graphics* g = ev.getGraphics();
  gfx::Rect rc = getClientBounds();
  gfx::Color fg, bg;
  SkinPartPtr nw;
  gfx::Rect boxRc, textRc, iconRc;
  gfx::Size iconSize;
  if (m_icon)
    iconSize = m_icon->getSize();

  getTextIconInfo(
    &boxRc, &textRc, &iconRc,
    CENTER | (hasText() ? BOTTOM: MIDDLE),
    iconSize.w, iconSize.h);

  Grid::Info info = buttonSet()->getChildInfo(this);
  bool isLastCol = (info.col+info.hspan >= info.grid_cols);
  bool isLastRow = (info.row+info.vspan >= info.grid_rows);

  if (m_icon || isLastRow) {
    textRc.y -= 1*guiscale();
    iconRc.y -= 1*guiscale();
  }

  if (!gfx::is_transparent(getBgColor()))
    g->fillRect(getBgColor(), g->getClipBounds());

  if (isSelected() || hasMouseOver()) {
    if (hasCapture()) {
      nw = theme->parts.toolbuttonPushed();
      fg = theme->colors.buttonSelectedText();
      bg = theme->colors.buttonSelectedFace();
    }
    else {
      nw = (hasFocus() ? theme->parts.toolbuttonHotFocused():
                         theme->parts.toolbuttonHot());
      fg = theme->colors.buttonHotText();
      bg = theme->colors.buttonHotFace();
    }
  }
  else {
    nw = (hasFocus() ? theme->parts.toolbuttonFocused():
                       theme->parts.toolbuttonLast());
    fg = theme->colors.buttonNormalText();
    bg = theme->colors.buttonNormalFace();
  }

  if (!isLastCol)
    rc.w += 1*guiscale();

  if (!isLastRow) {
    if (nw == theme->parts.toolbuttonHotFocused())
      rc.h += 2*guiscale();
    else
      rc.h += 3*guiscale();
  }

  theme->drawRect(g, rc, nw.get(), bg);

  if (m_icon) {
    if (isSelected() && hasCapture())
      g->drawColoredRgbaSurface(m_icon->getBitmap(0), theme->colors.buttonSelectedText(),
                                iconRc.x, iconRc.y);
    else
      g->drawRgbaSurface(m_icon->getBitmap(0), iconRc.x, iconRc.y);
  }

  if (hasText()) {
    g->setFont(getFont());
    g->drawUIString(getText(), fg, gfx::ColorNone, textRc.getOrigin(),
                    false);
  }
}