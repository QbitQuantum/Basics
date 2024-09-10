void TestLinks::test5LinkedParts_94911()
      {
      MCursor c;
      c.setTimeSig(Fraction(4,4));
      c.createScore("test");
      c.addPart("electric-guitar");
      c.move(0, 0);     // move to track 0 tick 0

      c.addKeySig(Key(1));
      c.addTimeSig(Fraction(4,4));
      c.addChord(60, TDuration(TDuration::DurationType::V_WHOLE));

      MasterScore* score = c.score();
      score->addText("title", "Title");
      score->doLayout();
      // delete chord
      Measure* m = score->firstMeasure();
      Segment* s = m->first(Segment::Type::ChordRest);
      Element* e = s->element(0);
      QVERIFY(e->type() == ElementType::CHORD);
      score->select(e);
      score->cmdDeleteSelection();
      e = s->element(0);
      QVERIFY(e->type() == ElementType::REST);
      QVERIFY(e->links() == nullptr);

      // create parts//
      score->startCmd();
      QList<Part*> parts;
      parts.append(score->parts().at(0));
      Score* nscore = new Score(score);
      Excerpt ex(score);
      ex.setPartScore(nscore);
      ex.setTitle("Guitar");
      ex.setParts(parts);
      Excerpt::createExcerpt(&ex);
      QVERIFY(nscore);
      score->undo(new AddExcerpt(&ex));
      score->endCmd();

      // we should have now 1 staff and 2 linked rests
      QVERIFY(score->staves().size() == 1);
      e = s->element(0);
      QVERIFY(e->type() == ElementType::REST);
      QVERIFY(e->links()->size() == 2);

      // add a linked staff
      score->startCmd();
      Staff* oStaff = score->staff(0);
      Staff* staff       = new Staff(score);
      staff->setPart(oStaff->part());
      score->undoInsertStaff(staff, 1);
      Excerpt::cloneStaff(oStaff, staff);
      score->endCmd();

      // we should have now 2 staves and 3 linked rests
      QCOMPARE(score->staves().size(), 2);
      QCOMPARE(nscore->staves().size(), 1);
      QVERIFY(score->staves()[0]->linkedStaves()->staves().size() == 3);
      e = s->element(0);
      QVERIFY(e->type() == ElementType::REST);
      QVERIFY(e->links()->size() == 3);
      e = s->element(4);
      QVERIFY(e->type() == ElementType::REST);
      QVERIFY(e->links()->size() == 3);
      QVERIFY(score->excerpts().size() == 1);

      // undo
      score->undoStack()->undo();
      // we should have now 1 staves and 2 linked rests
      QVERIFY(score->staves().size() == 1);
      QVERIFY(score->staves()[0]->linkedStaves()->staves().size() == 2);
      e = s->element(0);
      QVERIFY(e->type() == ElementType::REST);
      QVERIFY(e->links()->size() == 2);
      QVERIFY(score->excerpts().size() == 1);

      // redo
      score->undoStack()->redo();
      // we should have now 2 staves and 3 linked rests
      QVERIFY(score->staves().size() == 2);
      QVERIFY(score->staves()[0]->linkedStaves()->staves().size() == 3);
      e = s->element(0);
      QVERIFY(e->type() == ElementType::REST);
      QVERIFY(e->links()->size() == 3);
      e = s->element(4);
      QVERIFY(e->type() == ElementType::REST);
      QVERIFY(e->links()->size() == 3);
      QVERIFY(score->excerpts().size() == 1);
      }