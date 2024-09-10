void
InterfaceElem1d :: computeLocalSlipDir(FloatArray &normal)
{
    normal.resizeWithValues(3);
    if ( this->referenceNode ) {
        // normal
        normal.at(1) = domain->giveNode(this->referenceNode)->giveCoordinate(1) - this->giveNode(1)->giveCoordinate(1);
        normal.at(2) = domain->giveNode(this->referenceNode)->giveCoordinate(2) - this->giveNode(1)->giveCoordinate(2);
        normal.at(3) = domain->giveNode(this->referenceNode)->giveCoordinate(3) - this->giveNode(1)->giveCoordinate(3);
    } else {
        if ( normal.at(1) == 0 && normal.at(2) == 0 && normal.at(3) == 0 ) {
            _error("computeLocalSlipDir: normal is not defined (referenceNode=0,normal=(0,0,0))");
        }
    }

    normal.normalize();
}