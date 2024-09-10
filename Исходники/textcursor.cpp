void PositionCursor::move(int tick)
      {
      QRectF r(bbox());
      //
      // set mark height for whole system
      //
      if (_type == CursorType::LOOP_OUT)
        tick --;
      Score* score = _sv->score();
      Measure* measure = score->tick2measureMM(tick);
      if (measure == 0)
            return;
      qreal x;
      int offset = 0;

      Segment* s;
      for (s = measure->first(Segment::Type::ChordRest); s;) {
            int t1 = s->tick();
            int x1 = s->canvasPos().x();
            qreal x2;
            int t2;
            Segment* ns = s->next(Segment::Type::ChordRest);
            if (ns) {
                  t2 = ns->tick();
                  x2 = ns->canvasPos().x();
                  }
            else {
                  t2 = measure->endTick();
                  x2 = measure->canvasPos().x() + measure->width();
                  }
            t1 += offset;
            t2 += offset;
            if (tick >= t1 && tick < t2) {
                  int   dt = t2 - t1;
                  qreal dx = x2 - x1;
                  x = x1 + dx * (tick-t1) / dt;
                  break;
                  }
            s = ns;
            }
      if (s == 0)
            return;

      System* system = measure->system();
      if (system == 0)
            return;
      double y        = system->staffYpage(0) + system->page()->pos().y();
      double _spatium = score->spatium();

      qreal mag = _spatium / (MScore::DPI * SPATIUM20);
      double w  = (_spatium * 2.0 + score->scoreFont()->width(SymId::noteheadBlack, mag))/3;
      double h  = 6 * _spatium;
      //
      // set cursor height for whole system
      //
      double y2 = 0.0;

      for (int i = 0; i < score->nstaves(); ++i) {
            SysStaff* ss = system->staff(i);
            if (!ss->show() || !score->staff(i)->show())
                  continue;
            y2 = ss->y() + ss->bbox().height();
            }
      h += y2;
      y -= 3 * _spatium;

      if (_type == CursorType::LOOP_IN) {
            x = x - _spatium + w/1.5;
            }
      else {
            x = x - _spatium * .5;
            }
      _tick = tick;
      _rect = QRectF(x, y, w, h);
      _sv->update(_sv->matrix().mapRect(r | bbox()).toRect().adjusted(-1,-1,1,1));
      }