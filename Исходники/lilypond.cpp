void Lilypond::addNote(const LNote& lnote)
      {
      createMeasure();

      Segment* segment = new Segment(measure);
      segment->setSubtype(SegChordRest);
      segment->setTick(tick);
      segment->setParent(measure);
      measure->add(segment);

      Chord* chord = new Chord(score);
      chord->setTrack(staff->idx() * VOICES);
      chord->setParent(segment);
      Duration d;
      d.setVal(lnote.len);
      chord->setDurationType(d);

      segment->add(chord);

      Note* note = new Note(score);
      note->setPitch(lnote.pitch);
      note->setTpcFromPitch();
      note->setParent(chord);
      note->setTrack(staff->idx() * VOICES);
      chord->add(note);
      tick += lnote.len;
      }