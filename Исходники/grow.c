int grow_poly(polygon **poly, int npolys, polygon *polys[/*npolys*/], long double grow_angle, long double mtol, int *np){
  int i, ip, jp, iret, ier, dn;
  long double s, cmi, cm_new,theta, theta_new, tol;
  polygon *poly1= 0x0;
  
/* part_poly should lasso all one-boundary polygons */
#define ALL_ONEBOUNDARY		2
  /* how part_poly should tighten lasso */
#define ADJUST_LASSO            2
  /* part_poly should force polygon to be split even if no part can be lassoed */
#define FORCE_SPLIT             1
  /* partition_poly should overwrite all original polygons */
#define OVERWRITE_ORIGINAL      2

  if((*poly)->pixel!=0){
    fprintf(stderr, "Error: input polygon is pixelized. The grow function can only be applied to non-pixelized polygons.");
    return(-1);
  }
  
  *np=0;
  // partition disconnected polygons
  tol = mtol;
  ier = partition_poly(poly, npolys, polys, tol, ALL_ONEBOUNDARY, ADJUST_LASSO, FORCE_SPLIT, OVERWRITE_ORIGINAL, &dn); 
  // error
  if (ier == -1) {
    fprintf(stderr, "grow: UHOH at polygon %lld; continuing ...\n",polys[i]->id);
    // return(-1);
      // failed to partition polygon into desired number of parts
  } else if (ier == 1) {
    fprintf(stderr, "grow: failed to partition polygon %lld fully; partitioned it into %d parts\n", (*poly)->id, dn + 1);
  }  
  *np+=dn;
  
  // check whether exceeded maximum number of polygons
  //printf("(2) n = %d\n", n);
  if (*np > npolys) {
    fprintf(stderr, "grow: total number of polygons exceeded maximum\n");
    fprintf(stderr, "if you need more space, enlarge NPOLYSMAX in defines.h, and recompile\n");
    return(-1);
  }
  
  for(i=-1; i<*np; i++){
    if(i=-1)
      poly1=(*poly);
    else
      poly1=polys[i];
    
    for (ip = 0; ip < poly1->np; ip++) { 
      cmi=poly1->cm[ip];
      //convert cm into an angle
      s = sqrtl(fabsl(cmi) / 2.);
      if (s > 1.) s = 1.;
      theta = 2. * asinl(s);
      theta=(cmi >= 0.)? theta : -theta;
      
      theta_new=theta+grow_angle;
      
      // if growing angle has caused cap to encompass whole sphere, set cm_new=2 to make it superfluous
      if(theta>=0 && theta_new>=PI)
	cm_new=2.;
      else if(theta<0 && theta_new>=0) 
	cm_new=2.;
      // if growing angle (with a negative value for grow_angle) has shrunk cap to less than nothing, make polygon null
      else if(theta>=0 && theta_new<0) 
	cm_new=0.;
      else if(theta<0 && theta_new<=-PI) 
	cm_new=0.;
      // otherwise convert normally
      else{
	/* 1 - cosl(radius) = 2 sin^2(radius/2) */
	s = sinl(theta_new / 2.);
	cm_new = s * s * 2.;
	cm_new = (theta_new >= 0.)? cm_new : -cm_new;
      }
      
      poly1->cm[ip]=cm_new;
    }
    tol=mtol;
    iret=prune_poly(poly1,tol);
  }
  return(iret);
}