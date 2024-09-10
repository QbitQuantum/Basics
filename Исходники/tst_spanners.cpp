void TestSpanners::spanners12()
{
    MasterScore* score = readScore(DIR + "lyricsline05.mscx");
    QVERIFY(score);
    score->doLayout();

    // DELETE SECOND MEASURE AND VERIFY
    Measure*    msr   = score->firstMeasure();
    QVERIFY(msr);
    msr = msr->nextMeasure();
    QVERIFY(msr);
    score->startCmd();
    score->select(msr);
    score->cmdTimeDelete();
    score->endCmd();
    QVERIFY(saveCompareScore(score, "lyricsline05.mscx", DIR + "lyricsline05-ref.mscx"));

    // UNDO AND VERIFY
    score->undoStack()->undo();
    QVERIFY(saveCompareScore(score, "lyricsline05.mscx", DIR + "lyricsline05.mscx"));
    delete score;
}