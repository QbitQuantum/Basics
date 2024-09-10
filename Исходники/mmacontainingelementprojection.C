void
MMAContainingElementProjection :: __init(Domain *dold, IntArray &type, FloatArray &coords, Set &elemSet, TimeStep *tStep, bool iCohesiveZoneGP)
{
    SpatialLocalizer *sl = dold->giveSpatialLocalizer();
    FloatArray jGpCoords;
    double distance, minDist = 1.e6;
    Element *srcElem;

    if ( ( srcElem = sl->giveElementContainingPoint(coords, elemSet) ) ) {
        this->source = NULL;
        for ( GaussPoint *jGp: *srcElem->giveDefaultIntegrationRulePtr() ) {
            if ( srcElem->computeGlobalCoordinates( jGpCoords, jGp->giveNaturalCoordinates() ) ) {
                distance = coords.distance(jGpCoords);
                if ( distance < minDist ) {
                    minDist = distance;
                    this->source = jGp;
                }
            }
        }

        if ( !source ) {
            OOFEM_ERROR("no suitable source found");
        }
    } else {
        OOFEM_ERROR("No suitable element found");
    }
}