void DrumTools::updateDrumset(const Drumset* ds)
      {
      drumPalette->clear();
      drumset = ds;
      if (!drumset)
            return;
      double _spatium = gscore->spatium();
      for (int pitch = 0; pitch < 128; ++pitch) {
            if (!drumset->isValid(pitch))
                  continue;
            bool up;
            int line      = drumset->line(pitch);
            NoteHead::Group noteHead  = drumset->noteHead(pitch);
            int voice     = drumset->voice(pitch);
            Direction dir = drumset->stemDirection(pitch);
            if (dir == Direction::UP)
                  up = true;
            else if (dir == Direction::DOWN)
                  up = false;
            else
                  up = line > 4;

            Chord* chord = new Chord(gscore);
            chord->setDurationType(TDuration::DurationType::V_QUARTER);
            chord->setStemDirection(dir);
            chord->setUp(up);
            chord->setTrack(voice);
            Note* note = new Note(gscore);
            note->setParent(chord);
            note->setTrack(voice);
            note->setPitch(pitch);
            note->setTpcFromPitch();
            note->setLine(line);
            note->setPos(0.0, _spatium * .5 * line);
            note->setHeadGroup(noteHead);
            chord->add(note);
            Stem* stem = new Stem(gscore);
            stem->setLen((up ? -3.0 : 3.0) * _spatium);
            chord->add(stem);
            stem->setPos(chord->stemPos());
            int sc = drumset->shortcut(pitch);
            QString shortcut;
            if (sc)
                  shortcut = QChar(sc);
            drumPalette->append(chord, qApp->translate("drumset", drumset->name(pitch).toLatin1().data()), shortcut);
            }
      }