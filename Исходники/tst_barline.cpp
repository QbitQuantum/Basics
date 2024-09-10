void TestBarline::barline05()
      {
      Score* score = readScore(DIR + "barline05.mscx");
      QVERIFY(score);
      score->doLayout();

      // 'go' to 4th measure
      Measure* msr = score->firstMeasure();
      for (int i=0; i < 3; i++)
            msr = msr->nextMeasure();
      // create and add a LineBreak element
      LayoutBreak* lb = new LayoutBreak(score);
      lb->setLayoutBreakType(LayoutBreak::Type::LINE);
      lb->setTrack(-1);             // system-level element
      lb->setParent(msr);
      score->undoAddElement(lb);
      score->doLayout();

      // check an end-repeat bar line has been created at the end of this measure and it is generated
      Segment* seg = msr->findSegment(SegmentType::EndBarLine, msr->tick()+msr->ticks());
      QVERIFY2(seg != nullptr, "No SegEndBarLine segment in measure 4.");
      BarLine* bar = static_cast<BarLine*>(seg->element(0));
      QVERIFY2(bar != nullptr, "No end-repeat barline in measure 4.");
      QVERIFY2(bar->barLineType() == BarLineType::END_REPEAT, "Barline at measure 4 is not END-REPEAT");
      QVERIFY2(bar->generated(), "End-repeat barline in measure 4 is non-generated.");

      // // check an end-repeat bar line has been created at the beginning of the next measure and it is not generated
      // check an end-repeat bar line has been created at the beginning of the next measure and it is generated
      msr = msr->nextMeasure();
      seg = msr->findSegment(SegmentType::StartRepeatBarLine, msr->tick());
      QVERIFY2(seg != nullptr, "No SegStartRepeatBarLine segment in measure 5.");
      bar = static_cast<BarLine*>(seg->element(0));
      QVERIFY2(bar != nullptr, "No start-repeat barline in measure 5.");
      QVERIFY2(bar->generated(), "Start-reapeat barline in measure 5 is not generated.");

//      QVERIFY(saveCompareScore(score, "barline05.mscx", DIR + "barline05-ref.mscx"));
      delete score;
      }