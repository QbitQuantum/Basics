void PianoView::drawBackground(QPainter* p, const QRectF& r)
      {
      if (staff == 0)
            return;
      Score* _score = staff->score();
      setFrameShape(QFrame::NoFrame);

      QRectF r1;
      r1.setCoords(-1000000.0, 0.0, 480.0, 1000000.0);
      QRectF r2;
      r2.setCoords(ticks + MAP_OFFSET, 0.0, 1000000.0, 1000000.0);
      QColor bg(0x71, 0x8d, 0xbe);

      p->fillRect(r, bg);
      if (r.intersects(r1))
            p->fillRect(r.intersected(r1), bg.darker(150));
      if (r.intersects(r2))
            p->fillRect(r.intersected(r2), bg.darker(150));

      //
      // draw horizontal grid lines
      //
      qreal y1 = r.y();
      qreal y2 = y1 + r.height();
      qreal kh = 13.0;
      qreal x1 = r.x();
      qreal x2 = x1 + r.width();

      // int key = floor(y1 / 75);
      int key = floor(y1 / kh);
      qreal y = key * kh;

      for (; key < 75; ++key, y += kh) {
            if (y < y1)
                  continue;
            if (y > y2)
                  break;
            p->setPen(QPen((key % 7) == 5 ? Qt::lightGray : Qt::gray));
            p->drawLine(QLineF(x1, y, x2, y));
            }

      //
      // draw vertical grid lines
      //
      static const int mag[7] = {
            1, 1, 2, 5, 10, 20, 50
            };

      Pos pos1 = pix2pos(x1);
      Pos pos2 = pix2pos(x2);

      //---------------------------------------------------
      //    draw raster
      //---------------------------------------------------

      int bar1, bar2, beat, tick;
      pos1.mbt(&bar1, &beat, &tick);
      pos2.mbt(&bar2, &beat, &tick);

      int n = mag[magStep < 0 ? 0 : magStep];

      bar1 = (bar1 / n) * n;           // round down
      if (bar1 && n >= 2)
            bar1 -= 1;
      bar2 = ((bar2 + n - 1) / n) * n; // round up

      for (int bar = bar1; bar <= bar2;) {
            Pos stick(_score->tempomap(), _score->sigmap(), bar, 0, 0);
            if (magStep > 0) {
                  double x = double(pos2pix(stick));
                  if (x > 0) {
                        p->setPen(QPen(Qt::lightGray, 0.0));
                        p->drawLine(x, y1, x, y2);
                        }
                  else {
                        p->setPen(QPen(Qt::black, 0.0));
                        p->drawLine(x, y1, x, y1);
                        }
                  }
            else {
                  int z = stick.timesig().timesig().numerator();
                  for (int beat = 0; beat < z; beat++) {
                        if (magStep == 0) {
                              Pos xx(_score->tempomap(), _score->sigmap(), bar, beat, 0);
                              int xp = pos2pix(xx);
                              if (xp < 0)
                                    continue;
                              if (xp > 0) {
                                    p->setPen(QPen(beat == 0 ? Qt::lightGray : Qt::gray, 0.0));
                                    p->drawLine(xp, y1, xp, y2);
                                    }
                              else {
                                    p->setPen(QPen(Qt::black, 0.0));
                                    p->drawLine(xp, y1, xp, y2);
                                    }
                              }
                        else {
                              int k;
                              if (magStep == -1)
                                    k = 2;
                              else if (magStep == -2)
                                    k = 4;
                              else if (magStep == -3)
                                    k = 8;
                              else if (magStep == -4)
                                    k = 16;
                              else
                                    k = 32;

                              int n = (MScore::division * 4) / stick.timesig().timesig().denominator();
                              for (int i = 0; i < k; ++i) {
                                    Pos xx(_score->tempomap(), _score->sigmap(), bar, beat, (n * i)/ k);
                                    int xp = pos2pix(xx);
                                    if (xp < 0)
                                          continue;
                                    if (xp > 0) {
                                          p->setPen(QPen(i == 0 && beat == 0 ? Qt::lightGray : Qt::gray, 0.0));
                                          p->drawLine(xp, y1, xp, y2);
                                          }
                                    else {
                                          p->setPen(QPen(Qt::black, 0.0));
                                          p->drawLine(xp, y1, xp, y2);
                                          }
                                    }
                              }
                        }
                  }
            if (bar == 0 && n >= 2)
                  bar += (n-1);
            else
                  bar += n;
            }
      }