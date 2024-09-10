void TransferFunctionEditor::drawGrid(QPainter & painter, int w, int h)
{
  QColor c(128, 128, 128, 128);

  QPen pen(c);
  pen.setWidth(1);

  QBrush brush(c);

  painter.setPen(pen);
  painter.setBrush(brush);

  // vykreslenie samotnej mriezky
  painter.setRenderHint(QPainter::Antialiasing, false);
  painter.setRenderHint(QPainter::HighQualityAntialiasing, false);

  const int vert_step = 20;
  const int horz_step = 10;

  // horizontalne ciary mriezky
  for (int i = INNER_PADDING_BOTTOM; i < h - INNER_PADDING_TOP; i += horz_step)
  {
    painter.drawLine(INNER_PADDING_LEFT, h - i, w - INNER_PADDING_RIGHT, h - i);
  }

  // vertikalne ciary mriezky
  for (int i = INNER_PADDING_LEFT; i < w - INNER_PADDING_RIGHT; i += vert_step)
  {
    painter.drawLine(i, INNER_PADDING_TOP, i, h - INNER_PADDING_BOTTOM);
  }

  painter.setRenderHint(QPainter::Antialiasing, true);
  painter.setRenderHint(QPainter::HighQualityAntialiasing, true);

  pen.setWidth(2);
  painter.setPen(pen);

  // vykreslenie horizontalnej osi
  const QPointF triangle_horz[3] = {
    QPointF(w - INNER_PADDING_RIGHT + EXTRA_INNNER_PADDING_RIGHT,                   h - INNER_PADDING_BOTTOM - 2.5f),
    QPointF(w - INNER_PADDING_RIGHT + EXTRA_INNNER_PADDING_RIGHT + AXIS_ARROW_SIZE, h - INNER_PADDING_BOTTOM + 0.0f),
    QPointF(w - INNER_PADDING_RIGHT + EXTRA_INNNER_PADDING_RIGHT,                   h - INNER_PADDING_BOTTOM + 2.5f)
  };

  painter.drawLine(INNER_PADDING_LEFT, h - INNER_PADDING_BOTTOM, w - INNER_PADDING_RIGHT + EXTRA_INNNER_PADDING_RIGHT, h - INNER_PADDING_BOTTOM);
  painter.drawPolygon(triangle_horz, 3);

  // vykreslenie vertikalnej osi
  const QPointF triangle_vert[3] = {
    //                       x      y
    QPointF(INNER_PADDING_LEFT - 2.5f, INNER_PADDING_TOP - EXTRA_INNNER_PADDING_TOP), // lavy bod
    QPointF(INNER_PADDING_LEFT + 2.5f, INNER_PADDING_TOP - EXTRA_INNNER_PADDING_TOP), // pravy bod
    QPointF(INNER_PADDING_LEFT + 0.0f, INNER_PADDING_TOP - EXTRA_INNNER_PADDING_TOP - AXIS_ARROW_SIZE)  // stredny bod
  };

  painter.drawLine(INNER_PADDING_LEFT, h - INNER_PADDING_BOTTOM, INNER_PADDING_LEFT, INNER_PADDING_TOP - EXTRA_INNNER_PADDING_TOP);
  painter.drawPolygon(triangle_vert, 3);

  // vykreslenie horizontalneho popisku
  painter.drawStaticText(w - INNER_PADDING_RIGHT - 40, h - INNER_PADDING_BOTTOM + 2, QStaticText("intensity"));

  // vykreslenie vertikalneho popisku
  {
    QTransform old_t = painter.transform();
    QTransform t;
    t.translate(0, INNER_PADDING_TOP + 30);
    t.rotate(-90);
    painter.setTransform(t);
    painter.drawStaticText(0, 0, QStaticText("opacity"));
    painter.setTransform(old_t);
  }
}