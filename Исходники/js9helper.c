int parseSection(char *s, int *x0, int *x1, int *y0, int *y1, int *block){
  int itype=0, got=0;
  double tx0=0, tx1=0, ty0=0, ty1=0;
  double dim1, dim2, cen1, cen2;
  char s1[SLEN], s2[SLEN], s3[SLEN], s4[SLEN], s5[SLEN];
  char *t;
  /* look for different ways of specifying the section -- order counts! */
  if(sscanf(s,
     "%32[-0-9.dDeE] : %32[-0-9.dDeE] , %32[-0-9.dDeE] : %32[-0-9.dDeE] , %32[0-9]",
     s1, s2, s3, s4, s5) == 5){
    tx0 = atof(s1);
    tx1 = atof(s2);
    ty0 = atof(s3);
    ty1 = atof(s4);
    *block = MAX(1, atof(s5));
    got = 1;
  } else if(sscanf(s,
	  "%32[-0-9.dDeE] : %32[-0-9.dDeE] , %32[-0-9.dDeE] : %32[-0-9.dDeE]",
	  s1, s2, s3, s4) == 4){
    tx0 = atof(s1);
    tx1 = atof(s2);
    ty0 = atof(s3);
    ty1 = atof(s4);
    *block = 1;
    got = 1;
  } else if(sscanf(s,
	    "%32[-0-9.dDeE] : %32[-0-9.dDeE] , %32[0-9as]",
	    s1, s2, s3) == 3){
    tx0 = atof(s1);
    tx1 = atof(s2);
    ty0 = tx0;
    ty1 = tx1;
    *block = MAX(1, atof(s3));
    got = 1;
  } else if(sscanf(s,
	    "%32[-0-9.dDeE] : %32[-0-9.dDeE]",
	    s1, s2) == 2){
    tx0 = atof(s1);
    tx1 = atof(s2);
    ty0 = tx0;
    ty1 = tx1;
    *block = 1;
    got = 1;
  } else if(sscanf(s,
	    "%32[0-9.dDeE] @ %32[-0-9.dDeE] , %32[0-9.dDeE] @ %32[-0-9.dDeE] , %32[0-9]",
	    s1, s2, s3, s4, s5) == 5){
    dim1 = atof(s1);
    cen1 = atof(s2);
    dim2 = atof(s3);
    cen2 = atof(s4);
    *block = MAX(1, strtol(s5, &t, 0));
    itype = 1;
    got = 1;
  } else if(sscanf(s,
	    "%32[0-9.dDeE] @ %32[-0-9.dDeE] , %32[0-9.dDeE] @ %32[-0-9.dDeE]",
	     s1, s2, s3, s4) == 4){
    dim1 = atof(s1);
    cen1 = atof(s2);
    dim2 = atof(s3);
    cen2 = atof(s4);
    *block = 1;
    itype = 1;
    got = 1;
  } else if(sscanf(s,
	    "%32[0-9.dDeE] @ %32[-0-9.dDeE]  , %32[0-9]",
		   s1, s2, s3) == 3){
    dim1 = atof(s1);
    cen1 = atof(s2);
    dim2 = dim1;
    cen2 = cen1;
    *block = MAX(1, strtol(s3, &t, 0));
    itype = 1;
    got = 1;
  } else if(sscanf(s,
	    "%32[0-9.dDeE] @ %32[-0-9.dDeE]",
	    s1, s2) == 2){
    dim1 = atof(s1);
    cen1 = atof(s2);
    dim2 = dim1;
    cen2 = cen1;
    itype = 1;
    got = 1;
  }
  /* if we are processing dim@center, we need to calculate section values */
  if( itype ){
    tx0 = cen1 - ((dim1+1)/2) + 1;
    ty0 = cen2 - ((dim2+1)/2) + 1;
    /* this method maintains the center and changes the dimensions */
    /* Frank, Eric, and John all prefer this method, so that the user
       gets the center he asked for, even if the image is reduced */
    tx1 = cen1 + (dim1/2);
    ty1 = cen2 + (dim2/2);
  }
  /* now we can integerize and set the output values */
  *x0 = (int)tx0;
  *x1 = (int)tx1;
  *y0 = (int)ty0;
  *y1 = (int)ty1;
  return got;
}