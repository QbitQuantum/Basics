void
SoBillboard::getMatrix(SoGetMatrixAction *action)
//
////////////////////////////////////////////////////////////////////////
{
    //if (! rotation.isIgnored() && ! rotation.isDefault()) {
    SbRotation rot = calculateRotation(action->getState());
    SbMatrix &ctm = action->getMatrix();
    SbMatrix &inv = action->getInverse();
    SbMatrix m;

    rot.getValue(m);
    ctm.multLeft(m);
    rot.invert();
    rot.getValue(m);
    inv.multRight(m);
    //}
}