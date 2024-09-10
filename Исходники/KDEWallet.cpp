NS_IMETHODIMP KDEWallet::SetLoginSavingEnabled(const nsAString & aHost,
        bool isEnabled) {
    PR_LOG( gKDEWalletLog, PR_LOG_DEBUG, ( "KDEWallet::SetLoginSavingEnabled() Called") );

    nsresult res = checkWallet();
    NS_ENSURE_SUCCESS(res, res);

    QMap< QString, QString > saveDisabledHostMap;

    wallet->readMap( kSaveDisabledHostsMapName, saveDisabledHostMap );
    if( isEnabled ) { //Remove form disabled list, if it is there
        if( saveDisabledHostMap.contains( NSString2QtString(aHost) ) )
            if( saveDisabledHostMap.remove( NSString2QtString(aHost) ) != 1 ) {
                NS_ERROR("Can not remove save map information");
                return NS_ERROR_FAILURE;
            }
    }
    else 	// Add to disabled list
        saveDisabledHostMap[ NSString2QtString(aHost) ] = "TRUE";
    if( wallet->writeMap( kSaveDisabledHostsMapName, saveDisabledHostMap ) ) {
        NS_ERROR("Can not save map information");
        return NS_ERROR_FAILURE;
    }
    return NS_OK;
}