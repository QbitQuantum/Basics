void ChordRest::layoutArticulations()
      {
      if (parent() == 0 || _articulations.isEmpty())
            return;
      qreal _spatium  = spatium();
      qreal _spStaff  = _spatium * staff()->lineDistance(); // scaled to staff line distance for vert. pos. within a staff

      if (type() == Element::Type::CHORD) {
            if (_articulations.size() == 1) {
                  static_cast<Chord*>(this)->layoutArticulation(_articulations[0]);
                  return;
                  }
            if (_articulations.size() == 2) {
                  //
                  // staccato | tenuto + marcato
                  //
                  Articulation* a1 = _articulations[0];
                  Articulation* a2 = _articulations[1];
                  ArticulationType st1 = a1->articulationType();
                  ArticulationType st2 = a2->articulationType();

                  if ((st2 == ArticulationType::Tenuto || st2 == ArticulationType::Staccato)
                     && (st1 == ArticulationType::Marcato)) {
                        qSwap(a1, a2);
                        qSwap(st1, st2);
                        }
                  if ((st1 == ArticulationType::Tenuto || st1 == ArticulationType::Staccato)
                     && (st2 == ArticulationType::Marcato)) {
                        QPointF pt = static_cast<Chord*>(this)->layoutArticulation(a1);
                        pt.ry() += a1->up() ? -_spStaff * .5 : _spStaff * .5;
                        a2->layout();
                        a2->setUp(a1->up());
                        a2->setPos(pt);
                        a2->adjustReadPos();
                        return;
                        }
                  //
                  // staccato | tenuto + sforzato
                  //
                  if ((st2 == ArticulationType::Tenuto || st2 == ArticulationType::Staccato)
                     && (st1 == ArticulationType::Sforzatoaccent)) {
                        qSwap(a1, a2);
                        qSwap(st1, st2);
                        }
                  if ((st1 == ArticulationType::Tenuto || st1 == ArticulationType::Staccato)
                     && (st2 == ArticulationType::Sforzatoaccent)) {
                        QPointF pt = static_cast<Chord*>(this)->layoutArticulation(a1);
                        pt.ry() += a1->up() ? -_spStaff * .7 : _spStaff * .7;
                        a2->layout();
                        a2->setUp(a1->up());
                        a2->setPos(pt);
                        a2->adjustReadPos();
                        return;
                        }
                  }
            }

      qreal x         = centerX();
      qreal distance0 = score()->styleS(StyleIdx::propertyDistance).val()     * _spatium;
      qreal distance1 = score()->styleS(StyleIdx::propertyDistanceHead).val() * _spatium;
      qreal distance2 = score()->styleS(StyleIdx::propertyDistanceStem).val() * _spatium;

      qreal chordTopY = upPos();    // note position of highest note
      qreal chordBotY = downPos();  // note position of lowest note

      qreal staffTopY = -distance2;
      qreal staffBotY = staff()->height() + distance2;

      // avoid collisions of staff articulations with chord notes:
      // gap between note and staff articulation is distance0 + 0.5 spatium

      if (type() == Element::Type::CHORD) {
            Chord* chord = static_cast<Chord*>(this);
            Stem* stem   = chord->stem();
            if (stem) {
                  qreal y = stem->pos().y() + pos().y();
                  if (up() && stem->stemLen() < 0.0)
                        y += stem->stemLen();
                  else if (!up() && stem->stemLen() > 0.0)
                        y -= stem->stemLen();

                  if (beam()) {
                        qreal bw = score()->styleS(StyleIdx::beamWidth).val() * _spatium;
                        y += up() ? -bw : bw;
                        }
                  if (up())
                        staffTopY = qMin(staffTopY, qreal(y - 0.5 * _spatium));
                  else
                        staffBotY = qMax(staffBotY, qreal(y + 0.5 * _spatium));
                  }
            }

      staffTopY = qMin(staffTopY, qreal(chordTopY - distance0 - 0.5 * _spatium));
      staffBotY = qMax(staffBotY, qreal(chordBotY + distance0 + 0.5 * _spatium));

      qreal dy = 0.0;

      int n = _articulations.size();
      for (int i = 0; i < n; ++i) {
            Articulation* a = _articulations.at(i);
            //
            // determine MScore::Direction
            //
            if (a->direction() != MScore::Direction::AUTO) {
                  a->setUp(a->direction() == MScore::Direction::UP);
                  }
            else {
                  if (a->anchor() == ArticulationAnchor::CHORD)
                        a->setUp(!up());
                  else
                        a->setUp(a->anchor() == ArticulationAnchor::TOP_STAFF || a->anchor() == ArticulationAnchor::TOP_CHORD);
                  }
            }

      //
      //    pass 1
      //    place tenuto and staccato
      //

      for (int i = 0; i < n; ++i) {
            Articulation* a = _articulations.at(i);
            a->layout();
            ArticulationAnchor aa = a->anchor();

            if ((a->articulationType() != ArticulationType::Tenuto)
               && (a->articulationType() != ArticulationType::Staccato))
                  continue;

            if (aa != ArticulationAnchor::CHORD && aa != ArticulationAnchor::TOP_CHORD && aa != ArticulationAnchor::BOTTOM_CHORD)
                  continue;

            bool bottom;
            if ((aa == ArticulationAnchor::CHORD) && measure()->hasVoices(a->staffIdx()))
                  bottom = !up();
            else
                  bottom = (aa == ArticulationAnchor::BOTTOM_CHORD) || (aa == ArticulationAnchor::CHORD && up());
            bool headSide = bottom == up();

            dy += distance1;
            qreal y;
            Chord* chord = static_cast<Chord*>(this);
            if (bottom) {
                  int line = downLine();
                  y = chordBotY + dy;
                  if (!headSide && type() == Element::Type::CHORD && chord->stem()) {
                        Stem* stem = chord->stem();
                        y          = chordTopY + stem->stemLen();
                        if (chord->beam())
                              y += score()->styleS(StyleIdx::beamWidth).val() * _spatium * .5;
                        x          = stem->pos().x();
                        int line   = lrint((y+0.5*_spatium) / _spatium);
                        if (line <= 4)    // align between staff lines
                              y = line * _spatium + _spatium * .5;
                        else
                              y += _spatium;
                        }
                  else {
                        int lines = (staff()->lines() - 1) * 2;
                        if (line < lines)
                              y = (line & ~1) + 3;
                        else
                              y = line + 2;
                        y *= _spatium * .5;
                        }
                  }
            else {
                  int line = upLine();
                  y = chordTopY - dy;
                  if (!headSide && type() == Element::Type::CHORD && chord->stem()) {
                        Stem* stem = chord->stem();
                        y          = chordBotY + stem->stemLen();
                        if (chord->beam())
                              y -= score()->styleS(StyleIdx::beamWidth).val() * _spatium * .5;
                        x          = stem->pos().x();
                        int line   = lrint((y-0.5*_spatium) / _spatium);
                        if (line >= 0)    // align between staff lines
                              y = line * _spatium - _spatium * .5;
                        else
                              y -= _spatium;
                        }
                  else {
                        if (line > 0)
                              y = ((line+1) & ~1) - 3;
                        else
                              y = line - 2;
                        y *= _spatium * .5;
                        }
                  }
            dy += _spatium * .5;
            a->setPos(x, y);
            }

      // reserve space for slur
      bool botGap = false;
      bool topGap = false;

#if 0 // TODO-S: optimize
      for (Spanner* sp = _spannerFor; sp; sp = sp->next()) {
            if (sp->type() != SLUR)
                  continue;
            Slur* s = static_cast<Slur*>(sp);
            if (s->up())
                  topGap = true;
            else
                  botGap = true;
            }
      for (Spanner* sp = _spannerBack; sp; sp = sp->next()) {
            if (sp->type() != SLUR)
                  continue;
            Slur* s = static_cast<Slur*>(sp);
            if (s->up())
                  topGap = true;
            else
                  botGap = true;
            }
#endif
      if (botGap)
            chordBotY += _spatium;
      if (topGap)
            chordTopY -= _spatium;

      //
      //    pass 2
      //    place all articulations with anchor at chord/rest
      //
      n = _articulations.size();
      for (int i = 0; i < n; ++i) {
            Articulation* a = _articulations.at(i);
            a->layout();
            ArticulationAnchor aa = a->anchor();
            if ((a->articulationType() == ArticulationType::Tenuto)
               || (a->articulationType() == ArticulationType::Staccato))
                  continue;

            if (aa != ArticulationAnchor::CHORD && aa != ArticulationAnchor::TOP_CHORD && aa != ArticulationAnchor::BOTTOM_CHORD)
                  continue;

            // for tenuto and staccate check for staff line collision
            bool staffLineCT = a->articulationType() == ArticulationType::Tenuto
                               || a->articulationType() == ArticulationType::Staccato;

//            qreal sh = a->bbox().height() * mag();
            bool bottom = (aa == ArticulationAnchor::BOTTOM_CHORD) || (aa == ArticulationAnchor::CHORD && up());

            dy += distance1;
            if (bottom) {
                  qreal y = chordBotY + dy;
                  if (staffLineCT && (y <= staffBotY -.1 - dy)) {
                        qreal l = y / _spatium;
                        qreal delta = fabs(l - round(l));
                        if (delta < 0.4) {
                              y  += _spatium * .5;
                              dy += _spatium * .5;
                              }
                        }
                  a->setPos(x, y); // - a->bbox().y() + a->bbox().height() * .5);
                  }
            else {
                  qreal y = chordTopY - dy;
                  if (staffLineCT && (y >= (staffTopY +.1 + dy))) {
                        qreal l = y / _spatium;
                        qreal delta = fabs(l - round(l));
                        if (delta < 0.4) {
                              y  -= _spatium * .5;
                              dy += _spatium * .5;
                              }
                        }
                  a->setPos(x, y); // + a->bbox().y() - a->bbox().height() * .5);
                  }
            }

      //
      //    pass 3
      //    now place all articulations with staff top or bottom anchor
      //
      qreal dyTop = staffTopY;
      qreal dyBot = staffBotY;

/*      if ((upPos() - _spatium) < dyTop)
            dyTop = upPos() - _spatium;
      if ((downPos() + _spatium) > dyBot)
            dyBot = downPos() + _spatium;
  */
      for (int i = 0; i < n; ++i) {
            Articulation* a = _articulations.at(i);
            ArticulationAnchor aa = a->anchor();
            if (aa == ArticulationAnchor::TOP_STAFF || aa == ArticulationAnchor::BOTTOM_STAFF) {
                  if (a->up()) {
                        a->setPos(x, dyTop);
                        dyTop -= distance0;
                        }
                  else {
                        a->setPos(x, dyBot);
                        dyBot += distance0;
                        }
                  }
            a->adjustReadPos();
            }
      }