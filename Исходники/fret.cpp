QLineF FretDiagram::dragAnchor() const
      {
      qreal xp = 0.0;
      for (Element* e = parent(); e; e = e->parent())
            xp += e->x();
      qreal yp;
      if (parent()->isSegment()) {
            System* system = toSegment(parent())->measure()->system();
            yp = system->staffCanvasYpage(staffIdx());
            }
      else
            yp = parent()->canvasPos().y();
      QPointF p1(xp, yp);
      return QLineF(p1, canvasPos());
#if 0 // TODOxx
      if (parent()->type() == ElementType::SEGMENT) {
            Segment* s     = toSegment(parent());
            Measure* m     = s->measure();
            System* system = m->system();
            qreal yp      = system->staff(staffIdx())->y() + system->y();
            qreal xp      = m->tick2pos(s->tick()) + m->pagePos().x();
            QPointF p1(xp, yp);

            qreal x  = 0.0;
            qreal y  = 0.0;
            qreal tw = width();
            qreal th = height();
            if (_align & Align::BOTTOM)
                  y = th;
            else if (_align & Align::VCENTER)
                  y = (th * .5);
            else if (_align & Align::BASELINE)
                  y = baseLine();
            if (_align & Align::RIGHT)
                  x = tw;
            else if (_align & Align::HCENTER)
                  x = (tw * .5);
            return QLineF(p1, abbox().topLeft() + QPointF(x, y));
            }
      return QLineF(parent()->pagePos(), abbox().topLeft());
#endif
      }