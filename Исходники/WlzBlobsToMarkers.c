int             main(int argc, char **argv)
{
  int		tI,
		idN,
  		option,
		con = WLZ_0_CONNECTED,
		nLo = 0,
		nHi = 0,
		maxSep = 1024,
		nObj = 0,
  		ok = 1,
		usage = 0;
  char		tC;
  double  	tD,
		mrkMass = 1.0,
  		rad = 0.0;
  int		tR[4];
  WlzPixelV	gV,
  		bV;
  WlzBlobMark	mrk = WLZ_BLOBMARK_CIRCLE;
  WlzObject     *inObj = NULL,
  		*outObj = NULL,
		*mrkObj = NULL;
  WlzObject	**lObj = NULL;
  FILE		*fP = NULL;
  char 		*inObjFileStr,
  		*outObjFileStr;
  WlzErrorNum	errNum = WLZ_ERR_NONE;
  const char	*errMsg;
  static char	optList[] = "c:g:G:hm:n:N:o:r:x:",
  		fileStrDef[] = "-";

  opterr = 0;
  memset(&gV, 0, sizeof(WlzPixelV));
  bV.type = WLZ_GREY_UBYTE;
  bV.v.ubv = 0;
  gV.type = WLZ_GREY_ERROR;
  inObjFileStr = fileStrDef;
  outObjFileStr = fileStrDef;
  while((usage == 0) && ((option = getopt(argc, argv, optList)) != -1))
  {
    switch(option)
    {
      case 'c':
        if(sscanf(optarg, "%d", &tI) != 1)
	{
	  usage = 1;
	}
	else
	{
	  switch(tI)
	  {
	    case  4:
	      con = WLZ_4_CONNECTED;
	      break;
	    case  6:
	      con = WLZ_6_CONNECTED;
	      break;
	    case  8:
	      con = WLZ_8_CONNECTED;
	      break;
	    case 18:
	      con = WLZ_18_CONNECTED;
	      break;
	    case 26:
	      con = WLZ_26_CONNECTED;
	      break;
	    default:
	      usage = 1;
	      break;
	  }
	}
	break;
      case 'g':
        switch(gV.type)
	{
	  case WLZ_GREY_UBYTE:
	    if((sscanf(optarg, "%d", &tI) != 1) ||
	       (tI < 0) || (tI > 255))
	    {
	      usage = 1;
	    }
	    else
	    {
	      gV.v.ubv = tI;
	    }
	    break;
	  case WLZ_GREY_SHORT:
	    if((sscanf(optarg, "%d", &tI) != 1) ||
	       (tI < SHRT_MIN) || (tI > SHRT_MAX))
	    {
	      usage = 1;
	    }
	    else
	    {
	      gV.v.shv = tI;
	    }
	    break;
	  case WLZ_GREY_INT:
	    if(sscanf(optarg, "%d", &tI) != 1)
	    {
	      usage = 1;
	    }
	    else
	    {
	      gV.v.inv = tI;
	    }
	    break;
	  case WLZ_GREY_FLOAT:
	    if((sscanf(optarg, "%lg", &tD) != 1) ||
	       (tD < -(FLT_MAX)) || (tD > FLT_MAX))
	    {
	      usage = 1;
	    }
	    else
	    {
	      gV.v.flv = tD;
	    }
	    break;
	  case WLZ_GREY_DOUBLE:
	    if(sscanf(optarg, "%lg", &tD) != 1)
	    {
	      usage = 1;
	    }
	    else
	    {
	      gV.v.dbv = tD;
	    }
	    break;
	  case WLZ_GREY_RGBA:
	    tR[3] = 255;
	    tR[0] = tR[1] = tR[2] = 0;
	    if((sscanf(optarg, "%d,%d,%d,%d",
	               &(tR[0]), &(tR[1]), &(tR[2]), &(tR[3])) == 0) ||
	       (tR[0] < 0) || (tR[0] > 255) ||
	       (tR[1] < 0) || (tR[1] > 255) ||
	       (tR[2] < 0) || (tR[2] > 255) ||
	       (tR[3] < 0) || (tR[3] > 255))
	    {
	      usage = 1;
	    }
	    else
	    {
	      WLZ_RGBA_RGBA_SET(gV.v.rgbv, tR[0], tR[1], tR[2], tR[3]);
	    }
	    break;
	  default:
	    usage = 1;
	    break;
	}
	break;
      case 'G':
        if(sscanf(optarg, "%c", &tC) != 1)
	{
	  usage = 1;
	}
	switch(tC)
	{
	  case 'v':
	    gV.type = WLZ_GREY_ERROR;
	    break;
	  case 'u':
	    gV.type = WLZ_GREY_UBYTE;
	    break;
	  case 's':
	    gV.type = WLZ_GREY_SHORT;
	    break;
	  case 'i':
	    gV.type = WLZ_GREY_INT;
	    break;
	  case 'f':
	    gV.type = WLZ_GREY_FLOAT;
	    break;
	  case 'd':
	    gV.type = WLZ_GREY_DOUBLE;
	    break;
	  case 'r':
	    gV.type = WLZ_GREY_RGBA;
	    break;
	  default:
	    usage = 1;
	    break;
	}
	break;
      case 'm':
        if((sscanf(optarg, "%d", &tI) != 1) ||
	   ((tI != WLZ_BLOBMARK_CIRCLE) && (tI != WLZ_BLOBMARK_SQUARE)))
	{
	  usage = 1;
	}
	else
	{
	  mrk = (WlzBlobMark )tI;
	}
	break;
      case 'n':
        if((sscanf(optarg, "%d", &nLo) != 1) || (nLo < 0))
	{
	  usage = 1;
	}
	break;
      case 'N':
        if((sscanf(optarg, "%d", &nHi) != 1) || (nHi < 0))
	{
	  usage = 1;
	}
	break;
      case 'o':
        outObjFileStr = optarg;
	break;
      case 'r':
        if((sscanf(optarg, "%lg", &rad) != 1) || (rad < 0.0))
	{
	  usage = 1;
	}
	break;
      case 'x':
        if((sscanf(optarg, "%d", &maxSep) != 1) || (maxSep < 1))
	{
	  usage = 1;
	}
      case 'h': /* FALLTHROUGH */
      default:
        usage = 1;
	break;
    }
  }
  if((usage == 0) && (nLo > nHi) && (nHi != 0))
  {
    usage = 1;
  }
  if((usage == 0) && (optind < argc))
  {
    if((optind + 1) != argc)
    {
      usage = 1;
    }
    else
    {
      inObjFileStr = *(argv + optind);
    }
  }
  ok = (usage == 0);
  /* Read input domain object. */
  if(ok)
  {
    if((inObjFileStr == NULL) ||
	(*inObjFileStr == '\0') ||
	((fP = (strcmp(inObjFileStr, "-")?
	       fopen(inObjFileStr, "r"): stdin)) == NULL) ||
	((inObj = WlzAssignObject(WlzReadObj(fP, &errNum), NULL)) == NULL) ||
	(errNum != WLZ_ERR_NONE))
    {
      ok = 0;
    }
    if(fP)
    {
      if(strcmp(inObjFileStr, "-"))
      {
	(void )fclose(fP);
      }
      fP = NULL;
    }
  }
  /* Check object type and connectivity. */
  if(ok)
  {
    switch(inObj->type)
    {
      case WLZ_2D_DOMAINOBJ:
	switch(con)
	{
	  case WLZ_0_CONNECTED:
	    con = WLZ_8_CONNECTED;
	    break;
	  case WLZ_4_CONNECTED: /* FALLTHROUGH */
	  case WLZ_8_CONNECTED:
	    break;
	  default:
	    ok = 0;
	    errNum = WLZ_ERR_PARAM_DATA;
	    (void )WlzStringFromErrorNum(errNum, &errMsg);
	    (void )fprintf(stderr,
	           "%s: Connectivity for 2D must be 4 or 8 (%s).\n",
		   *argv, errMsg);
	    break;
	}
	break;
      case WLZ_3D_DOMAINOBJ:
	switch(con)
	{
	  case WLZ_0_CONNECTED:
	    con = WLZ_26_CONNECTED;
	    break;
	  case  WLZ_6_CONNECTED: /* FALLTHROUGH */
	  case WLZ_18_CONNECTED: /* FALLTHROUGH */
	  case WLZ_26_CONNECTED:
	    break;
	  default:
	    ok = 0;
	    errNum = WLZ_ERR_PARAM_DATA;
	    (void )WlzStringFromErrorNum(errNum, &errMsg);
	    (void )fprintf(stderr,
	           "%s: Connectivity for 3D must be 6, 18 or 26 (%s).\n",
		   *argv, errMsg);
	    break;
	}
	break;
      default:
	ok = 0;
	errNum = WLZ_ERR_OBJECT_TYPE;
	(void )WlzStringFromErrorNum(errNum, &errMsg);
	(void )fprintf(stderr,
	       "%s: Input object must either a 2 or 3D domain object (%s).\n",
	       *argv, errMsg);
	break;
    }
  }
  /* Make basic marker with centre at the origin. */
  if(ok)
  {
    double	mrkRad;

    if(rad > 0.5)
    {
      mrkRad = rad;
    }
    else
    {
      mrkRad = 127;
    }
    if(mrk == WLZ_BLOBMARK_SQUARE)
    {
      mrkObj = WlzMakeCuboidObject(inObj->type, mrkRad, mrkRad, mrkRad,
                                   0, 0, 0, &errNum);
    }
    else /* mrk = WLZ_BLOBMARK_CIRCLE */
    {
      mrkObj = WlzMakeSphereObject(inObj->type, mrkRad, 0, 0, 0, &errNum);
    }
    if(mrkObj == NULL)
    {
      ok = 0;
      (void )WlzStringFromErrorNum(errNum, &errMsg);
      (void )fprintf(stderr,
             "%s: Failed to create basic marker object (%s).\n",
	     *argv, errMsg);
    }
    else
    {
      mrkMass = WlzVolume(mrkObj, NULL);
    }
  }
  /* Label the given domain. */
  if(ok)
  {
    errNum = WlzLabel(inObj, &nObj, &lObj, maxSep, 1, con);
    if((errNum != WLZ_ERR_NONE) || (nObj == 0))
    {
      ok = 0;
      if(errNum == WLZ_ERR_NONE)
      {
        errNum = WLZ_ERR_DOMAIN_DATA;
      }
      (void )WlzStringFromErrorNum(errNum, &errMsg);
      (void )fprintf(stderr,
      "%s: Failed to split the given object into separate regions (%s)\n",
      *argv, errMsg);
    }
  }
  /* Work through the separate object list removing small/large objects
   * according to the low and high thresholds. */
  if(ok)
  {
    int		idM;

    for(idN = 0, idM = 0; idN < nObj; ++idN)
    {
      int	vol;

      vol = WlzVolume(lObj[idN], &errNum);
      if(errNum == WLZ_ERR_NONE)
      {
        if(((nLo > 0) && (vol < nLo)) || ((nHi > 0) && (vol > nHi)))
	{
	  (void )WlzFreeObj(lObj[idN]);
	}
	else
	{
	  lObj[idM] = lObj[idN];
	  ++idM;
	}
      }
    }
    nObj = idM;
    if(nObj == 0)
    {
      ok = 0;
      errNum = WLZ_ERR_DOMAIN_DATA;
      (void )WlzStringFromErrorNum(errNum, &errMsg);
      (void )fprintf(stderr,
                     "%s: Failed to find and separate regions (%s)\n",
		     *argv, errMsg);

    }
  }
  /* Build a marker object by adding a mark at the centre of mass of each
   * separate fragment. */
  if(ok)
  {
    WlzObject	*obj0 = NULL;

    idN = 0;
    obj0 = WlzMakeEmpty(&errNum);
    while((errNum == WLZ_ERR_NONE) && (idN < nObj))
    {
      double	  mass;
      WlzDVertex3 com;
      WlzObject	  *obj1 = NULL,
      		  *obj2 = NULL;
      WlzAffineTransform *tr = NULL;

      com = WlzCentreOfMass3D(lObj[idN], 1, &mass, &errNum);
      if(errNum == WLZ_ERR_NONE)
      {
        double	s;

	if(rad < 0.5)
	{
	  double t;

	  t = mass / mrkMass;
	  if(inObj->type == WLZ_2D_DOMAINOBJ)
	  {
	    s = sqrt(t);
	  }
	  else /* inObj->type == WLZ_3D_DOMAINOBJ */
	  {
	    s = cbrt(t);
	  }
	}
	else
	{
	  s = 1.0;
	}
        tr = (inObj->type == WLZ_2D_DOMAINOBJ)?
             WlzAffineTransformFromPrimVal(
	       WLZ_TRANSFORM_2D_AFFINE, com.vtX, com.vtY, 0.0,
	       s, 0.0, 0.0, 0.0, 0.0, 0.0, 0, &errNum):
             WlzAffineTransformFromPrimVal(
	       WLZ_TRANSFORM_3D_AFFINE, com.vtX, com.vtY, com.vtZ,
	       s, 0.0, 0.0, 0.0, 0.0, 0.0, 0, &errNum);
      }
      if(errNum == WLZ_ERR_NONE)
      {
	obj1 = WlzAffineTransformObj(mrkObj, tr, WLZ_INTERPOLATION_NEAREST,
				     &errNum);
      }
      if(errNum == WLZ_ERR_NONE)
      {
	obj2 = WlzUnion2(obj0, obj1, &errNum);
      }
      if(errNum == WLZ_ERR_NONE)
      {
        (void )WlzFreeObj(obj0);
	obj0 = obj2;
	obj2 = NULL;
      }
      (void )WlzFreeObj(obj1);
      (void )WlzFreeObj(obj2);
      (void )WlzFreeAffineTransform(tr);
      ++idN;
    }
    if(errNum == WLZ_ERR_NONE)
    {
      WlzValues	val;
      WlzObjectType vTT;

      val.core = NULL;
      if(gV.type != WLZ_GREY_ERROR)
      {
	vTT = WlzGreyTableType(WLZ_GREY_TAB_RAGR, gV.type, NULL);
	if(inObj->type == WLZ_2D_DOMAINOBJ)
	{
	  val.v = WlzNewValueTb(obj0, vTT, bV, &errNum);
	}
	else /* inObj->type == WLZ_3D_DOMAINOBJ */
	{
	  val.vox = WlzNewValuesVox(obj0, vTT, bV, &errNum);
	}
      }
      if(errNum == WLZ_ERR_NONE)
      {
        outObj = WlzMakeMain(inObj->type, obj0->domain, val, NULL, NULL,
	                     &errNum);
      }
      if((errNum == WLZ_ERR_NONE) && (gV.type != WLZ_GREY_ERROR))
      {
        errNum = WlzGreySetValue(outObj, gV);
      }
    }
  }
  if(ok)
  {
    errNum = WLZ_ERR_WRITE_EOF;
    if(((fP = (strcmp(outObjFileStr, "-")?
              fopen(outObjFileStr, "w"): stdout)) == NULL) ||
       ((errNum = WlzWriteObj(fP, outObj)) != WLZ_ERR_NONE))
    {
      ok = 0;
      (void )WlzStringFromErrorNum(errNum, &errMsg);
      (void )fprintf(stderr,
                     "%s: Failed to write output object (%s).\n",
		     *argv, errMsg);
    }
    if(fP && strcmp(outObjFileStr, "-"))
    {
      (void )fclose(fP);
    }
  }
  (void )WlzFreeObj(inObj);
  if(lObj != NULL)
  {
    for(idN = 0; idN < nObj; ++idN)
    {
      (void )WlzFreeObj(lObj[idN]);
    }
    AlcFree(lObj);
  }
  (void )WlzFreeObj(outObj);
  if(usage)
  {
    (void )fprintf(stderr,
    "Usage: %s%sExample: %s%s",
    *argv,
    " [-c#] [-g#] [-G#] [-h] [-m#] [-n#] [-N#]\n"
    "       [-o<output object>] [-r#]] [-x#] [<input object>]\n"
    "Options:\n"
    "  -c  Connectivity: 4, 6, 8, 18 or 26 connected (default 8 for 2D\n"
    "      domains and 26 for 3D domains).\n"
    "  -g  Grey value for marker. This is a single number for all except\n"
    "      RGBA (colour) grey values. RGBA components must be separated by\n"
    "      by a comma.\n"
    "  -G  Grey value type for marker specified by letter:\n"
    "        v  no grey values (default).\n"
    "        u  unsigned byte grey values.\n"
    "        s  short grey values.\n"
    "        i  int grey values.\n"
    "        f  int grey values.\n"
    "        d  int grey values.\n"
    "        r  red, green, blue, alpha grey values.\n"
    "  -h  Help, prints usage message.\n"
    "  -m  Marker type specified by a number:\n"
    "        1  circle/sphere (default)\n"
    "        2  square/cube\n"
    "  -n  Threshold minimum area/volume of blob for a marker (default\n"
    "      >= 1).\n"
    "  -N  Threshold maximum area/volume of blob for a marker. If zero\n"
    "      there is no upper limit. (default  0).\n"
    "  -o  Output object file.\n"
    "  -r  Marker radius. Attempts to keep the same area/volume if zero.\n"
    "      (default 0).\n"
    "  -x  Maximum number of separate regions in the object (default 1024).\n"
    "Reads a spatial domain object and replaces each spatialy separate\n"
    "region with a marker placed at the centre of mass of the region.\n"
    "All files are read from the standard input and written to the standard\n"
    "output unless filenames are given.\n"
    "If grey values are required then the grey value type must be set before\n"
    "the actual grey value.\n",
    *argv,
    " -o out.wlz -n 4 -r 10 -G r -g 200,100,0,255 in.wlz\n"
    "A spatial domain object is read from the file in.wlz and each\n"
    "spatialy separate region of the domain is replaced by a circle or\n"
    "sphere of radius 10 (pixels). All small regions with less than four\n"
    "(pixels voxels) is ignored. The output object (with grey values set\n"
    "to orange) is written to the file out.wlz.\n");
  }
  return(!ok);
}