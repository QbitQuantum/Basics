QPointF Arpeggio::gripAnchor(int n) const
      {
      Chord* c = chord();
      if (c == 0)
            return QPointF();
      if (n == 0)
            return c->upNote()->pagePos();
      else if (n == 1) {
            Note* dnote = c->downNote();
            int btrack  = track() + (_span - 1) * VOICES;
            ChordRest* bchord = static_cast<ChordRest*>(c->segment()->element(btrack));
            if (bchord && bchord->type() == CHORD)
                  dnote = static_cast<Chord*>(bchord)->downNote();
            return dnote->pagePos();
            }
      return QPointF();
      }