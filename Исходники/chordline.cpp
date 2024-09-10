void ChordLine::layout()
      {
      if (!modified) {
            qreal x2 = 0;
            qreal y2 = 0;
            switch(_chordLineType) {
                  case ChordLineType::NOTYPE:
                        break;
                  case ChordLineType::FALL:
                        x2 = _initialLength;
                        y2 = _initialLength;
                        break;
                  case ChordLineType::PLOP:
                        x2 = -_initialLength;
                        y2 = -_initialLength;
                        break;
                  case ChordLineType::SCOOP:
                        x2 = -_initialLength;
                        y2 = _initialLength;
                        break;
                  default:
                  case ChordLineType::DOIT:
                        x2 = _initialLength;
                        y2 = -_initialLength;
                        break;
                  }
            if (_chordLineType != ChordLineType::NOTYPE) {
                  path = QPainterPath();
                  // chordlines to the right of the note
                  if (_chordLineType == ChordLineType::FALL || _chordLineType == ChordLineType::DOIT) {
                        if (_straight)
                              path.lineTo(x2, y2);
                        else
                              path.cubicTo(x2/2, 0.0, x2, y2/2, x2, y2);
                        }
                  // chordlines to the left of the note
                  else if (_chordLineType == ChordLineType::PLOP || _chordLineType == ChordLineType::SCOOP) {
                        if (_straight)
                              path.lineTo(x2, y2);
                        else
                              path.cubicTo(0.0, y2/2, x2/2, y2, x2, y2);
                        }
                  }
            }

      qreal _spatium = spatium();
      if (parent()) {
            Note* note = chord()->upNote();
            QPointF p(note->pos());
            // chordlines to the right of the note
            if (_chordLineType == ChordLineType::FALL || _chordLineType == ChordLineType::DOIT)
                  setPos(p.x() + note->headWidth() + _spatium * .2, p.y());
            // chordlines to the left of the note
            if (_chordLineType == ChordLineType::PLOP)
                  setPos(p.x() + note->headWidth() * .25, p.y() - note->headHeight() * .75);
            if (_chordLineType == ChordLineType::SCOOP) {
                  qreal x = p.x() + (chord()->up() ? note->headWidth() * .25 : _spatium * -.2);
                  setPos(x, p.y() + note->headHeight() * .75);
                  }
            }
      else
            setPos(0.0, 0.0);
      QRectF r(path.boundingRect());
      int x1, y1, width, height = 0;

      x1 = r.x() * _spatium;
      y1 = r.y() * _spatium;
      width = r.width() * _spatium;
      height = r.height() * _spatium;
      bbox().setRect(x1, y1, width, height);
      }