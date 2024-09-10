void DocumentList::reloadAppLnks()
{
    if ( d->sendAppLnks && d->serverGui ) {
    d->serverGui->applicationScanningProgress( 0 );
    d->serverGui->allApplicationsRemoved();
    }

    delete appLnkSet;
    appLnkSet = new AppLnkSet( MimeType::appsFolderName() );

    if ( d->sendAppLnks && d->serverGui ) {
    static QStringList prevTypeList;
    QStringList types = appLnkSet->types();
    for ( QStringList::Iterator ittypes=types.begin(); ittypes!=types.end(); ++ittypes) {
        if ( !(*ittypes).isEmpty() ) {
        if ( !prevTypeList.contains(*ittypes) ) {
            QString name = appLnkSet->typeName(*ittypes);
            QPixmap pm = appLnkSet->typePixmap(*ittypes);
            QPixmap bgPm = appLnkSet->typeBigPixmap(*ittypes);

            if (pm.isNull())
            {
                pm = OResource::loadImage( "UnknownDocument", OResource::SmallIcon );
                bgPm = OResource::loadImage( "UnknownDocument", OResource::BigIcon );
            }

            //FIXME our current launcher expects docs tab to be last
            d->serverGui->typeAdded( *ittypes, name.isNull() ? (*ittypes) : name, pm, bgPm );
        }
        prevTypeList.remove(*ittypes);
        }
    }
    for ( QStringList::Iterator ittypes=prevTypeList.begin(); ittypes!=prevTypeList.end(); ++ittypes) {
        d->serverGui->typeRemoved(*ittypes);
    }
    prevTypeList = types;
    }

    QListIterator<AppLnk> itapp( appLnkSet->children() );
    AppLnk* l;
    while ( (l=itapp.current()) ) {
    ++itapp;
    if ( d->sendAppLnks && d->serverGui )
        d->serverGui->applicationAdded( l->type(), *l );
    }

    if ( d->sendAppLnks && d->serverGui )
    d->serverGui->applicationScanningProgress( 100 );
}