void TestSegmentTypeCommand::changeToCurve()
{
    KoPathShape path;
    path.moveTo( QPointF(0,0) );
    path.lineTo( QPointF(100,0) );

    KoPathPointData segment(&path, KoPathPointIndex(0,0));
    QList<KoPathPointData> segments;
    segments.append(segment);

    // get first segment
    KoPathSegment s = path.segmentByIndex(KoPathPointIndex(0,0));

    KoPathSegmentTypeCommand cmd(segments, KoPathSegmentTypeCommand::Curve);

    QVERIFY(!s.first()->activeControlPoint2());
    QVERIFY(!s.second()->activeControlPoint1());

    cmd.redo();

    QVERIFY(s.first()->activeControlPoint2());
    QVERIFY(s.second()->activeControlPoint1());

    cmd.undo();

    QVERIFY(!s.first()->activeControlPoint2());
    QVERIFY(!s.second()->activeControlPoint1());
}