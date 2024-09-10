void Stem::draw(QPainter* painter) const
      {
      // hide if second chord of a cross-measure pair
      if (chord() && chord()->crossMeasure() == CrossMeasure::SECOND)
            return;

      Staff* st   = staff();
      bool useTab = st && st->isTabStaff(chord()->tick());

      painter->setPen(QPen(curColor(), _lineWidth, Qt::SolidLine, Qt::RoundCap));
      painter->drawLine(line);

      if (!(useTab && chord()))
            return;

      // TODO: adjust bounding rectangle in layout() for dots and for slash
      StaffType* stt = st->staffType(chord()->tick());
      qreal sp = spatium();
      bool _up = up();

      // slashed half note stem
      if (chord()->durationType().type() == TDuration::DurationType::V_HALF && stt->minimStyle() == TablatureMinimStyle::SLASHED) {
            // position slashes onto stem
            qreal y = _up ? -(_len+_userLen) + STAFFTYPE_TAB_SLASH_2STARTY_UP*sp : (_len+_userLen) - STAFFTYPE_TAB_SLASH_2STARTY_DN*sp;
            // if stems through, try to align slashes within or across lines
            if (stt->stemThrough()) {
                  qreal halfLineDist = stt->lineDistance().val() * sp * 0.5;
                  qreal halfSlashHgt = STAFFTYPE_TAB_SLASH_2TOTHEIGHT * sp * 0.5;
                  y = lrint( (y + halfSlashHgt) / halfLineDist) * halfLineDist - halfSlashHgt;
                  }
            // draw slashes
            qreal hlfWdt= sp * STAFFTYPE_TAB_SLASH_WIDTH * 0.5;
            qreal sln   = sp * STAFFTYPE_TAB_SLASH_SLANTY;
            qreal thk   = sp * STAFFTYPE_TAB_SLASH_THICK;
            qreal displ = sp * STAFFTYPE_TAB_SLASH_DISPL;
            QPainterPath path;
            for (int i = 0; i < 2; ++i) {
                  path.moveTo( hlfWdt, y);            // top-right corner
                  path.lineTo( hlfWdt, y+thk);        // bottom-right corner
                  path.lineTo(-hlfWdt, y+thk+sln);    // bottom-left corner
                  path.lineTo(-hlfWdt, y+sln);        // top-left corner
                  path.closeSubpath();
                  y += displ;
                  }
            painter->setBrush(QBrush(curColor()));
            painter->setPen(Qt::NoPen);
            painter->drawPath(path);
            }

      // dots
      // NOT THE BEST PLACE FOR THIS?
      // with tablatures and stems beside staves, dots are not drawn near 'notes', but near stems
      int nDots = chord()->dots();
      if (nDots > 0 && !stt->stemThrough()) {
            qreal x     = chord()->dotPosX();
            qreal y     = ( (STAFFTYPE_TAB_DEFAULTSTEMLEN_DN * 0.2) * sp) * (_up ? -1.0 : 1.0);
            qreal step  = score()->styleS(StyleIdx::dotDotDistance).val() * sp;
            for (int dot = 0; dot < nDots; dot++, x += step)
                  drawSymbol(SymId::augmentationDot, painter, QPointF(x, y));
            }
      }