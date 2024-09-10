void Clef::layout()
      {
      // determine current number of lines and line distance
      int   lines;
      qreal lineDist;
      Segment* clefSeg  = segment();
      int stepOffset;

      // check clef visibility and type compatibility
      if (clefSeg && staff()) {
            int tick             = clefSeg->tick();
            StaffType* staffType = staff()->staffType(tick);
            bool show            = staffType->genClef();        // check staff type allows clef display

            // check clef is compatible with staff type group:
            if (ClefInfo::staffGroup(clefType()) != staffType->group()) {
                  if (tick > 0 && !generated()) // if clef is not generated, hide it
                        show = false;
                  else                          // if generated, replace with initial clef type
                        // TODO : instead of initial staff clef (which is assumed to be compatible)
                        // use the last compatible clef previously found in staff
                        _clefTypes = staff()->clefType(0);
                  }

            Measure* meas = clefSeg->measure();
            if (meas && meas->system()) {
                  auto ml = meas->system()->measures();
                  bool found = (std::find(ml.begin(), ml.end(), meas) != ml.end());
                  bool courtesy = (tick == meas->endTick() && (meas == meas->system()->lastMeasure() || !found));
                  if (courtesy && (!showCourtesy() || !score()->styleB(Sid::genCourtesyClef) || meas->isFinalMeasureOfSection()))
                        show = false;
                  }
            // if clef not to show or not compatible with staff group
            if (!show) {
                  setbbox(QRectF());
                  qDebug("Clef::layout(): invisible clef at tick %d(%d) staff %d",
                     segment()->tick(), segment()->tick()/1920, staffIdx());
                  return;
                  }
            lines      = staffType->lines();         // init values from staff type
            lineDist   = staffType->lineDistance().val();
            stepOffset = staffType->stepOffset();
            }
      else {
            lines      = 5;
            lineDist   = 1.0;
            stepOffset = 0;
            }

      qreal _spatium = spatium();
      qreal yoff     = 0.0;
      if (clefType() !=  ClefType::INVALID && clefType() !=  ClefType::MAX) {
            symId = ClefInfo::symId(clefType());
            yoff = lineDist * (lines - ClefInfo::line(clefType()));
            }

      switch (clefType()) {
            case ClefType::C_19C:                            // 19th C clef is like a G clef
                  yoff = lineDist * 1.5;
                  break;
            case ClefType::TAB:                            // TAB clef
                  // on tablature, position clef at half the number of spaces * line distance
                  yoff = lineDist * (lines - 1) * .5;
                  break;
            case ClefType::TAB4:                            // TAB clef 4 strings
                  // on tablature, position clef at half the number of spaces * line distance
                  yoff = lineDist * (lines - 1) * .5;
                  break;
            case ClefType::TAB_SERIF:                           // TAB clef alternate style
                  // on tablature, position clef at half the number of spaces * line distance
                  yoff = lineDist * (lines - 1) * .5;
                  break;
            case ClefType::TAB4_SERIF:                           // TAB clef alternate style
                  // on tablature, position clef at half the number of spaces * line distance
                  yoff = lineDist * (lines - 1) * .5;
                  break;
            case ClefType::PERC:                           // percussion clefs
                  yoff = lineDist * (lines - 1) * 0.5;
                  break;
            case ClefType::PERC2:
                  yoff = lineDist * (lines - 1) * 0.5;
                  break;
            case ClefType::INVALID:
            case ClefType::MAX:
                  qDebug("Clef::layout: invalid type");
                  return;
            default:
                  break;
            }
      // clefs are right aligned to Segment
      QRectF r(symBbox(symId));
      setPos(0.0, yoff * _spatium + (stepOffset * -_spatium));

      setbbox(r);
      }