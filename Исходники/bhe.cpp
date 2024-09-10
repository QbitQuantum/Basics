void bhe::logBeacon ( const char * pDiagnostic, 
                     const double & currentPeriod,
                     const epicsTime & currentTime )
{
    if ( this->pIIU ) {
        char name[64];
        this->name ( name, sizeof ( name ) );
        char date[64];
        currentTime.strftime ( date, sizeof ( date ), 
            "%a %b %d %Y %H:%M:%S.%f");
        ::printf ( "%s cp=%g ap=%g %s %s\n",
            pDiagnostic, currentPeriod, 
            this->averagePeriod, name, date );
    }
}