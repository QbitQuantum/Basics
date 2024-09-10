int HPCupsFilter::processRasterData(cups_raster_t *cups_raster)
{
    FILE                   *kfp = NULL;
    FILE                   *cfp = NULL;
    BYTE                   *kRaster = NULL;
    BYTE                   *rgbRaster = NULL;
    int                    current_page_number = 0;
    cups_page_header2_t    cups_header;
    DRIVER_ERROR           err;
    int                    ret_status = 0;
    char hpPreProcessedRasterFile[] = "/tmp/hplipSwapedPagesXXXXXX"; //temp file needed to store raster data with swaped pages.

    while (cupsRasterReadHeader2(cups_raster, &cups_header))
    {
        current_page_number++;

        if (current_page_number == 1) {
            
            if (startPage(&cups_header) != NO_ERROR) {
                return JOB_CANCELED;
            }
            
            if(m_JA.pre_process_raster) {
		        err = m_Job.preProcessRasterData(&cups_raster, &cups_header, hpPreProcessedRasterFile);
				if (err != NO_ERROR) {
					if (m_iLogLevel & BASIC_LOG) {
						dbglog ("DEBUG: Job::StartPage failed with err = %d\n", err);
					}
					ret_status = JOB_CANCELED;
					break;
				}   
			}
            
            if (cups_header.cupsColorSpace == CUPS_CSPACE_RGBW) {
                rgbRaster = new BYTE[cups_header.cupsWidth * 3];
                if (rgbRaster == NULL) {
                    return ALLOCMEM_ERROR;
                }
                kRaster = new BYTE[cups_header.cupsWidth];
                if (kRaster == NULL) {
                    delete [] rgbRaster;
                    return ALLOCMEM_ERROR;
                }
                memset (kRaster, 0, cups_header.cupsWidth);
                memset (rgbRaster, 0xFF, cups_header.cupsWidth * 3);
            }
        } // current_page_number == 1

        if (cups_header.cupsColorSpace == CUPS_CSPACE_K) {
            kRaster = m_pPrinterBuffer;
            rgbRaster = NULL;
        }
        else if (cups_header.cupsColorSpace != CUPS_CSPACE_RGBW) {
            rgbRaster = m_pPrinterBuffer;
            kRaster = NULL;
        }

        BYTE    *color_raster = NULL;
        BYTE    *black_raster = NULL;

        err = m_Job.StartPage(&m_JA);
        if (err != NO_ERROR) {
            if (m_iLogLevel & BASIC_LOG) {
                dbglog ("DEBUG: Job::StartPage failed with err = %d\n", err);
            }
            ret_status = JOB_CANCELED;
            break;
        }
        
        if (m_iLogLevel & SAVE_INPUT_RASTERS)
        {
            char    szFileName[32];
            memset(szFileName, 0, sizeof(szFileName));
            snprintf (szFileName, sizeof(szFileName), "/tmp/hpcupsfilterc_%d.bmp", current_page_number);
            if (cups_header.cupsColorSpace == CUPS_CSPACE_RGBW ||
                cups_header.cupsColorSpace == CUPS_CSPACE_RGB)
            {
                cfp = fopen (szFileName, "w");
                chmod (szFileName, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
            }
            if (cups_header.cupsColorSpace == CUPS_CSPACE_RGBW ||
                cups_header.cupsColorSpace == CUPS_CSPACE_K)
            {
                szFileName[17] = 'k';
                kfp = fopen (szFileName, "w");
                chmod (szFileName, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
            }

            WriteBMPHeader (cfp, cups_header.cupsWidth, cups_header.cupsHeight, COLOR_RASTER);
            WriteBMPHeader (kfp, cups_header.cupsWidth, cups_header.cupsHeight, BLACK_RASTER);
        }

        fprintf(stderr, "PAGE: %d %s\r\n", current_page_number, m_argv[4]);
        // Iterating through the raster per page
        for (int y = 0; y < (int) cups_header.cupsHeight; y++) {
            cupsRasterReadPixels (cups_raster, m_pPrinterBuffer, cups_header.cupsBytesPerLine);
            color_raster = rgbRaster;
            black_raster = kRaster;

            if(y == 0 && (0 == strcmp(m_JA.printer_language, "ljmono")) )
			{
				//For ljmono, make sure that first line is not a blankRaster line.Otherwise printer 
				//may not skip blank lines before actual data
				//Need to revisit to crosscheck if it is a firmware issue.
				
				*m_pPrinterBuffer = 0x01;  
				dbglog("First raster data plane.." );
			}
			
            if (this->isBlankRaster((BYTE *) m_pPrinterBuffer, &cups_header)) {
            
                color_raster = NULL;
                black_raster = NULL;
            }
            extractBlackPixels(&cups_header, black_raster, color_raster);
            //! Sending Raster bits off to encapsulation 
            err = m_Job.SendRasters (black_raster, color_raster);
            if (err != NO_ERROR) {
                break;
            }
            WriteBMPRaster (cfp, color_raster, cups_header.cupsWidth, COLOR_RASTER);
            WriteBMPRaster (kfp, black_raster, cups_header.cupsWidth/8, BLACK_RASTER);
        }
        m_Job.NewPage();
        if (err != NO_ERROR) {
            break;
        }
    }

    //! Remove the old processing band data...
    if (cups_header.cupsColorSpace == CUPS_CSPACE_RGBW) {
        delete [] kRaster;
        delete [] rgbRaster;
    }

    unlink(hpPreProcessedRasterFile); 
    return ret_status;
}