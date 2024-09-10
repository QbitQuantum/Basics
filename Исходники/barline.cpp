void BarLine::getY(qreal* y1, qreal* y2) const
      {
      qreal _spatium = spatium();
      if (parent()) {
            int staffIdx1    = staffIdx();
            int staffIdx2    = staffIdx1 + _span - 1;
            if (staffIdx2 >= score()->nstaves()) {
                  qDebug("BarLine: bad _span %d", _span);
                  staffIdx2 = score()->nstaves() - 1;
                  }
            Measure* measure;
            System* system;
            qreal yp = 0.0;
            if (parent()->type() == Element::Type::SEGMENT) {
                  Segment* segment = static_cast<Segment*>(parent());
                  measure = segment->measure();
                  system  = measure->system();
                  }
            else {
                  system  = static_cast<System*>(parent());
                  measure = system->firstMeasure();
                  }
            if (measure) {
                  // test start and end staff visibility
                  int   nstaves = score()->nstaves();
                  int   span = _span;
                  Staff* staff1 = score()->staff(staffIdx1);
                  Staff* staff2 = score()->staff(staffIdx2);
                  SysStaff* sysStaff1 = system->staff(staffIdx1);
                  SysStaff* sysStaff2 = system->staff(staffIdx2);
                  while (span > 0) {
                        // if start staff not shown, reduce span and move one staff down
                        if ( !(sysStaff1->show() && staff1->show()) ) {
                              span--;
                              if (staffIdx1 >= nstaves-1)         // running out of staves?
                                    break;
                              sysStaff1 = system->staff(++staffIdx1);
                              staff1    = score()->staff(staffIdx1);
                        }
                        // if end staff not shown, reduce span and move one staff up
                        else if ( !(sysStaff2->show() && staff2->show()) ) {
                              span--;
                              if (staffIdx2 == 0)
                                    break;
                              sysStaff2 = system->staff(--staffIdx2);
                              staff2    = score()->staff(staffIdx2);
                        }
                        // if both staves shown, exit loop
                        else
                              break;
                  }
                  // if no longer any span, set 0 length and exit
                  if (span <= 0) {
                        *y1 = *y2 = 0;
                        return;
                  }
                  // both staffIdx1 and staffIdx2 are shown: compute corresponding line length
                  StaffLines* l1 = measure->staffLines(staffIdx1);
                  StaffLines* l2 = measure->staffLines(staffIdx2);

                  if (system)
                        yp += sysStaff1->y();
                  *y1 = l1->y1() - yp;
                  *y1 += (_spanFrom * staff1->lineDistance() * staff1->spatium()) / 2;
                  *y2 = l2->y1() - yp;
                  *y2 += (_spanTo   * staff2->lineDistance() * staff2->spatium()) / 2;
                  }
            }
      else {
            // for use in palette
            *y1 = _spanFrom * _spatium / 2;
            *y2 = _spanTo   * _spatium / 2;
            }

      if (selected()) {
            *y1 += yoff1;
            *y2 += yoff2;
            }
      }