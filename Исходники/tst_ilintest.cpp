void IlinTest::test_translation()
{
    double radians = 0.5;
    Angle angle;
    translation(radians, &angle);
    QCOMPARE(angle.degree, 28);
    QCOMPARE(angle.min, 39);
    QCOMPARE(angle.sec, 44);

}