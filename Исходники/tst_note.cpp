void TestNote::grace()
      {
      MasterScore* score = readScore(DIR + "grace.mscx");
      score->doLayout();
      Ms::Chord* chord = score->firstMeasure()->findChord(0, 0);
      Note* note = chord->upNote();

      // create
      score->setGraceNote(chord, note->pitch(), NoteType::APPOGGIATURA, MScore::division/2);
      Ms::Chord* gc = chord->graceNotes().first();
      Note* gn = gc->notes().front();
//      Note* n = static_cast<Note*>(writeReadElement(gn));
//      QCOMPARE(n->noteType(), NoteType::APPOGGIATURA);
//      delete n;

      // tie
      score->select(gn);
      score->cmdAddTie();
//      n = static_cast<Note*>(writeReadElement(gn));
//      QVERIFY(n->tieFor() != 0);
//      delete n;

      // tremolo
      score->startCmd();
      Tremolo* tr = new Tremolo(score);
      tr->setTremoloType(TremoloType::R16);
      tr->setParent(gc);
      tr->setTrack(gc->track());
      score->undoAddElement(tr);
      score->endCmd();
//      Ms::Chord* c = static_cast<Ms::Chord*>(writeReadElement(gc));
//      QVERIFY(c->tremolo() != 0);
//      delete c;

      // articulation
      score->startCmd();
      Articulation* ar = new Articulation(SymId::articAccentAbove, score);
      ar->setParent(gc);
      ar->setTrack(gc->track());
      score->undoAddElement(ar);
      score->endCmd();
//      c = static_cast<Ms::Chord*>(writeReadElement(gc));
//      QVERIFY(c->articulations().size() == 1);
//      delete c;

      QVERIFY(saveCompareScore(score, "grace-test.mscx", DIR + "grace-ref.mscx"));
      }