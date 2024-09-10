void MsScWriter::note(const QString pitch, const QVector<Bww::BeamType> beamList,
                      const QString type, const int dots,
                      bool tieStart, bool /*TODO tieStop */,
                      StartStop triplet,
                      bool grace)
      {
      qDebug() << "MsScWriter::note()"
               << "type:" << type
               << "dots:" << dots
               << "grace" << grace
      ;

      if (!stepAlterOctMap.contains(pitch)
          || !typeMap.contains(type)) {
            // TODO: error message
            return;
            }
      StepAlterOct sao = stepAlterOctMap.value(pitch);

      int ticks = 4 * Ms::MScore::division / type.toInt();
      if (dots) ticks = 3 * ticks / 2;
      qDebug() << "ticks:" << ticks;
      Ms::TDuration durationType(Ms::TDuration::DurationType::V_INVALID);
      durationType.setVal(ticks);
      qDebug() << "duration:" << durationType.name();
      if (triplet != ST_NONE) ticks = 2 * ticks / 3;

      Ms::Beam::Mode bm  = (beamList.at(0) == Bww::BM_BEGIN) ? Ms::Beam::Mode::BEGIN : Ms::Beam::Mode::AUTO;
      Ms::Direction sd = Ms::Direction::AUTO;

      // create chord
      Ms::Chord* cr = new Ms::Chord(score);
      //ws cr->setTick(tick);
      cr->setBeamMode(bm);
      cr->setTrack(0);
      if (grace) {
            cr->setNoteType(Ms::NoteType::GRACE32);
            cr->setDurationType(Ms::TDuration::DurationType::V_32ND);
            sd = Ms::Direction::UP;
            }
      else {
            if (durationType.type() == Ms::TDuration::DurationType::V_INVALID)
                  durationType.setType(Ms::TDuration::DurationType::V_QUARTER);
            cr->setDurationType(durationType);
            sd = Ms::Direction::DOWN;
            }
      cr->setDuration(durationType.fraction());
      cr->setDots(dots);
      cr->setStemDirection(sd);
      // add note to chord
      Ms::Note* note = new Ms::Note(score);
      note->setTrack(0);
      xmlSetPitch(note, sao.s.toLatin1(), sao.a, sao.o);
      if (tieStart) {
            Ms::Tie* tie = new Ms::Tie(score);
            note->setTieFor(tie);
            tie->setStartNote(note);
            tie->setTrack(0);
            }
      cr->add(note);
      // add chord to measure
      if (!grace) {
            Ms::Segment* s = currentMeasure->getSegment(cr, tick);
            s->add(cr);
            if (!currentGraceNotes.isEmpty()) {
                  for (int i = currentGraceNotes.size() - 1; i >=0; i--)
                        cr->add(currentGraceNotes.at(i));
                  currentGraceNotes.clear();
                  }
            doTriplet(cr, triplet);
            int tickBefore = tick;
            tick += ticks;
            Ms::Fraction nl(Ms::Fraction::fromTicks(tick - currentMeasure->tick()));
            currentMeasure->setLen(nl);
            qDebug() << "MsScWriter::note()"
                     << "tickBefore:" << tickBefore
                     << "tick:" << tick
                     << "nl:" << nl.print()
            ;
            }
      else {
            currentGraceNotes.append(cr);
            }
      }