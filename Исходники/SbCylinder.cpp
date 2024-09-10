SbBool
SbCylinder::intersect(const SbLine &line, SbVec3f &enter, SbVec3f &exit) const
//
////////////////////////////////////////////////////////////////////////
{
    // The intersection will actually be done on a radius 1 cylinder
    // aligned with the y axis, so we transform the line into that
    // space, then intersect, then transform the results back.

    // rotation to y axis
    SbRotation	rotToYAxis(axis.getDirection(), SbVec3f(0,1,0));
    SbMatrix	mtxToYAxis;
    mtxToYAxis.setRotate(rotToYAxis);

    // scale to unit space
    float	scaleFactor = 1.0f/radius;
    SbMatrix	toUnitCylSpace;
    toUnitCylSpace.setScale(SbVec3f(scaleFactor, scaleFactor, scaleFactor));
    toUnitCylSpace.multLeft(mtxToYAxis);

    // find the given line un-translated
    SbVec3f origin = line.getPosition();
    origin -= axis.getPosition();
    SbLine noTranslationLine(origin, origin + line.getDirection());

    // find the un-translated line in unit cylinder's space
    SbLine cylLine;
    toUnitCylSpace.multLineMatrix(noTranslationLine, cylLine);

    // find the intersection on the unit cylinder
    SbVec3f cylEnter, cylExit;
    SbBool intersected = unitCylinderIntersect(cylLine, cylEnter, cylExit);

    if (intersected) {
        // transform back to original space
        SbMatrix fromUnitCylSpace = toUnitCylSpace.inverse();

        fromUnitCylSpace.multVecMatrix(cylEnter, enter);
        enter += axis.getPosition();

        fromUnitCylSpace.multVecMatrix(cylExit, exit);
        exit += axis.getPosition();
    }

    return intersected;
}