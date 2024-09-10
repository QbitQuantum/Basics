void TimelineBar::paintEvent(QPaintEvent *e)
{
  QPainter p(viewport());

  p.setFont(font());
  p.setRenderHint(QPainter::TextAntialiasing);

  // draw boundaries and background
  {
    QRectF r = viewport()->rect();

    p.fillRect(r, palette().brush(QPalette::Window));

    r = r.marginsRemoved(QMargins(borderWidth + margin, borderWidth + margin, borderWidth + margin,
                                  borderWidth + margin));

    p.fillRect(r, palette().brush(QPalette::Base));
    p.drawRect(r);
  }

  QTextOption to;

  to.setWrapMode(QTextOption::NoWrap);
  to.setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

  QFontMetrics fm = p.fontMetrics();

  {
    QRectF titleRect = m_eidAxisRect;
    titleRect.setLeft(titleRect.left() - m_titleWidth);
    titleRect.setWidth(m_titleWidth);

    p.setPen(QPen(palette().brush(QPalette::Text), 1.0));

    // add an extra margin for the text
    p.drawText(titleRect.marginsRemoved(QMarginsF(margin, 0, 0, 0)), eidAxisTitle, to);

    titleRect.setLeft(titleRect.left() - margin);
    titleRect.setTop(titleRect.top() - margin);
    p.drawLine(titleRect.bottomLeft(), titleRect.bottomRight());
    p.drawLine(titleRect.topRight(), titleRect.bottomRight());
  }

  QRectF eidAxisRect = m_eidAxisRect;

  p.drawLine(eidAxisRect.bottomLeft(), eidAxisRect.bottomRight() + QPointF(margin, 0));

  p.drawLine(m_highlightingRect.topLeft(), m_highlightingRect.topRight());

  if(m_Draws.isEmpty())
    return;

  eidAxisRect.setLeft(m_eidAxisRect.left() + m_pan);

  uint32_t maxEID = m_Draws.isEmpty() ? 0 : m_Draws.back();

  to.setAlignment(Qt::AlignCenter | Qt::AlignVCenter);

  p.setFont(Formatter::PreferredFont());

  QRectF hoverRect = eidAxisRect;

  // clip labels to the visible section
  p.setClipRect(m_eidAxisRect.marginsAdded(QMargins(0, margin, margin, 0)));

  // draw where we're hovering
  {
    QPoint pos = viewport()->mapFromGlobal(QCursor::pos());

    if(m_dataArea.contains(pos))
    {
      uint32_t hoverEID = eventAt(pos.x());

      hoverRect.setLeft(offsetOf(hoverEID));
      hoverRect.setWidth(m_eidAxisLabelWidth);

      // recentre
      hoverRect.moveLeft(hoverRect.left() - m_eidAxisLabelWidth / 2 + m_eidWidth / 2);

      QColor backCol = palette().color(QPalette::Base);

      if(getLuminance(backCol) < 0.2f)
        backCol = backCol.lighter(120);
      else
        backCol = backCol.darker(120);

      QRectF backRect = hoverRect.marginsAdded(QMargins(0, margin - borderWidth, 0, 0));

      backRect.setLeft(qMax(backRect.left(), m_eidAxisRect.left() + 1));

      p.fillRect(backRect, backCol);

      p.drawText(hoverRect, QString::number(hoverEID), to);

      // re-add the top margin so the lines match up with the border around the EID axis
      hoverRect = hoverRect.marginsAdded(QMargins(0, margin, 0, 0));

      if(hoverRect.left() >= m_eidAxisRect.left())
        p.drawLine(hoverRect.topLeft(), hoverRect.bottomLeft());
      p.drawLine(hoverRect.topRight(), hoverRect.bottomRight());

      // shrink the rect a bit for clipping against labels below
      hoverRect.setX(qRound(hoverRect.x() + 0.5));
      hoverRect.setWidth(int(hoverRect.width()));
    }
    else
    {
      hoverRect = QRectF();
    }
  }

  QRectF labelRect = eidAxisRect;
  labelRect.setWidth(m_eidAxisLabelWidth);

  // iterate through the EIDs from 0, starting from possible a negative offset if the user has
  // panned to the right.
  for(uint32_t i = 0; i <= maxEID; i += m_eidAxisLabelStep)
  {
    labelRect.moveLeft(offsetOf(i) - labelRect.width() / 2 + m_eidWidth / 2);

    // check if this label is visible at all, but don't draw labels that intersect with the hovered
    // number
    if(labelRect.right() >= 0 && !labelRect.intersects(hoverRect))
      p.drawText(labelRect, QString::number(i), to);

    // check if labelRect is off the edge of the screen
    if(labelRect.left() >= m_eidAxisRect.right())
      break;
  }

  // stop clipping
  p.setClipRect(viewport()->rect());

  // clip the markers
  p.setClipRect(m_markerRect);

  {
    QPen pen = p.pen();
    paintMarkers(p, m_RootMarkers, m_RootDraws, m_markerRect);
    p.setPen(pen);
  }

  // stop clipping
  p.setClipRect(viewport()->rect());

  QRectF currentRect = eidAxisRect;

  // draw the current label and line
  {
    uint32_t curEID = m_Ctx.CurEvent();

    currentRect.setLeft(offsetOf(curEID));
    currentRect.setWidth(
        qMax(m_eidAxisLabelWidth, m_eidAxisLabelTextWidth + dataBarHeight + margin * 2));

    // recentre
    currentRect.moveLeft(currentRect.left() - currentRect.width() / 2 + m_eidWidth / 2);

    // remember where the middle would have been, without clamping
    qreal realMiddle = currentRect.center().x();

    // clamp the position from the left or right side
    if(currentRect.left() < eidAxisRect.left())
      currentRect.moveLeft(eidAxisRect.left());
    else if(currentRect.right() > eidAxisRect.right())
      currentRect.moveRight(eidAxisRect.right());

    // re-add the top margin so the lines match up with the border around the EID axis
    QRectF currentBackRect = currentRect.marginsAdded(QMargins(0, margin, 0, 0));

    p.fillRect(currentBackRect, palette().brush(QPalette::Base));
    p.drawRect(currentBackRect);

    // draw the 'current marker' pixmap
    const QPixmap &px = Pixmaps::flag_green(devicePixelRatio());
    p.drawPixmap(currentRect.topLeft() + QPointF(margin, 1), px, px.rect());

    // move to where the text should be and draw it
    currentRect.setLeft(currentRect.left() + margin * 2 + dataBarHeight);
    p.drawText(currentRect, QString::number(curEID), to);

    // draw a line from the bottom of the shadow downwards
    QPointF currentTop = currentRect.center();
    currentTop.setX(int(qBound(eidAxisRect.left(), realMiddle, eidAxisRect.right() - 2.0)) + 0.5);
    currentTop.setY(currentRect.bottom());

    QPointF currentBottom = currentTop;
    currentBottom.setY(m_markerRect.bottom());

    p.drawLine(currentTop, currentBottom);
  }

  to.setAlignment(Qt::AlignLeft | Qt::AlignTop);

  if(!m_UsageTarget.isEmpty() || !m_HistoryTarget.isEmpty())
  {
    p.setRenderHint(QPainter::Antialiasing);

    QRectF highlightLabel = m_highlightingRect.marginsRemoved(uniformMargins(margin));

    highlightLabel.setX(highlightLabel.x() + margin);

    QString text;

    if(!m_HistoryTarget.isEmpty())
      text = tr("Pixel history for %1").arg(m_HistoryTarget);
    else
      text = tr("Usage for %1:").arg(m_UsageTarget);

    p.drawText(highlightLabel, text, to);

    const int triRadius = fm.averageCharWidth();
    const int triHeight = fm.ascent();

    QPainterPath triangle;
    triangle.addPolygon(
        QPolygonF({QPoint(0, triHeight), QPoint(triRadius * 2, triHeight), QPoint(triRadius, 0)}));
    triangle.closeSubpath();

    enum
    {
      ReadUsage,
      WriteUsage,
      ReadWriteUsage,
      ClearUsage,
      BarrierUsage,

      HistoryPassed,
      HistoryFailed,

      UsageCount,
    };

    const QColor colors[UsageCount] = {
        // read
        QColor(Qt::red),
        // write
        QColor(Qt::green),
        // read/write
        QColor(Qt::yellow),
        // clear
        QColor(Qt::blue),
        // barrier
        QColor(Qt::magenta),

        // pass
        QColor(Qt::green),
        // fail
        QColor(Qt::red),
    };

    // draw the key
    if(m_HistoryTarget.isEmpty())
    {
      // advance past the first text to draw the key
      highlightLabel.setLeft(highlightLabel.left() + fm.width(text));

      text = lit(" Reads ( ");
      p.drawText(highlightLabel, text, to);
      highlightLabel.setLeft(highlightLabel.left() + fm.width(text));

      QPainterPath path = triangle.translated(aliasAlign(highlightLabel.topLeft()));
      p.fillPath(path, colors[ReadUsage]);
      p.drawPath(path);
      highlightLabel.setLeft(highlightLabel.left() + triRadius * 2);

      text = lit(" ), Writes ( ");
      p.drawText(highlightLabel, text, to);
      highlightLabel.setLeft(highlightLabel.left() + fm.width(text));

      path = triangle.translated(aliasAlign(highlightLabel.topLeft()));
      p.fillPath(path, colors[WriteUsage]);
      p.drawPath(path);
      highlightLabel.setLeft(highlightLabel.left() + triRadius * 2);

      text = lit(" ), Read/Write ( ");
      p.drawText(highlightLabel, text, to);
      highlightLabel.setLeft(highlightLabel.left() + fm.width(text));

      path = triangle.translated(aliasAlign(highlightLabel.topLeft()));
      p.fillPath(path, colors[ReadWriteUsage]);
      p.drawPath(path);
      highlightLabel.setLeft(highlightLabel.left() + triRadius * 2);

      if(m_Ctx.CurPipelineState().SupportsBarriers())
      {
        text = lit(" ) Barriers ( ");
        p.drawText(highlightLabel, text, to);
        highlightLabel.setLeft(highlightLabel.left() + fm.width(text));

        path = triangle.translated(aliasAlign(highlightLabel.topLeft()));
        p.fillPath(path, colors[BarrierUsage]);
        p.drawPath(path);
        highlightLabel.setLeft(highlightLabel.left() + triRadius * 2);
      }

      text = lit(" ), and Clears ( ");
      p.drawText(highlightLabel, text, to);
      highlightLabel.setLeft(highlightLabel.left() + fm.width(text));

      path = triangle.translated(aliasAlign(highlightLabel.topLeft()));
      p.fillPath(path, colors[ClearUsage]);
      p.drawPath(path);
      highlightLabel.setLeft(highlightLabel.left() + triRadius * 2);

      text = lit(" )");
      p.drawText(highlightLabel, text, to);
    }

    PipRanges pipranges[UsageCount];

    QRectF pipsRect = m_highlightingRect.marginsRemoved(uniformMargins(margin));

    pipsRect.setX(pipsRect.x() + margin + m_titleWidth);
    pipsRect.setHeight(triHeight + margin);
    pipsRect.moveBottom(m_highlightingRect.bottom());

    p.setClipRect(pipsRect);

    qreal leftClip = -triRadius * 2.0;
    qreal rightClip = pipsRect.width() + triRadius * 10.0;

    if(!m_HistoryEvents.isEmpty())
    {
      for(const PixelModification &mod : m_HistoryEvents)
      {
        qreal pos = offsetOf(mod.eventId) + m_eidWidth / 2 - triRadius;

        if(pos < leftClip || pos > rightClip)
          continue;

        if(mod.Passed())
          pipranges[HistoryPassed].push(pos, triRadius);
        else
          pipranges[HistoryFailed].push(pos, triRadius);
      }
    }
    else
    {
      for(const EventUsage &use : m_UsageEvents)
      {
        qreal pos = offsetOf(use.eventId) + m_eidWidth / 2 - triRadius;

        if(pos < leftClip || pos > rightClip)
          continue;

        if(((int)use.usage >= (int)ResourceUsage::VS_RWResource &&
            (int)use.usage <= (int)ResourceUsage::All_RWResource) ||
           use.usage == ResourceUsage::GenMips || use.usage == ResourceUsage::Copy ||
           use.usage == ResourceUsage::Resolve)
        {
          pipranges[ReadWriteUsage].push(pos, triRadius);
        }
        else if(use.usage == ResourceUsage::StreamOut || use.usage == ResourceUsage::ResolveDst ||
                use.usage == ResourceUsage::ColorTarget ||
                use.usage == ResourceUsage::DepthStencilTarget || use.usage == ResourceUsage::CopyDst)
        {
          pipranges[WriteUsage].push(pos, triRadius);
        }
        else if(use.usage == ResourceUsage::Clear)
        {
          pipranges[ClearUsage].push(pos, triRadius);
        }
        else if(use.usage == ResourceUsage::Barrier)
        {
          pipranges[BarrierUsage].push(pos, triRadius);
        }
        else
        {
          pipranges[ReadUsage].push(pos, triRadius);
        }
      }
    }

    for(int i = 0; i < UsageCount; i++)
    {
      QPainterPath path = pipranges[i].makePath(triRadius, triHeight, pipsRect.y());

      if(!path.isEmpty())
      {
        p.drawPath(path);
        p.fillPath(path, colors[i]);
      }
    }
  }
  else
  {
    QRectF highlightLabel = m_highlightingRect;
    highlightLabel = highlightLabel.marginsRemoved(uniformMargins(margin));

    highlightLabel.setX(highlightLabel.x() + margin);

    p.drawText(highlightLabel, tr("No resource selected for highlighting."), to);
  }
}