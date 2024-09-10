int fb_PrinterOpen( DEV_LPT_INFO *devInfo, int iPort, const char *pszDevice )
{
    int result = fb_ErrorSetNum( FB_RTERROR_OK );
    const DEV_PRINTER_EMU_MODE *pFoundEmu = NULL;
    DWORD dwJob = 0;
    BOOL fResult;
    HANDLE hPrinter = NULL;
    HDC hDc = NULL;

		char *printer_name = NULL;
		char *doc_title = NULL;

		DEV_LPT_PROTOCOL *lpt_proto;
		if ( !fb_DevLptParseProtocol( &lpt_proto, pszDevice, strlen(pszDevice), TRUE ) )
		{
			if( lpt_proto!=NULL )
				free(lpt_proto);
      return fb_ErrorSetNum( FB_RTERROR_ILLEGALFUNCTIONCALL );
		}

    /* Allow only valid emulation modes */
    if( *lpt_proto->emu!=0 ) {
        int i;
        for( i=0;
             i!=sizeof(aEmulationModes)/sizeof(aEmulationModes[0]);
             ++i )
        {
            const DEV_PRINTER_EMU_MODE *pEmu = aEmulationModes + i;
            if( strcasecmp( lpt_proto->emu, pEmu->pszId )==0 ) {
                pFoundEmu = pEmu;
                break;
            }
        }
        if( !pFoundEmu )
				{
					if( lpt_proto!=NULL )
						free(lpt_proto);
          return fb_ErrorSetNum( FB_RTERROR_ILLEGALFUNCTIONCALL );
				}
    }

    if( iPort==0 ) {
      /* LPT:[PrinterName] */
			if( *lpt_proto->name )
			{
        printer_name = strdup( lpt_proto->name );
			} else {
				printer_name = GetDefaultPrinterName();
			}

    } else {
        /* LPTx: */
        FB_LIST dev_printer_devs;
        DEV_PRINTER_DEVICE* node;

        fb_hListDevInit( &dev_printer_devs );
        fb_hPrinterBuildList( &dev_printer_devs );

        /* Find printer attached to specified device */
        node = fb_hListDevFindDevice( &dev_printer_devs, lpt_proto->proto );
        if( node!=NULL ) {
            printer_name = strdup( node->printer_name );
        }

        fb_hListDevClear( &dev_printer_devs );
    }

    if( printer_name == NULL ) {
        result = fb_ErrorSetNum( FB_RTERROR_FILENOTFOUND );
    } else {
        if( *lpt_proto->emu!= '\0' ) {
            /* When EMULATION is used, we have to use the DC instead of
             * the PRINTER directly */
            hDc = CreateDCA( "WINSPOOL",
                             printer_name,
                             NULL,
                             NULL );
            fResult = hDc!=NULL;
        } else {
            /* User PRINTER directly */
            fResult = OpenPrinter(printer_name, &hPrinter, NULL);
        }
        if( !fResult ) {
            result = fb_ErrorSetNum( FB_RTERROR_FILENOTFOUND );
        }
    }

    if( lpt_proto->title && *lpt_proto->title ) {
			doc_title = strdup( lpt_proto->title );
		} else {
      doc_title = strdup( "FreeBASIC document" );
		}

    if( result==FB_RTERROR_OK ) {
        if( *lpt_proto->emu!= '\0' ) {
            int iJob;
            DOCINFO docInfo;
            memset( &docInfo, 0, sizeof(DOCINFO) );
            docInfo.cbSize = sizeof(DOCINFO);
            docInfo.lpszDocName = doc_title;
            iJob = StartDoc( hDc, &docInfo );
            if( iJob <= 0 ) {
                result = fb_ErrorSetNum( FB_RTERROR_FILEIO );
            } else {
                dwJob = (DWORD) iJob;
            }
        } else {
            DOC_INFO_1 DocInfo;
            DocInfo.pDocName = doc_title;
            DocInfo.pOutputFile = NULL;
            DocInfo.pDatatype = TEXT("RAW");

            dwJob = StartDocPrinter( hPrinter, 1, (BYTE*) &DocInfo );
            if( dwJob==0 ) {
                result = fb_ErrorSetNum( FB_RTERROR_FILEIO );
            }
        }
    }

    if( result==FB_RTERROR_OK ) {
        W32_PRINTER_INFO *pInfo = calloc( 1, sizeof(W32_PRINTER_INFO) );
        if( pInfo==NULL ) {
            result = fb_ErrorSetNum( FB_RTERROR_OUTOFMEM );
        } else {
            devInfo->driver_opaque = pInfo;
            pInfo->hPrinter = hPrinter;
            pInfo->dwJob = dwJob;
            pInfo->hDc = hDc;
            if( hDc!=NULL ) {
                LOGFONT lf;

                pInfo->Emu.dwFullSizeX = GetDeviceCaps( hDc, PHYSICALWIDTH );
                pInfo->Emu.dwFullSizeY = GetDeviceCaps( hDc, PHYSICALHEIGHT );
                pInfo->Emu.dwSizeX = GetDeviceCaps( hDc, HORZRES );
                pInfo->Emu.dwSizeY = GetDeviceCaps( hDc, VERTRES );
                pInfo->Emu.dwOffsetX = GetDeviceCaps( hDc, PHYSICALOFFSETX );
                pInfo->Emu.dwOffsetY = GetDeviceCaps( hDc, PHYSICALOFFSETY );
                pInfo->Emu.dwDPI_X = GetDeviceCaps( hDc, LOGPIXELSX );
                pInfo->Emu.dwDPI_Y = GetDeviceCaps( hDc, LOGPIXELSY );
#if 0
                pInfo->Emu.dwCurrentX = pInfo->Emu.dwOffsetX;
                pInfo->Emu.dwCurrentY = pInfo->Emu.dwOffsetY;
#else
                pInfo->Emu.dwCurrentX = 0;
                pInfo->Emu.dwCurrentY = 0;
#endif
                pInfo->Emu.clFore = RGB(0,0,0);
                pInfo->Emu.clBack = RGB(255,255,255);

                /* Start in 12 CPI monospace mode */
                EmuBuild_LOGFONT( &lf, pInfo, 12 );

                /* Should never fail - except when some default fonts were
                 * removed by hand (which is very unlikely) */
                pInfo->Emu.hFont = CreateFontIndirect( &lf );
                DBG_ASSERT( pInfo->Emu.hFont!=NULL );

                /* Register PRINT function */
                pInfo->Emu.pfnPrint = pFoundEmu->pfnPrint;

                /* Should not be necessary because this is the default */
                SetTextAlign( hDc, TA_TOP | TA_LEFT | TA_NOUPDATECP );

                EmuUpdateInfo( pInfo );
            }
        }
    }

    if( result!=FB_RTERROR_OK ) {
        if( dwJob!=0 ) {
            if( *lpt_proto->emu != '\0' ) {
                EndDoc( hDc );
            } else {
                EndDocPrinter( hPrinter );
            }
        }
        if( hPrinter!=NULL ) {
            ClosePrinter( hPrinter );
        }
        if( hDc!=NULL ) {
            DeleteDC( hDc );
        }
    }

    if( printer_name!=NULL )
        free( printer_name );
    if( doc_title!=NULL )
        free( doc_title );
		if( lpt_proto!=NULL )
			free(lpt_proto);

    return result;
}