void TestMeasure::deleteLast()
      {
      MasterScore* score = readScore(DIR + "measure-10.mscx");

      score->startCmd();
      Measure* m = score->lastMeasure();
      score->select(m);
      score->cmdTimeDelete();
      score->endCmd();

      QVERIFY(saveCompareScore(score, "measure-10.mscx", DIR + "measure-10-ref.mscx"));
      delete score;
      }