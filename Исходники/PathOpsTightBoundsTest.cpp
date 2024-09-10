static void testTightBoundsLines(PathOpsThreadState* data) {
    SkRandom ran;
    for (int index = 0; index < 1000; ++index) {
        SkPath path;
        int contourCount = ran.nextRangeU(1, 10);
        for (int cIndex = 0; cIndex < contourCount; ++cIndex) {
            int lineCount = ran.nextRangeU(1, 10);
            path.moveTo(ran.nextRangeF(-1000, 1000), ran.nextRangeF(-1000, 1000));
            for (int lIndex = 0; lIndex < lineCount; ++lIndex) {
                path.lineTo(ran.nextRangeF(-1000, 1000), ran.nextRangeF(-1000, 1000));
            }
            if (ran.nextBool()) {
                path.close();
            }
        }
        SkRect classicBounds = path.getBounds();
        SkRect tightBounds;
        REPORTER_ASSERT(data->fReporter, TightBounds(path, &tightBounds));
        REPORTER_ASSERT(data->fReporter, classicBounds == tightBounds);
    }
}