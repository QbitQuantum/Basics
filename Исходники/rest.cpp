void Rest::layout()
      {
      if (staff() && staff()->isTabStaff()) {
            // no rests for tablature
            _space.setLw(0.0);
            _space.setRw(0.0);
            return;
            }
      switch(durationType().type()) {
            case TDuration::V_64TH:
            case TDuration::V_32ND:
                  dotline = -3;
                  break;
            case TDuration::V_256TH:
            case TDuration::V_128TH:
                  dotline = -5;
                  break;
            default:
                  dotline = -1;
                  break;
            }
      qreal _spatium = spatium();
      int stepOffset     = 0;
      if (staff())
            stepOffset = staff()->staffType()->stepOffset();
      int line        = lrint(userOff().y() / _spatium); //  + ((staff()->lines()-1) * 2);
      int lineOffset  = 0;

      int lines = staff() ? staff()->lines() : 5;
      if (segment() && measure() && measure()->mstaff(staffIdx())->hasVoices) {
            // move rests in a multi voice context
            bool up = (voice() == 0) || (voice() == 2);       // TODO: use style values
            switch(durationType().type()) {
                  case TDuration::V_LONG:
                        lineOffset = up ? -3 : 5;
                        break;
                  case TDuration::V_BREVE:
                        lineOffset = up ? -3 : 5;
                        break;
                  case TDuration::V_MEASURE:
                        if (duration() >= Fraction(2, 1))    // breve symbol
                              lineOffset = up ? -3 : 5;
                        // fall through
                  case TDuration::V_WHOLE:
                        lineOffset = up ? -4 : 6;
                        break;
                  case TDuration::V_HALF:
                        lineOffset = up ? -4 : 4;
                        break;
                  case TDuration::V_QUARTER:
                        lineOffset = up ? -4 : 4;
                        break;
                  case TDuration::V_EIGHT:
                        lineOffset = up ? -4 : 4;
                        break;
                  case TDuration::V_16TH:
                        lineOffset = up ? -6 : 4;
                        break;
                  case TDuration::V_32ND:
                        lineOffset = up ? -6 : 6;
                        break;
                  case TDuration::V_64TH:
                        lineOffset = up ? -8 : 6;
                        break;
                  case TDuration::V_128TH:
                        lineOffset = up ? -8 : 8;
                        break;
                  case TDuration::V_256TH:             // not available
                        lineOffset = up ? -10 : 6;
                        break;
                  default:
                        break;
                  }
            }
      else {
            switch(durationType().type()) {
                  case TDuration::V_LONG:
                  case TDuration::V_BREVE:
                  case TDuration::V_MEASURE:
                  case TDuration::V_WHOLE:
                        if (lines == 1)
                              lineOffset = -2;
                        break;
                  case TDuration::V_HALF:
                  case TDuration::V_QUARTER:
                  case TDuration::V_EIGHT:
                  case TDuration::V_16TH:
                  case TDuration::V_32ND:
                  case TDuration::V_64TH:
                  case TDuration::V_128TH:
                  case TDuration::V_256TH:             // not available
                        if (lines == 1)
                              lineOffset = -4;
                        break;
                  default:
                        break;
                  }
            }

      int yo;
      _sym = getSymbol(durationType().type(), line + lineOffset/2, lines, &yo);
      layoutArticulations();
      rypos() = (qreal(yo) + qreal(lineOffset + stepOffset) * .5) * _spatium;

      Spatium rs;
      if (dots()) {
            rs = Spatium(score()->styleS(ST_dotNoteDistance)
               + dots() * score()->styleS(ST_dotDotDistance));
            }
      Segment* s = segment();
      if (s && s->measure() && s->measure()->multiMeasure()) {
            qreal _spatium = spatium();
            qreal h = _spatium * 6.5;
            qreal w = point(score()->styleS(ST_minMMRestWidth));
            setbbox(QRectF(-w * .5, -h + 2 * _spatium, w, h));
            }
      else {
            if (dots()) {
                  rs = Spatium(score()->styleS(ST_dotNoteDistance)
                     + dots() * score()->styleS(ST_dotDotDistance));
                  }
            setbbox(symbols[score()->symIdx()][_sym].bbox(magS()));
            }
      _space.setLw(0.0);
      _space.setRw(width() + point(rs));
      }