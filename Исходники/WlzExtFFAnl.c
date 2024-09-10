/*!
* \return	New Woolz object or NULL on error.
* \ingroup	WlzExtFF
* \brief	Reads a Woolz object from the given stream using the
*		ANALYZE 7.5 format. The given file name is used to
*		generate the '.hdr' and '.img' filenames.
* \param	gvnFileName		Given file name.
* \param	dstErr			Destination error code, may be NULL.
*/
WlzObject	*WlzEffReadObjAnl(const char *gvnFileName, WlzErrorNum *dstErr)
{
  int		idx,
  		timePoints = 0;
  FILE		*fP = NULL;
  char		*fileName = NULL,
  		*hdrFileName = NULL,
		*imgFileName = NULL;
  WlzVertex	org,
  		sz;
  WlzEffAnlDsr 	dsr;
  int 		swap = 0;
  WlzObject	*obj = NULL;
  WlzGreyType	gType = WLZ_GREY_ERROR;
  WlzPixelV	bgdV;
  WlzErrorNum	errNum = WLZ_ERR_NONE;

  sz.i3.vtX = sz.i3.vtY = sz.i3.vtZ = 0;
  /* Compute .hdr and .img file names. */
  if((gvnFileName == NULL) || (*gvnFileName == '\0'))
  {
    errNum = WLZ_ERR_PARAM_NULL;
  }
  else
  {
    errNum = WlzEffAnlFileNames(&fileName, &hdrFileName, &imgFileName,
				gvnFileName);
  }
  if(errNum == WLZ_ERR_NONE)
  {
    if((hdrFileName == NULL) || (*hdrFileName == '\0') ||
       ((fP = fopen(hdrFileName, "r")) == NULL))
    {
      errNum = WLZ_ERR_READ_EOF;
    }
#ifdef _WIN32
    else
    {
      if(fP != NULL)
      {
	if(_setmode(_fileno(fP), 0x8000) == -1)
	{
	  errNum = WLZ_ERR_READ_EOF;
	}
      }
    }
#endif
  }
  /* Read the .hdr (header) file. */
  if(errNum == WLZ_ERR_NONE)
  {
    (void )memset((void *)&dsr, 0, sizeof(WlzEffAnlDsr));
    errNum = WlzEffReadAnlHdrKey(fP, &dsr, &swap);
  }
  if(errNum == WLZ_ERR_NONE)
  {
    errNum = WlzEffReadAnlHdrImageDim(fP, &dsr, swap);
  }
  if(errNum == WLZ_ERR_NONE)
  {
    errNum = WlzEffReadAnlHdrDataHistory(fP, &dsr, swap);
  }
  if(fP)
  {
    (void )fclose(fP);
    fP = NULL;
  }
  /* Check header data is valid. */
  if(errNum == WLZ_ERR_NONE)
  {
    if('r' != dsr.hk.regular)
    {
      errNum = WLZ_ERR_OBJECT_DATA;
    }
  }
  if(errNum == WLZ_ERR_NONE)
  {
    switch(dsr.dim.bitPix)
    {
      case 8:  /* FALLTHROUGH */
      case 16: /* FALLTHROUGH */
      case 32: /* FALLTHROUGH */
      case 64:
        break;
      case 1:
      default:
        errNum = WLZ_ERR_OBJECT_DATA;
	break;
    }
  }
  /* Compute the image parameters. */
  if(errNum == WLZ_ERR_NONE)
  {
    switch(dsr.dim.dataType)
    {
      case WLZEFF_ANL_DT_UNSIGNED_CHAR:
        gType = WLZ_GREY_UBYTE;
	bgdV.type = gType;
	bgdV.v.ubv = 0;
	break;
      case WLZEFF_ANL_DT_SIGNED_SHORT:
        gType = WLZ_GREY_SHORT;
	bgdV.type = gType;
	bgdV.v.shv = 0;
	break;
      case WLZEFF_ANL_DT_SIGNED_INT:
        gType = WLZ_GREY_INT;
	bgdV.type = gType;
	bgdV.v.inv = 0;
	break;
      case WLZEFF_ANL_DT_FLOAT:
        gType = WLZ_GREY_FLOAT;
	bgdV.type = gType;
	bgdV.v.flv = 0.0;
	break;
      case WLZEFF_ANL_DT_DOUBLE:
        gType = WLZ_GREY_DOUBLE;
	bgdV.type = gType;
	bgdV.v.dbv = 0.0;
	break;
      default:
	errNum = WLZ_ERR_GREY_TYPE;
	break;
    }
  }
  if(errNum == WLZ_ERR_NONE)
  {
    switch(dsr.dim.dim[0])
    {
      case 2:
	org.i2.vtX = 0;
	org.i2.vtY = 0;
	sz.i2.vtX = dsr.dim.dim[1];
	sz.i2.vtY = dsr.dim.dim[2];
	timePoints = 1;
	if((sz.i2.vtX < 1) || (sz.i2.vtY < 1))
	{
	  errNum = WLZ_ERR_OBJECT_DATA;
	}
	break;
      case 3:
        org.i3.vtX = 0;
	org.i3.vtY = 0;
	org.i3.vtZ = 0;
	sz.i3.vtX = dsr.dim.dim[1];
	sz.i3.vtY = dsr.dim.dim[2];
	sz.i3.vtZ = dsr.dim.dim[3];
	if((sz.i3.vtX < 1) || (sz.i3.vtY < 1) || (sz.i3.vtZ < 1))
	{
	  errNum = WLZ_ERR_OBJECT_DATA;
	}
        break;
      case 4:
        org.i3.vtX = 0;
	org.i3.vtY = 0;
	org.i3.vtZ = 0;
	sz.i3.vtX = dsr.dim.dim[1];
	sz.i3.vtY = dsr.dim.dim[2];
	sz.i3.vtZ = dsr.dim.dim[3];
	timePoints = dsr.dim.dim[4];
	if((sz.i3.vtX < 1) || (sz.i3.vtY < 1) || (sz.i3.vtZ < 1) ||
	   (timePoints < 1))
	{
	  errNum = WLZ_ERR_OBJECT_DATA;
	}
        break;
      default:
	errNum = WLZ_ERR_OBJECT_DATA;
        break;
        
    }
  }
  /* Create object. */
  if(errNum == WLZ_ERR_NONE)
  {
    if(timePoints > 1)
    {
      obj = (WlzObject *)
            WlzMakeCompoundArray(WLZ_3D_DOMAINOBJ, 1, timePoints, NULL,
	                         WLZ_3D_DOMAINOBJ, &errNum);
      if(obj)
      {
        idx = 0;
	do
	{
	  ((WlzCompoundArray *)obj)->o[idx] = WlzAssignObject(
		WlzMakeCuboid(org.i3.vtZ, org.i3.vtZ + sz.i3.vtZ - 1,
			      org.i3.vtY, org.i3.vtY + sz.i3.vtY - 1,
			      org.i3.vtX, org.i3.vtX + sz.i3.vtX - 1,
			      gType, bgdV, NULL, NULL, &errNum), NULL);
	} while((++idx < timePoints) && (WLZ_ERR_NONE == errNum));
      }
    }
    else if(3 <= dsr.dim.dim[0])
    {
      obj = WlzMakeCuboid(org.i3.vtZ, org.i3.vtZ + sz.i3.vtZ - 1,
                          org.i3.vtY, org.i3.vtY + sz.i3.vtY - 1,
			  org.i3.vtX, org.i3.vtX + sz.i3.vtX - 1,
			  gType, bgdV, NULL, NULL, &errNum);
    }
    else /* 2 == dsr.dim.dim[0] */
    {
      obj = WlzMakeRect(org.i2.vtY, org.i2.vtY + sz.i2.vtY - 1,
			org.i2.vtX, org.i2.vtX + sz.i2.vtX - 1,
			gType, NULL, bgdV, NULL, NULL, &errNum);
    }
  }
  /* Open the .img (image data) file. */
  if(errNum == WLZ_ERR_NONE)
  {
    if((imgFileName == NULL) || (*imgFileName == '\0') ||
       ((fP = fopen(imgFileName, "r")) == NULL))
    {
      errNum = WLZ_ERR_READ_EOF;
    }
#ifdef _WIN32
    else
    {
      if(fP != NULL)
      {
	if(_setmode(_fileno(fP), 0x8000) == -1)
	{
	  errNum = WLZ_ERR_READ_EOF;
	}
      }
    }
#endif
  }
  /* Read the object values. */
  if(errNum == WLZ_ERR_NONE)
  {
    errNum = WlzEffReadAnlImgData(obj, gType, &dsr, fP, swap);
  }
  if(fP)
  {
    (void )fclose(fP);
  }
  (void )AlcFree(fileName);
  (void )AlcFree(hdrFileName);
  (void )AlcFree(imgFileName);
  if(errNum != WLZ_ERR_NONE)
  {
    (void )WlzFreeObj(obj);
    obj = NULL;
  }
  if(dstErr)
  {
    *dstErr = errNum;
  }
  return(obj);
}