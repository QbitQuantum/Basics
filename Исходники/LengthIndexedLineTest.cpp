    void runOffsetTest(string const& inputWKT, string const& testPtWKT,
                       double offsetDistance, string const& expectedPtWKT)
    {
        GeomPtr input(reader.read(inputWKT));
        GeomPtr testPoint(reader.read(testPtWKT));
        GeomPtr expectedPoint(reader.read(expectedPtWKT));
        const Coordinate* testPt = testPoint->getCoordinate();
        const Coordinate* expectedPt = expectedPoint->getCoordinate();
        Coordinate offsetPt = extractOffsetAt(input.get(), *testPt, offsetDistance);

        bool isOk = offsetPt.distance(*expectedPt) < TOLERANCE_DIST;
        if (! isOk)
            cout << "Expected = " << *expectedPoint << "  Actual = " << offsetPt << endl;
        ensure(isOk);
    }