qreal SunLocator::shading(qreal lon, qreal a, qreal c) const
{
    // haversine formula
    qreal b = sin((lon-d->m_lon)/2.0);
//    qreal g = sin((lat-d->m_lat)/2.0);
//    qreal h = (g*g)+cos(lat)*cos(d->m_lat)*(b*b); 
    qreal h = (a*a) + c * (b*b); 

    /*
      h = 0.0 // directly beneath sun
      h = 0.5 // sunrise/sunset line
      h = 1.0 // opposite side of earth to the sun
      theta = 2*asin(sqrt(h))
    */

    qreal twilightZone = 0.0;

    QString planetId = d->m_planet->id();
    if ( planetId == "earth" || planetId == "venus") {
        twilightZone = 0.1; // this equals 18 deg astronomical twilight.
    }
    else if ( planetId == "mars" ) {
        twilightZone = 0.05;
    }

    qreal brightness;
    if ( h <= 0.5 - twilightZone / 2.0 )
        brightness = 1.0;
    else if ( h >= 0.5 + twilightZone / 2.0 )
        brightness = 0.0;
    else
        brightness = ( 0.5 + twilightZone/2.0 - h ) / twilightZone;

    return brightness;
}