void tst_QPainterPath::testStroker()
{
    QFETCH(QPainterPath, path);
    QFETCH(QPen, pen);
    QFETCH(QPainterPath, stroke);

    QPainterPathStroker stroker;
    stroker.setWidth(pen.widthF());
    stroker.setCapStyle(pen.capStyle());
    stroker.setJoinStyle(pen.joinStyle());
    stroker.setMiterLimit(pen.miterLimit());
    stroker.setDashPattern(pen.style());
    stroker.setDashOffset(pen.dashOffset());

    QPainterPath result = stroker.createStroke(path);

    // check if stroke == result
    QVERIFY(result.subtracted(stroke).isEmpty());
    QVERIFY(stroke.subtracted(result).isEmpty());
}