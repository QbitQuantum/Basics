void EditDrumset::updateExample()
      {
      int pitch = pitchList->currentItem()->data(0, Qt::UserRole).toInt();
      if (!nDrumset.isValid(pitch)) {
            drumNote->add(0,  0, "");
            return;
            }
      int line      = nDrumset.line(pitch);
      NoteHead::Group noteHead = nDrumset.noteHead(pitch);
      int voice     = nDrumset.voice(pitch);
      MScore::Direction dir = nDrumset.stemDirection(pitch);
      bool up;
      if (dir == MScore::Direction::UP)
            up = true;
      else if (dir == MScore::Direction::DOWN)
            up = false;
      else
            up = line > 4;
      Chord* chord = new Chord(gscore);
      chord->setDurationType(TDuration::DurationType::V_QUARTER);
      chord->setStemDirection(dir);
      chord->setTrack(voice);
      chord->setUp(up);
      Note* note = new Note(gscore);
      note->setParent(chord);
      note->setTrack(voice);
      note->setPitch(pitch);
      note->setTpcFromPitch();
      note->setLine(line);
      note->setPos(0.0, gscore->spatium() * .5 * line);
      note->setHeadGroup(noteHead);
      chord->add(note);
      Stem* stem = new Stem(gscore);
      stem->setLen((up ? -3.0 : 3.0) * gscore->spatium());
      chord->add(stem);
      stem->setPos(chord->stemPos());
      drumNote->add(0,  chord, qApp->translate("drumset", nDrumset.name(pitch).toUtf8().constData()));
      }