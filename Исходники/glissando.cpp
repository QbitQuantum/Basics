void Glissando::layout()
      {
      Chord* chord = static_cast<Chord*>(parent());
      if (chord == 0) {
            return;
            }
      Note* anchor2   = chord->upNote();
      Segment* s = chord->segment();
      s = s->prev1();
      while (s) {
            if ((s->subtype() == SegChordRest || s->subtype() == SegGrace) && s->element(track()))
                  break;
            s = s->prev1();
            }
      if (s == 0) {
            qDebug("no segment for first note of glissando found\n");
            return;
            }
      ChordRest* cr = static_cast<ChordRest*>(s->element(track()));
      if (cr == 0 || cr->type() != CHORD) {
            qDebug("no first note for glissando found, track %d\n", track());
            return;
            }
      Note* anchor1 = static_cast<Chord*>(cr)->upNote();

      setPos(0.0, 0.0);

      QPointF cp1    = anchor1->pagePos();
      QPointF cp2    = anchor2->pagePos();

      // construct line from notehead to notehead
      qreal x1 = (anchor1->headWidth()) - (cp2.x() - cp1.x());
      qreal y1 = anchor1->pos().y();
      qreal x2 = anchor2->pos().x();
      qreal y2 = anchor2->pos().y();
      QLineF fullLine(x1, y1, x2, y2);

      // shorten line on each side by offsets
      qreal xo = spatium() * .5;
      qreal yo = xo;   // spatium() * .5;
      QPointF p1 = fullLine.pointAt(xo / fullLine.length());
      QPointF p2 = fullLine.pointAt(1 - (yo / fullLine.length()));

      line = QLineF(p1, p2);
      qreal lw = spatium() * .15 * .5;
      QRectF r = QRectF(line.p1(), line.p2()).normalized();
      setbbox(r.adjusted(-lw, -lw, lw, lw));
      }