void MTrack::processPendingNotes(QList<MidiChord> &midiChords,
                                 int voice,
                                 const Fraction &startChordTickFrac,
                                 const Fraction &nextChordTick)
      {
      Score* score     = staff->score();
      int track        = staff->idx() * VOICES + voice;
      Drumset* drumset = staff->part()->instr()->drumset();
      bool useDrumset  = staff->part()->instr()->useDrumset();
                  // all midiChords here should have the same onTime value
                  // and all notes in each midiChord should have the same duration
      Fraction startChordTick = startChordTickFrac;
      while (!midiChords.isEmpty()) {
            Fraction tick = startChordTick;
            Fraction len = nextChordTick - tick;
            if (len <= Fraction(0))
                  break;
            len = findMinDuration(midiChords, len);
            Measure* measure = score->tick2measure(tick.ticks());
            len = splitDurationOnBarBoundary(len, tick, measure);

            auto dl = toDurationList(measure, voice, tick, len, Meter::DurationType::NOTE);
            if (dl.isEmpty())
                  break;
            const TDuration &d = dl[0].second;
            const Fraction &tupletRatio = dl[0].first;
            len = d.fraction() / tupletRatio;

            Chord* chord = new Chord(score);
            chord->setTrack(track);
            chord->setDurationType(d);
            chord->setDuration(d.fraction());
            Segment* s = measure->getSegment(chord, tick.ticks());
            s->add(chord);
            chord->setUserPlayEvents(true);
            addElementToTuplet(voice, tick, len, chord);

            for (int k = 0; k < midiChords.size(); ++k) {
                  MidiChord& midiChord = midiChords[k];
                  setMusicNotesFromMidi(score, midiChord.notes, startChordTick,
                                        len, chord, tick, drumset, useDrumset);
                  if (!midiChord.notes.empty() && midiChord.notes.first().len <= len) {
                        midiChords.removeAt(k);
                        --k;
                        continue;
                        }
                  setTies(chord, score, midiChord.notes);
                  for (auto &midiNote: midiChord.notes)
                        midiNote.len -= len;
                  }
            startChordTick += len;
            }
      fillGapWithRests(score, voice, startChordTick,
                       nextChordTick - startChordTick, track);
      }