/*
 * D3DAppIDDEnumCallback
 * Callback function used during enumeration of DirectDraw drivers.
 * During enumeration, if a 3D capable hardware device is found, it is 
 * created and *(LPDIRECTDRAW*)lpContext is set to it.  Otherwise, does
 * nothing.
 */
BOOL FAR PASCAL D3DAppIDDEnumCallback(GUID FAR* lpGUID, LPSTR lpDriverDesc,
                                      LPSTR lpDriverName, LPVOID lpContext)
{
    LPDIRECTDRAW lpDD;
    DDCAPS DriverCaps, HELCaps;
#ifdef FINAL_RELEASE
    BOOL    ThisOne = FALSE;
#endif
    /*
     * A NULL GUID* indicates the DirectDraw HEL which we are not interested
     * in at the moment.
     */
//    if (lpGUID)
    {
        /*
         * Create the DirectDraw device using this driver.  If it fails,
         * just move on to the next driver.
         */
        if (FAILED(DirectDrawCreate(lpGUID, &lpDD, NULL))) {
            return DDENUMRET_OK;
        }
        /*
         * Get the capabilities of this DirectDraw driver.  If it fails,
         * just move on to the next driver.
         */
        memset(&DriverCaps, 0, sizeof(DDCAPS));
        DriverCaps.dwSize = sizeof(DDCAPS);
        memset(&HELCaps, 0, sizeof(DDCAPS));
        HELCaps.dwSize = sizeof(DDCAPS);
        if (FAILED(lpDD->lpVtbl->GetCaps(lpDD, &DriverCaps, &HELCaps))) {
            lpDD->lpVtbl->Release(lpDD);
            return DDENUMRET_OK;
        }
#ifdef FINAL_RELEASE
        if (DriverCaps.dwCaps & DDCAPS_3D )
        {
            if( !lpGUID && !DeviceGuidPnt)
            {
                ThisOne = TRUE;
            }
            if( DeviceGuidPnt && lpGUID )
            {
                if( IsEqualGuid( lpGUID, &DeviceGuid) )
                {
                    ThisOne = TRUE;
                }
            }
            if( ThisOne )
            {
                /*
                 * We have found a 3d hardware device.  Return the DD object
                 * and stop enumeration.
                 */
                d3dappi.bIsPrimary = FALSE;
                *(LPDIRECTDRAW*)lpContext = lpDD;
                return DDENUMRET_CANCEL;
            }
        }
#else
        if (DriverCaps.dwCaps & DDCAPS_3D )
        {
            if( ddcount3d++ == ddchosen3d )
            {
                /*
                 * We have found a 3d hardware device.  Return the DD object
                 * and stop enumeration.
                 */
#ifdef ORIGINAL
                d3dappi.bIsPrimary = FALSE;
#else
                d3dappi.bIsPrimary = TRUE; // This is no longer a DD limitation.
#endif
                *(LPDIRECTDRAW*)lpContext = lpDD;
                return DDENUMRET_CANCEL;
            }
        }
#endif
        lpDD->lpVtbl->Release(lpDD);
    }
    return DDENUMRET_OK;
}