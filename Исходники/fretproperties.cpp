void FretCanvas::paintEvent(QPaintEvent* ev)
      {
      double mag        = 1.5;
      double _spatium   = 20.0 * mag;
      double lw1        = _spatium * 0.08;
      int fretOffset    = diagram->fretOffset();
      double lw2        = fretOffset ? lw1 : _spatium * 0.2;
      double stringDist = _spatium * .7;
      double fretDist   = _spatium * .8;
      int _strings      = diagram->strings();
      int _frets        = diagram->frets();
//      char* _dots       = diagram->dots();
//      char* _marker     = diagram->marker();

      double w  = (_strings - 1) * stringDist;
      double xo = (width() - w) * .5;
      double h  = (_frets * fretDist) + fretDist * .5;
      double yo = (height() - h) * .5;

      QFont font("FreeSans");
      int size = lrint(18.0 * mag);
      font.setPixelSize(size);

      QPainter p(this);
      p.setRenderHint(QPainter::Antialiasing, preferences.antialiasedDrawing);
      p.setRenderHint(QPainter::TextAntialiasing, true);
      p.translate(xo, yo);

      QPen pen(p.pen());
      pen.setWidthF(lw2);
      pen.setCapStyle(Qt::FlatCap);
      p.setPen(pen);
      p.setBrush(pen.color());
      double x2 = (_strings-1) * stringDist;
      p.drawLine(QLineF(-lw1 * .5, 0.0, x2+lw1*.5, 0.0));

      pen.setWidthF(lw1);
      p.setPen(pen);
      double y2 = (_frets+1) * fretDist - fretDist*.5;
      for (int i = 0; i < _strings; ++i) {
            double x = stringDist * i;
            p.drawLine(QLineF(x, fretOffset ? -_spatium*.2 : 0.0, x, y2));
            }
      for (int i = 1; i <= _frets; ++i) {
            double y = fretDist * i;
            p.drawLine(QLineF(0.0, y, x2, y));
            }
      for (int i = 0; i < _strings; ++i) {
            p.setPen(Qt::NoPen);
            if (diagram->dot(i)) {
                  double dotd = stringDist * .6 + lw1;
                  int fret = diagram->dot(i) - 1;
                  double x = stringDist * i - dotd * .5;
                  double y = fretDist * fret + fretDist * .5 - dotd * .5;
                  p.drawEllipse(QRectF(x, y, dotd, dotd));
                  }
            p.setPen(pen);
            if (diagram->marker(i)) {
                  p.setFont(font);
                  double x = stringDist * i;
                  double y = -fretDist * .1;
                  p.drawText(QRectF(x, y, 0.0, 0.0),
                     Qt::AlignHCenter | Qt::AlignBottom | Qt::TextDontClip, QChar(diagram->marker(i)));
                  }
            }
      if ((cfret > 0) && (cfret <= _frets) && (cstring >= 0) && (cstring < _strings)) {
            double dotd;
            if (diagram->dot(cstring) != cfret) {
                  p.setPen(Qt::NoPen);
                  dotd = stringDist * .6 + lw1;
                  }
            else {
                  p.setPen(pen);
                  dotd = stringDist * .6;
                  }
            double x = stringDist * cstring - dotd * .5;
            double y = fretDist * (cfret-1) + fretDist * .5 - dotd * .5;
            p.setBrush(Qt::lightGray);
            p.drawEllipse(QRectF(x, y, dotd, dotd));
            }
      if (fretOffset > 0) {
            qreal fretNumMag = 2.0; // TODO: get the value from StyleIdx::fretNumMag
            QFont scaledFont(font);
            scaledFont.setPixelSize(font.pixelSize() * fretNumMag);
            p.setFont(scaledFont);
            p.setPen(pen);
            // Todo: make dependant from StyleIdx::fretNumPos
            p.drawText(QRectF(-stringDist * .4, 0.0, 0.0, fretDist),
               Qt::AlignVCenter|Qt::AlignRight|Qt::TextDontClip,
               QString("%1").arg(fretOffset+1));
            p.setFont(font);
            }
      QFrame::paintEvent(ev);
      }