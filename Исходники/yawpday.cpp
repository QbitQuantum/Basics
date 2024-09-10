bool
CityWeather::isDayTime( const YawpDay * day ) const
{
    if( !day || !day->sunset().isValid() || !day->sunrise().isValid() )
        return true;

    QDateTime currentTime;
    if( observationPeriode().isValid() )
        currentTime = observationPeriode();
    else
        currentTime = localTime();

    QDateTime sunrise( currentTime.date(), day->sunrise() );
    QDateTime sunset( currentTime.date(), day->sunset() );

    bool bReturn = (currentTime > sunrise && currentTime  < sunset);

    dTracing() << "City: " << m_sLocalizedCity <<"   current Time:" << currentTime
               << "   sunrise:" << sunrise << "   sunset:" << sunset
               << "   daytime:" << bReturn;

    return bReturn;
}