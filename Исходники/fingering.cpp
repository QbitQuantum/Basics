void Fingering::layout()
      {
      if (parent()) {
            Fraction tick = parent()->tick();
            const Staff* st = staff();
            if (st && st->isTabStaff(tick) && !st->staffType(tick)->showTabFingering()) {
                  setbbox(QRectF());
                  return;
                  }
            }

      TextBase::layout();
      rypos() = 0.0;    // handle placement below

      if (autoplace() && note()) {
            Note* n      = note();
            Chord* chord = n->chord();
            bool voices  = chord->measure()->hasVoices(chord->staffIdx());
            bool tight   = voices && chord->notes().size() == 1 && !chord->beam() && tid() != Tid::STRING_NUMBER;

            qreal headWidth = n->bboxRightPos();

            // update offset after drag
            qreal rebase = 0.0;
            if (offsetChanged() != OffsetChange::NONE)
                  rebase = rebaseOffset();

            // temporarily exclude self from chord shape
            setAutoplace(false);

            if (layoutType() == ElementType::CHORD) {
                  Stem* stem = chord->stem();
                  Segment* s = chord->segment();
                  Measure* m = s->measure();
                  qreal sp = spatium();
                  qreal md = minDistance().val() * sp;
                  SysStaff* ss = m->system()->staff(chord->vStaffIdx());
                  Staff* vStaff = chord->staff();     // TODO: use current height at tick

                  if (n->mirror())
                        rxpos() -= n->ipos().x();
                  rxpos() += headWidth * .5;
                  if (placeAbove()) {
                        if (tight) {
                              if (chord->stem())
                                    rxpos() -= 0.8 * sp;
                              rypos() -= 1.5 * sp;
                              }
                        else {
                              QRectF r = bbox().translated(m->pos() + s->pos() + chord->pos() + n->pos() + pos());
                              SkylineLine sk(false);
                              sk.add(r.x(), r.bottom(), r.width());
                              qreal d = sk.minDistance(ss->skyline().north());
                              qreal yd = 0.0;
                              if (d > 0.0 && isStyled(Pid::MIN_DISTANCE))
                                    yd -= d + height() * .25;
                              // force extra space above staff & chord (but not other fingerings)
                              qreal top;
                              if (chord->up() && chord->beam() && stem) {
                                    top = stem->y() + stem->bbox().top();
                                    }
                              else {
                                    Note* un = chord->upNote();
                                    top = qMin(0.0, un->y() + un->bbox().top());
                                    }
                              top -= md;
                              qreal diff = (bbox().bottom() + ipos().y() + yd + n->y()) - top;
                              if (diff > 0.0)
                                    yd -= diff;
                              if (offsetChanged() != OffsetChange::NONE) {
                                    // user moved element within the skyline
                                    // we may need to adjust minDistance, yd, and/or offset
                                    bool inStaff = placeAbove() ? r.bottom() + rebase > 0.0 : r.top() + rebase < staff()->height();
                                    rebaseMinDistance(md, yd, sp, rebase, inStaff);
                                    }
                              rypos() += yd;
                              }
                        }
                  else {
                        if (tight) {
                              if (chord->stem())
                                    rxpos() += 0.8 * sp;
                              rypos() += 1.5 * sp;
                              }
                        else {
                              QRectF r = bbox().translated(m->pos() + s->pos() + chord->pos() + n->pos() + pos());
                              SkylineLine sk(true);
                              sk.add(r.x(), r.top(), r.width());
                              qreal d = ss->skyline().south().minDistance(sk);
                              qreal yd = 0.0;
                              if (d > 0.0 && isStyled(Pid::MIN_DISTANCE))
                                    yd += d + height() * .25;
                              // force extra space below staff & chord (but not other fingerings)
                              qreal bottom;
                              if (!chord->up() && chord->beam() && stem) {
                                    bottom = stem->y() + stem->bbox().bottom();
                                    }
                              else {
                                    Note* dn = chord->downNote();
                                    bottom = qMax(vStaff->height(), dn->y() + dn->bbox().bottom());
                                    }
                              bottom += md;
                              qreal diff = bottom - (bbox().top() + ipos().y() + yd + n->y());
                              if (diff > 0.0)
                                    yd += diff;
                              if (offsetChanged() != OffsetChange::NONE) {
                                    // user moved element within the skyline
                                    // we may need to adjust minDistance, yd, and/or offset
                                    bool inStaff = placeAbove() ? r.bottom() + rebase > 0.0 : r.top() + rebase < staff()->height();
                                    rebaseMinDistance(md, yd, sp, rebase, inStaff);
                                    }
                              rypos() += yd;
                              }
                        }
                  }
            else if (tid() == Tid::LH_GUITAR_FINGERING) {
                  // place to left of note
                  qreal left = n->shape().left();
                  if (left - n->x() > 0.0)
                        rxpos() -= left;
                  else
                        rxpos() -= n->x();
                  }
            // for other fingering styles, do not autoplace

            // restore autoplace
            setAutoplace(true);
            }
      else if (offsetChanged() != OffsetChange::NONE) {
            // rebase horizontally too, as autoplace may have adjusted it
            rebaseOffset(false);
            }
      setOffsetChanged(false);
      }