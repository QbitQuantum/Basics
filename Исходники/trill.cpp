void TrillSegment::layout()
      {
      if (autoplace())
            setUserOff(QPointF());

      if (staff())
            setMag(staff()->mag(tick()));
      if (isSingleType() || isBeginType()) {
            Accidental* a = trill()->accidental();
            if (a) {
                  a->layout();
                  a->setMag(a->mag() * .6);
                  qreal _spatium = spatium();
                  a->setPos(_spatium * 1.3, -2.2 * _spatium);
                  a->setParent(this);
                  }
            switch (trill()->trillType()) {
                  case Trill::Type::TRILL_LINE:
                        symbolLine(SymId::ornamentTrill, SymId::wiggleTrill);
                        break;
                  case Trill::Type::PRALLPRALL_LINE:
                        symbolLine(SymId::wiggleTrill, SymId::wiggleTrill);
                        break;
                  case Trill::Type::UPPRALL_LINE:
                              symbolLine(SymId::ornamentBottomLeftConcaveStroke,
                                 SymId::ornamentZigZagLineNoRightEnd, SymId::ornamentZigZagLineWithRightEnd);
                        break;
                  case Trill::Type::DOWNPRALL_LINE:
                              symbolLine(SymId::ornamentLeftVerticalStroke,
                                 SymId::ornamentZigZagLineNoRightEnd, SymId::ornamentZigZagLineWithRightEnd);
                        break;
                  }
            }
      else
            symbolLine(SymId::wiggleTrill, SymId::wiggleTrill);

      if (parent()) {
            qreal yo = score()->styleP(trill()->placeBelow() ? Sid::trillPosBelow : Sid::trillPosAbove);
            rypos() = yo;
            if (autoplace()) {
                  qreal minDistance = spatium();
                  Shape s1 = shape().translated(pos());
                  if (trill()->placeAbove()) {
                        qreal d  = system()->topDistance(staffIdx(), s1);
                        if (d > -minDistance)
                              rUserYoffset() = -d - minDistance;
                        }
                  else {
                        qreal d  = system()->bottomDistance(staffIdx(), s1);
                        if (d > -minDistance)
                              rUserYoffset() = d + minDistance;
                        }
                  }
            }
      }