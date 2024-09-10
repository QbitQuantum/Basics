QPointF Articulation::pagePos() const
      {
      if (parent() == 0 || parent()->parent() == 0)
            return pos();
      if (parent()->isChordRest()) {
            ChordRest* cr = static_cast<ChordRest*>(parent());
            Measure* m = cr->measure();
            if (m == 0)
                  return pos();
            System* system = m->system();
            if (system == 0)
                  return pos();
            qreal yp = y() + system->staff(staffIdx() + cr->staffMove())->y() + system->y();
            return QPointF(pageX(), yp);
            }
      return Element::pagePos();
      }