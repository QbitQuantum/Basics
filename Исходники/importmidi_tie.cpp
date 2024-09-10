bool isTied(const Segment *seg, int strack, int voice,
            Ms::Tie*(Note::*tieFunc)() const)
      {
      ChordRest *cr = static_cast<ChordRest *>(seg->element(strack + voice));
      if (cr && cr->type() == Element::Type::CHORD) {
            Chord *chord = static_cast<Chord *>(cr);
            const auto &notes = chord->notes();
            for (const Note *note: notes) {
                  if ((note->*tieFunc)())
                        return true;
                  }
            }
      return false;
      }