void testInstance(ULength instY, ULength targetY, ULength fromY, ULength toY, ULength horizDist, ULength inch, QList<TapingMethodMeasurement> tape) {
    WallsUnits units;
    units.setInch(inch);

    units.setIncd(ULength(1, Length::Inches));
    units.setIncs(ULength(1, Length::Inches));
    units.setIncv(UAngle(2, Angle::Degrees));
    units.setTape(tape);

    INFO( "instY: " << instY );
    INFO( "targetY: " << targetY );
    INFO( "fromY: " << fromY );
    INFO( "toY: " << toY );
    INFO( "horizDist: " << horizDist );
    INFO( "inch: " << inch );

    ULength tapeFromY = tape[0] == TapingMethodMeasurement::InstrumentHeight ? instY : fromY;
    ULength tapeToY   = tape[1] == TapingMethodMeasurement::TargetHeight     ? targetY : toY;

    Vector vector;
    vector.setDistance(usqrt(usq(horizDist) + usq(tapeToY - tapeFromY)) - units.incd());
    vector.setFrontAzimuth(UAngle(0, Angle::Degrees) - units.inca());
    if (horizDist.isNonzero() && targetY != instY) {
        vector.setFrontInclination(uatan((targetY - instY) / horizDist) - units.incv());
    }
    vector.setInstHeight(instY - fromY - units.incs());
    vector.setTargetHeight(targetY - toY - units.incs());
    vector.setUnits(units);

    ULength expectedDist = usqrt(usq(toY + inch - fromY) + usq(horizDist));
    UAngle  expectedInc  = uatan2((toY + inch - fromY), horizDist);

    ULength instHeightAboveTape = instY - tapeFromY;
    ULength targetHeightAboveTape = targetY - tapeToY;

    bool isDiveShot = tape[0] == TapingMethodMeasurement::Station &&
            tape[1] == TapingMethodMeasurement::Station &&
            (!vector.frontInclination().isValid() || vector.frontInclination().isZero());

    if (!isDiveShot && uabs(instHeightAboveTape - targetHeightAboveTape) > vector.distance()) {
        CHECK_THROWS( vector.applyHeightCorrections() );
    }
    else {
        vector.applyHeightCorrections();
        CHECK( (vector.distance() + units.incd()).get(Length::Meters) == Approx( expectedDist.get(Length::Meters) ) );
        CHECK( (vector.frontInclination() + units.incv()).get(Angle::Degrees) == Approx( expectedInc.get(Angle::Degrees) ) );
    }
}