void TestTools::undoChangeVoice()
      {
      QString readFile(DIR + "undoChangeVoice.mscx");
      QString writeFile1("undoChangeVoice01-test.mscx");
      QString reference1(DIR  + "undoChangeVoice01-ref.mscx");
      QString writeFile2("undoChangeVoice02-test.mscx");
      QString reference2(DIR  + "undoChangeVoice02-ref.mscx");

      Score* score = readScore(readFile);
      score->doLayout();

      // do
      score->deselectAll();
      // select bottom note of all voice 1 chords
      for (Segment* s = score->firstSegment(Segment::Type::ChordRest); s; s = s->next1()) {
            ChordRest* cr = static_cast<ChordRest*>(s->element(0));
            if (cr && cr->type() == Element::Type::CHORD) {
                  Ms::Chord* c = static_cast<Ms::Chord*>(cr);
                  score->select(c->downNote(), SelectType::ADD);
                  }
            }
      // change voice
      score->changeVoice(1);
      QVERIFY(saveCompareScore(score, writeFile1, reference1));

      // undo
      score->undo()->undo();
      QVERIFY(saveCompareScore(score, writeFile2, reference2));

      delete score;
      }