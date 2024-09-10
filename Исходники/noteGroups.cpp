Score* NoteGroups::createScore(int n, TDuration::DurationType t, std::vector<Chord*>* chords)
      {
      MCursor c;
      c.setTimeSig(_sig);
      c.createScore("score8");
      c.addPart("voice");
      c.move(0, 0);
      c.addKeySig(Key::C);
      TimeSig* nts = c.addTimeSig(_sig);
      GroupNode node {0, 0};
      Groups ng;
      ng.push_back(node);
      nts->setGroups(ng);

      for (int i = 0; i < n; ++i) {
            Chord* chord = c.addChord(67, t);
            int tick = chord->rtick();
            chord->setBeamMode(_groups.beamMode(tick, t));
            chords->push_back(chord);
            }
      c.score()->pageFormat()->setEvenLeftMargin(0.0);
      c.score()->pageFormat()->setOddLeftMargin(0.0);

      c.score()->parts().front()->setLongName("");
      c.score()->style()->set(StyleIdx::linearStretch, 1.3);
      c.score()->style()->set(StyleIdx::MusicalSymbolFont, QString("Bravura"));
      c.score()->style()->set(StyleIdx::MusicalTextFont, QString("Bravura Text"));
      return c.score();
      }