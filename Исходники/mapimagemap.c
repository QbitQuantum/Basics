int msSaveImageIM(imageObj* img, char *filename, outputFormatObj *format )

{
  FILE *stream;
  char workbuffer[5000];
  int nSize=0, size=0, iIndice=0;

  DEBUG_IF printf("msSaveImageIM\n<BR>");

  if(filename != NULL && strlen(filename) > 0) {
    stream = fopen(filename, "wb");
    if(!stream) {
      msSetError(MS_IOERR, "(%s)", "msSaveImage()", filename);
      return(MS_FAILURE);
    }
  } else { /* use stdout */

#ifdef _WIN32
    /*
     * Change stdout mode to binary on win32 platforms
     */
    if(_setmode( _fileno(stdout), _O_BINARY) == -1) {
      msSetError(MS_IOERR, "Unable to change stdout to binary mode.", "msSaveImage()");
      return(MS_FAILURE);
    }
#endif
    stream = stdout;
  }

  if( strcasecmp(format->driver,"imagemap") == 0 ) {
    DEBUG_IF printf("ALLOCD %d<BR>\n", img->size);
    /* DEBUG_IF printf("F %s<BR>\n", img->img.imagemap); */
    DEBUG_IF printf("FLEN %d<BR>\n", (int)strlen(img->img.imagemap));
    if (dxf == 2) {
      msIO_fprintf(stream, "%s", layerlist);
    } else if (dxf) {
      msIO_fprintf(stream, "  0\nSECTION\n  2\nHEADER\n  9\n$ACADVER\n  1\nAC1009\n0\nENDSEC\n  0\nSECTION\n  2\nTABLES\n  0\nTABLE\n%s0\nENDTAB\n0\nENDSEC\n  0\nSECTION\n  2\nBLOCKS\n0\nENDSEC\n  0\nSECTION\n  2\nENTITIES\n", layerlist);
    } else {
      msIO_fprintf(stream, "<map name=\"%s\" width=\"%d\" height=\"%d\">\n", mapName, img->width, img->height);
    }
    nSize = sizeof(workbuffer);

    size = strlen(img->img.imagemap);
    if (size > nSize) {
      iIndice = 0;
      while ((iIndice + nSize) <= size) {
        snprintf(workbuffer, sizeof(workbuffer), "%s", img->img.imagemap+iIndice );
        workbuffer[nSize-1] = '\0';
        msIO_fwrite(workbuffer, strlen(workbuffer), 1, stream);
        iIndice +=nSize-1;
      }
      if (iIndice < size) {
        sprintf(workbuffer, "%s", img->img.imagemap+iIndice );
        msIO_fprintf(stream, "%s", workbuffer);
      }
    } else
      msIO_fwrite(img->img.imagemap, size, 1, stream);
    if( strcasecmp("OFF",msGetOutputFormatOption( format, "SKIPENDTAG", "OFF" )) == 0) {
      if (dxf == 2)
        msIO_fprintf(stream, "END");
      else if (dxf)
        msIO_fprintf(stream, "0\nENDSEC\n0\nEOF\n");
      else
        msIO_fprintf(stream, "</map>");
    }
  } else {
    msSetError(MS_MISCERR, "Unknown output image type driver: %s.",
               "msSaveImage()", format->driver );
    return(MS_FAILURE);
  }

  if(filename != NULL && strlen(filename) > 0) fclose(stream);
  return(MS_SUCCESS);
}