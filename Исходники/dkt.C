void
DKTPlate :: computeMidPlaneNormal(FloatArray &answer, const GaussPoint *gp)
// returns normal vector to midPlane in GaussPoinr gp of receiver
{
    FloatArray u, v;
    u.beDifferenceOf( * this->giveNode(2)->giveCoordinates(), * this->giveNode(1)->giveCoordinates() );
    v.beDifferenceOf( * this->giveNode(3)->giveCoordinates(), * this->giveNode(1)->giveCoordinates() );

    answer.beVectorProductOf(u, v);
    answer.normalize();
}