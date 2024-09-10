nsresult nsXPInstallManager::InstallItems()
{
    nsresult rv;
    nsCOMPtr<nsIZipReader> hZip = do_CreateInstance(kZipReaderCID, &rv);
    NS_ENSURE_SUCCESS(rv, rv);
    nsCOMPtr<nsIExtensionManager> em = do_GetService("@mozilla.org/extensions/manager;1", &rv);
    NS_ENSURE_SUCCESS(rv, rv);

    // can't cancel from here on cause we can't undo installs in a multitrigger
    for (PRUint32 i = 0; i < mTriggers->Size(); ++i)
    {
        mItem = (nsXPITriggerItem*)mTriggers->Get(i);
        if ( !mItem || !mItem->mFile )
        {
            // notification for these errors already handled
            continue;
        }

        // If there was hash info in the trigger, but
        // there wasn't a hash object created, then the
        // algorithm used isn't known.

        if (mItem->mHashFound && !mItem->mHasher)
        {
            // report failure
            mTriggers->SendStatus( mItem->mURL.get(), nsInstall::INVALID_HASH_TYPE );
            if (mDlg)
                mDlg->OnStateChange( i, nsIXPIProgressDialog::INSTALL_DONE,
                                     nsInstall::INVALID_HASH_TYPE );
            continue;
        }

        // Don't install if we can't verify the hash (if specified)
        if (mItem->mHasher && !VerifyHash(mItem))
        {
            // report failure
            mTriggers->SendStatus( mItem->mURL.get(), nsInstall::INVALID_HASH );
            if (mDlg)
                mDlg->OnStateChange( i, nsIXPIProgressDialog::INSTALL_DONE,
                                     nsInstall::INVALID_HASH );
            continue;
        }

        if (mDlg)
            mDlg->OnStateChange( i, nsIXPIProgressDialog::INSTALL_START, 0 );

        PRInt32 finalStatus = OpenAndValidateArchive( hZip,
                                                      mItem->mFile,
                                                      mItem->mPrincipal);
        hZip->Close();

        if (finalStatus == nsInstall::SUCCESS)
        {
            rv = em->InstallItemFromFile( mItem->mFile,
                                          NS_INSTALL_LOCATION_APPPROFILE);
            if (NS_FAILED(rv))
                finalStatus = nsInstall::EXECUTION_ERROR;
        }

        mTriggers->SendStatus( mItem->mURL.get(), finalStatus );
        if (mDlg)
            mDlg->OnStateChange( i, nsIXPIProgressDialog::INSTALL_DONE,
                                 finalStatus );
    }
    return NS_OK;
}