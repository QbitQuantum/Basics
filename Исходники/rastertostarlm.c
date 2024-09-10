int main(int argc, char *argv[])
{
    int                 fd                      = 0;        /* File descriptor providing CUPS raster data                                           */
    cups_raster_t *     ras                     = NULL;     /* Raster stream for printing                                                           */
    cups_page_header_t  header;                             /* CUPS Page header                                                                     */
    int                 page                    = 0;        /* Current page                                                                         */
    
    int                 y                       = 0;        /* Vertical position in page 0 <= y <= header.cupsHeight                                */
    int                 vertDot                 = 0;        /* Vertical position in 8-dot heigh scan line 0 <= vertDot <= 8                         */
    int                 i                       = 0;        /* Horizontal byte index in CUPS raster data 0 <= i < header.cupsBytesPerLine           */
    
    unsigned char *     rasterData              = NULL;     /* CUPS raster data [0 ... header.cupsBytesPerLine - 1]  -- 1 byte = 8 horizontal dots  */
    unsigned char *     bitImageData            = NULL;     /* Line mode bit image data [0 ... header.cupsWidth - 1] -- 1 byte = 8 vertical dots    */
    
    int                 scanLineBlank           = FALSE;    /* TRUE iff 1-dot heigh scan line in CUPS raster data is blank                          */
    int                 blankScanLines          = 0;        /* Count of blank 1-dot heigh scan lines 0 <= blankScanLines <= 8                       */
    int                 blankPasses             = 0;        /* Count of blank 8-dot heigh scan lines                                                */
    
    struct settings_    settings;                           /* Configuration settings                                                               */

#ifdef RPMBUILD
    void * libCupsImage = NULL;                             /* Pointer to libCupsImage library                                                      */
    void * libCups      = NULL;                             /* Pointer to libCups library                                                           */
    
    libCups = dlopen ("libcups.so", RTLD_NOW | RTLD_GLOBAL);
    if (! libCups)
    {
        fputs("ERROR: libcups.so load failure\n", stderr);
        return EXIT_FAILURE;
    }
    
    libCupsImage = dlopen ("libcupsimage.so", RTLD_NOW | RTLD_GLOBAL);
    if (! libCupsImage)
    {
        fputs("ERROR: libcupsimage.so load failure\n", stderr);
        dlclose(libCups);
        return EXIT_FAILURE;
    }
    
    GET_LIB_FN_OR_EXIT_FAILURE(ppdClose_fn,             libCups,      "ppdClose"             );
    GET_LIB_FN_OR_EXIT_FAILURE(ppdFindChoice_fn,        libCups,      "ppdFindChoice"        );
    GET_LIB_FN_OR_EXIT_FAILURE(ppdFindMarkedChoice_fn,  libCups,      "ppdFindMarkedChoice"  );
    GET_LIB_FN_OR_EXIT_FAILURE(ppdFindOption_fn,        libCups,      "ppdFindOption"        );
    GET_LIB_FN_OR_EXIT_FAILURE(ppdMarkDefaults_fn,      libCups,      "ppdMarkDefaults"      );
    GET_LIB_FN_OR_EXIT_FAILURE(ppdOpenFile_fn,          libCups,      "ppdOpenFile"          );
    GET_LIB_FN_OR_EXIT_FAILURE(cupsFreeOptions_fn,      libCups,      "cupsFreeOptions"      );
    GET_LIB_FN_OR_EXIT_FAILURE(cupsParseOptions_fn,     libCups,      "cupsParseOptions"     );
    GET_LIB_FN_OR_EXIT_FAILURE(cupsMarkOptions_fn,      libCups,      "cupsMarkOptions"      );
    GET_LIB_FN_OR_EXIT_FAILURE(cupsRasterOpen_fn,       libCupsImage, "cupsRasterOpen"       );
    GET_LIB_FN_OR_EXIT_FAILURE(cupsRasterReadHeader_fn, libCupsImage, "cupsRasterReadHeader" );
    GET_LIB_FN_OR_EXIT_FAILURE(cupsRasterReadPixels_fn, libCupsImage, "cupsRasterReadPixels" );
    GET_LIB_FN_OR_EXIT_FAILURE(cupsRasterClose_fn,      libCupsImage, "cupsRasterClose"      );
#endif

    if (argc < 6 || argc > 7)
    {
        fputs("ERROR: rastertostar job-id user title copies options [file]\n", stderr);

        #ifdef RPMBUILD
            dlclose(libCupsImage);
            dlclose(libCups);
        #endif

        return EXIT_FAILURE;
    }

    if (argc == 7)
    {
        if ((fd = open(argv[6], O_RDONLY)) == -1)
        {
            perror("ERROR: Unable to open raster file - ");
            sleep(1);
            
            #ifdef RPMBUILD
                dlclose(libCupsImage);
                dlclose(libCups);
            #endif

            return EXIT_FAILURE;
        }
    }
    else
    {
        fd = 0;
    }

    initializeSettings(argv[5], &settings);

    jobSetup(settings,argv);

    ras = CUPSRASTEROPEN(fd, CUPS_RASTER_READ);

    page = 0;

    while (CUPSRASTERREADHEADER(ras, &header))
    {
        if ((header.cupsHeight == 0) || (header.cupsBytesPerLine == 0))
        {
            break;
        }
        
        if (bitImageData == NULL)
        {
            bitImageData = malloc(MAX(header.cupsWidth * settings.bytesPerHorizDot, settings.bytesPerScanLine));
            if (bitImageData == NULL)
            {
                CLEANUP;
                return EXIT_FAILURE;
            }
            memset(bitImageData, 0x00, settings.bytesPerScanLine);
        }
        
        if (rasterData == NULL)
        {
            rasterData = malloc(header.cupsBytesPerLine);
            if (rasterData == NULL)
            {
                CLEANUP;
                return EXIT_FAILURE;
            }
        }

        pageSetup(settings, header);

        page++;
        fprintf(stderr, "PAGE: %d %d\n", page, header.NumCopies);

        for (vertDot = 8, y = 0; y < header.cupsHeight; y++)
        {
            if ((y & 127) == 0)
            {
                fprintf(stderr, "INFO: Printing page %d, %d%% complete...\n", page, (100 * y / header.cupsHeight));            }

            if (CUPSRASTERREADPIXELS(ras, rasterData, header.cupsBytesPerLine) < 1)
            {
                break;
            }

            vertDot--;
            
            scanLineBlank = TRUE;
            for (i = 0; i < header.cupsBytesPerLine; i++)
            {
                scanLineBlank &= (rasterData[i] == 0);

                switch (header.cupsWidth - (i * 8))
                {
                    default: bitImageData[(i * 8) + 7] |= ((rasterData[i] & 0x01) >> 0) << vertDot;
                    case 6:  bitImageData[(i * 8) + 6] |= ((rasterData[i] & 0x02) >> 1) << vertDot;
                    case 5:  bitImageData[(i * 8) + 5] |= ((rasterData[i] & 0x04) >> 2) << vertDot;
                    case 4:  bitImageData[(i * 8) + 4] |= ((rasterData[i] & 0x08) >> 3) << vertDot;
                    case 3:  bitImageData[(i * 8) + 3] |= ((rasterData[i] & 0x10) >> 4) << vertDot;
                    case 2:  bitImageData[(i * 8) + 2] |= ((rasterData[i] & 0x20) >> 5) << vertDot;
                    case 1:  bitImageData[(i * 8) + 1] |= ((rasterData[i] & 0x40) >> 6) << vertDot;
                    case 0:  bitImageData[(i * 8) + 0] |= ((rasterData[i] & 0x80) >> 7) << vertDot;
                }
            }

            if (scanLineBlank == TRUE)
            {
                blankScanLines++;
            }

            if (vertDot == 0)
            {
                vertDot = 8;

                if (blankScanLines == 8)
                {
                    blankPasses++;
                }
                else
                {
                    while (blankPasses > 0)
                    {
                        putchar(0x1b);
                        putchar('J');
                        putchar(0x08);

                        blankPasses--;
                    }
                
		    switch(settings.modelNumber)
		      {
		      case SP512:
		      case SP542:
		      case SP712:
		      case SP742:
		      case SP717:
		      case SP747:
			if (settings.resolutionX == 170)
			  {
			    putchar(0x1b);
			    putchar('L');
			    putchar(settings.bytesPerScanLine % 256); // 420 % 256 = 164
			    putchar(settings.bytesPerScanLine / 256); // 420 / 256 = 1
			    
			    for (i = 0; i < settings.bytesPerScanLine; i++)
			      {
				putchar(bitImageData[i]);
			      }
			  }
			else if (settings.resolutionX == 85)
			  {
			    putchar(0x1b);
			    putchar('K');
			    putchar(settings.bytesPerScanLine % 256); // 210 % 256 = 210
			    putchar(settings.bytesPerScanLine / 256); // 210 / 256 = 0
			    
			    for (i = 0; i < settings.bytesPerScanLine; i++)
			      {
				putchar(bitImageData[i]);
			      }
			  }
			
			break;
			
		      case HSP7000S:
		      case HSP7000V:
			if (settings.resolutionX == 160)
			  {
			    putchar(0x1b);
			    putchar('L');
			    putchar(settings.bytesPerScanLine % 256); // 540 % 256 = 28
			    putchar(settings.bytesPerScanLine / 256); // 540 / 256 = 2
			    
			    for (i = 0; i < settings.bytesPerScanLine; i++)
			      {
				putchar(bitImageData[i]);
			      }
			  }
			else if (settings.resolutionX == 80)
			  {
			    putchar(0x1b);
			    putchar('K');
			    putchar(settings.bytesPerScanLine % 256); // 270 % 256 = 14
			    putchar(settings.bytesPerScanLine / 256); // 270 / 256 = 1
			    
			    for (i = 0; i < settings.bytesPerScanLine; i++)
			      {
				putchar(bitImageData[i]);
			      }
			  }
		      }
		    
                    putchar(0x1b);
                    putchar('J');
                    putchar(0x08);
                }

                blankScanLines = 0;

                memset(bitImageData, 0x00, settings.bytesPerScanLine);
            }
        }
        
        if (vertDot != 8)
        {
            if (blankScanLines + vertDot == 8)
            {
                 blankPasses++;
            }
            else
            {
                while (blankPasses > 0)
                {
                    putchar(0x1b);
                    putchar('J');
                    putchar(0x08);

                    blankPasses--;
                }
                
		switch (settings.modelNumber)
		{
		  case SP512:
		  case SP542:
		  case SP712:
		  case SP742:
		  case SP717:
		  case SP747:
		    if (settings.resolutionX == 170)
		    {
			putchar(0x1b);
			putchar('L');
			putchar(settings.bytesPerScanLine % 256); // 420 % 256 = 164
			putchar(settings.bytesPerScanLine / 256); // 420 / 256 = 1 

			for (i = 0; i < settings.bytesPerScanLine; i++)
			{
			    putchar(bitImageData[i]);
			}
		    }
		    else if (settings.resolutionX == 85)
		    {
			putchar(0x1b);
			putchar('K');
			putchar(settings.bytesPerScanLine % 256); // 210 % 256 = 210
			putchar(settings.bytesPerScanLine / 256); // 210 / 256 = 0

			for (i = 0; i < settings.bytesPerScanLine; i++)
			{
			  putchar(bitImageData[i]);
			}
		    }

		    break;

		  case HSP7000S:
		  case HSP7000V:
		    if (settings.resolutionX == 160)
		    {
			putchar(0x1b);
			putchar('L');
			putchar(settings.bytesPerScanLine % 256); // 540 % 256 = 28
			putchar(settings.bytesPerScanLine / 256); // 540 / 256 = 2

			for (i = 0; i < settings.bytesPerScanLine; i++)
			  {
			    putchar(bitImageData[i]);
			  }
		    }
		    else if (settings.resolutionX == 80)
		    {
			putchar(0x1b);
			putchar('K');
			putchar(settings.bytesPerScanLine % 256); // 270 % 256 = 14
			putchar(settings.bytesPerScanLine / 256); // 270 / 256 = 1

			for (i = 0; i < settings.bytesPerScanLine; i++)
			{
			    putchar(bitImageData[i]);
			}
		    }

		    break;
		}
		
                putchar(0x1b);
                putchar('J');
                putchar(0x08);

                memset(bitImageData, 0x00, settings.bytesPerScanLine);
            }

            blankScanLines = 0;

            vertDot = 8;
        }

        if (settings.pageType == PAGETYPE_TICKET)
        {
            while (blankPasses--)
            {
                putchar(0x1b);
                putchar('J');
                putchar(0x08);
            }
        }

        endPage(settings);
    }

    endJob(settings);

    CLEANUP;

    if (page == 0)
    {
        fputs("ERROR: No pages found!\n", stderr);
    }
    else
    {
        fputs("INFO: Ready to print.\n", stderr);
    }
    
    return (page == 0)?EXIT_FAILURE:EXIT_SUCCESS;
}