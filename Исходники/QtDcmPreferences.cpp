void QtDcmPreferences::writeSettings()
{
    //Remove settings file
    QFile ini ( d->iniFile.fileName() );
    ini.remove();
    //Instantiate a QSettings object with the ini file.
    QSettings prefs ( d->iniFile.fileName(), QSettings::IniFormat );
    //Write local settings from the private attributes
    prefs.beginGroup ( "LocalSettings" );
    prefs.setValue ( "AETitle", d->aetitle );
    prefs.setValue ( "Port", d->port );
    prefs.setValue ( "Hostname", d->hostname );
    prefs.endGroup();

    prefs.beginGroup ( "Converter" );
    prefs.setValue ( "Dcm2nii", d->dcm2niiPath );
    prefs.setValue ( "UseDcm2nii", d->useDcm2nii );
    prefs.endGroup();

    //Do the job for each server
    prefs.beginGroup ( "Servers" );
    for ( int i = 0; i < d->servers.size(); i++ )
    {
        prefs.beginGroup ( "Server" + QString::number ( i + 1 ) );
        prefs.setValue ( "AETitle", d->servers.at ( i )->getAetitle() );
        prefs.setValue ( "Hostname", d->servers.at ( i )->getServer() );
        prefs.setValue ( "Port", d->servers.at ( i )->getPort() );
        prefs.setValue ( "Name", d->servers.at ( i )->getName() );
        prefs.endGroup();
    }

    prefs.endGroup();

    emit preferencesUpdated();
}