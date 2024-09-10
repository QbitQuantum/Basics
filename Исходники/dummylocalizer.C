void
DummySpatialLocalizer :: giveAllElementsWithIpWithinBox(elementContainerType &elemSet, const FloatArray &coords, const double radius)
{
    int nelem;
    FloatArray jGpCoords;

    nelem = this->giveDomain()->giveNumberOfElements();
    for ( int i = 1; i <= nelem; i++ ) {
        Element *ielem = this->giveDomain()->giveElement(i);
        IntegrationRule *iRule = ielem->giveDefaultIntegrationRulePtr();
        for ( GaussPoint *jGp: *iRule ) {
            if ( ielem->computeGlobalCoordinates( jGpCoords, * ( jGp->giveCoordinates() ) ) ) {
                double currDist = coords.distance(jGpCoords);
                if ( currDist <= radius ) {
                    elemSet.insert(i);
                }
            }
        }
    } // end element loop
}