void
IntElPoint :: computeLocalSlipDir(FloatArray &normal)
{
    normal.resizeWithValues(3);
    if ( this->referenceNode ) {
        // normal
        normal.beDifferenceOf(*domain->giveNode(this->referenceNode)->giveCoordinates(), *this->giveNode(1)->giveCoordinates());
    } else {
        if ( normal.at(1) == 0 && normal.at(2) == 0 && normal.at(3) == 0 ) {
            OOFEM_ERROR("Normal is not defined (referenceNode=0,normal=(0,0,0))");
        }
    }

    normal.normalize();
}