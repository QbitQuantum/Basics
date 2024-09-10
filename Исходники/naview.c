static void traverse_loop(struct loop *lp, struct connection *anchor_connection)
/*
*   This is the workhorse of the display program. The algorithm is
*   recursive based on processing individual loops. Each base pairing
*   region is displayed using the direction given by the circle diagram,
*   and the connections between the regions is drawn by equally spaced
*   points. The radius of the loop is set to minimize the square error
*   for lengths between sequential bases in the loops. The "correct"
*   length for base links is 1. If the least squares fitting of the
*   radius results in loops being less than 1/2 unit apart, then that
*   segment is extruded. 
*   
*   The variable, anchor_connection, gives the connection to the loop
*   processed in an previous level of recursion.
*/

{
  double xs,ys,xe,ye,xn,yn,angleinc,r;
  double radius,xc,yc,xo,yo,astart,aend,a;
  struct connection *cp,*cpnext,**cpp,*acp,*cpprev;
  int i,j,n,ic;
  double da,maxang;
  int count,icstart,icend,icmiddle,icroot;
  logical done,done_all_connections,rooted;
  int sign;
  double midx,midy,nrx,nry,mx,my,vx,vy,dotmv,nmidx,nmidy;
  int icstart1,icup,icdown,icnext,direction;
  double dan,dx,dy,rr;
  double cpx,cpy,cpnextx,cpnexty,cnx,cny,rcn,rc,lnx,lny,rl,ac,acn,sx,sy,dcp;
  int imaxloop;
    
  angleinc = 2 * pi / (nbase+1);
  acp = NULL;
  icroot = -1;
  for (cpp=lp->connections, ic = 0; (cp = *cpp); cpp++, ic++) {
    /*	xs = cos(angleinc*cp->start);
	ys = sin(angleinc*cp->start);
	xe = cos(angleinc*cp->end);
	ye = sin(angleinc*cp->end); */
    xs = -sin(angleinc*cp->start);
    ys = cos(angleinc*cp->start);
    xe = -sin(angleinc*cp->end);
    ye = cos(angleinc*cp->end);
    xn = ye-ys;
    yn = xs-xe;
    r = sqrt(xn*xn + yn*yn);
    cp->xrad = xn/r;
    cp->yrad = yn/r;
    cp->angle = atan2(yn,xn);
    if (cp->angle < 0.0) cp->angle += 2*pi;
    if (anchor_connection != NULL &&
	anchor_connection->region == cp->region) {
      acp = cp;
      icroot = ic;
    }
  }
	
 set_radius:
  determine_radius(lp,lencut);
  radius = lp->radius;
  if (anchor_connection == NULL) xc = yc = 0.0;
  else {
    xo = (bases[acp->start].x+bases[acp->end].x) / 2.0;
    yo = (bases[acp->start].y+bases[acp->end].y) / 2.0;
    xc = xo - radius * acp->xrad;
    yc = yo - radius * acp->yrad;
  }
	
  /*
   *   The construction of the connectors will proceed in blocks of
   *   connected connectors, where a connected connector pairs means
   *   two connectors that are forced out of the drawn circle because they
   *   are too close together in angle.
   */

  /*
   *   First, find the start of a block of connected connectors
   */

  if (icroot == -1) 
    icstart = 0;
  else icstart = icroot;
  cp = lp->connections[icstart];
  count = 0;
  if (debug) printf("Now processing loop %d\n",lp->number);
  done = false;
  do {
    j = icstart - 1;
    if (j < 0) j = lp->nconnection - 1;
    cpprev = lp->connections[j];
    if (!connected_connection(cpprev,cp)) {
      done = true;
    }
    else {
      icstart = j;
      cp = cpprev;
    }
    if (++count > lp->nconnection) {
      /*
       *  Here everything is connected. Break on maximum angular separation
       *  between connections. 
       */
      maxang = -1.0;
      for (ic = 0;  ic < lp->nconnection;  ic++) {
	j = ic + 1;
	if (j >= lp->nconnection) j = 0;
	cp = lp->connections[ic];
	cpnext = lp->connections[j];
	ac = cpnext->angle - cp->angle;
	if (ac < 0.0) ac += 2*pi;
	if (ac > maxang) {
	  maxang = ac;
	  imaxloop = ic;
	}
      }
      icend = imaxloop;
      icstart = imaxloop + 1;
      if (icstart >= lp->nconnection) icstart = 0;
      cp = lp->connections[icend];
      cp->broken = true;
      done = true;
    }
  } while    (!done);
  done_all_connections = false;
  icstart1 = icstart;
  if (debug) printf("Icstart1 = %d\n",icstart1);
  while (!done_all_connections) {
    count = 0;
    done = false;
    icend = icstart;
    rooted = false;
    while (!done) {
      cp = lp->connections[icend];
      if (icend == icroot) rooted = true;
      j = icend + 1;
      if (j >= lp->nconnection) {
	j = 0;
      }
      cpnext = lp->connections[j];
      if (connected_connection(cp,cpnext)) {
	if (++count >= lp->nconnection) break;
	icend = j;
      }
      else {
	done = true;
      }
    }
    icmiddle = find_ic_middle(icstart,icend,anchor_connection,acp,lp);
    ic = icup = icdown = icmiddle;
    if (debug)
      printf("IC start = %d  middle = %d  end = %d\n",
	     icstart,icmiddle,icend);
    done = false;
    direction = 0;
    while (!done) {
      if (direction < 0) {
	ic = icup;
      }
      else if (direction == 0) {
	ic = icmiddle;
      }
      else {
	ic = icdown;
      }
      if (ic >= 0) {
	cp = lp->connections[ic];
	if (anchor_connection == NULL || acp != cp) {
	  if (direction == 0) {
	    astart = cp->angle - asin(1.0/2.0/radius);
	    aend = cp->angle + asin(1.0/2.0/radius);
	    bases[cp->start].x = xc + radius*cos(astart);
	    bases[cp->start].y = yc + radius*sin(astart);
	    bases[cp->end].x = xc + radius*cos(aend);
	    bases[cp->end].y = yc + radius*sin(aend);
	  }
	  else if (direction < 0) {
	    j = ic + 1;
	    if (j >= lp->nconnection) j = 0;
	    cp = lp->connections[ic];
	    cpnext = lp->connections[j];
	    cpx = cp->xrad;
	    cpy = cp->yrad;
	    ac = (cp->angle + cpnext->angle) / 2.0;
	    if (cp->angle > cpnext->angle) ac -= pi;
	    cnx = cos(ac);
	    cny = sin(ac);
	    lnx = cny;
	    lny = -cnx;
	    da = cpnext->angle - cp->angle;
	    if (da < 0.0) da += 2*pi;
	    if (cp->extruded) {
	      if (da <= pi/2) rl = 2.0;
	      else rl = 1.5;
	    }
	    else {
	      rl = 1.0;
	    }
	    bases[cp->end].x = bases[cpnext->start].x + rl*lnx;
	    bases[cp->end].y = bases[cpnext->start].y + rl*lny;
	    bases[cp->start].x = bases[cp->end].x + cpy;
	    bases[cp->start].y = bases[cp->end].y - cpx;
	  }
	  else {
	    j = ic - 1;
	    if (j < 0) j = lp->nconnection - 1;
	    cp = lp->connections[j];
	    cpnext = lp->connections[ic];
	    cpnextx = cpnext->xrad;
	    cpnexty = cpnext->yrad;
	    ac = (cp->angle + cpnext->angle) / 2.0;
	    if (cp->angle > cpnext->angle) ac -= pi;
	    cnx = cos(ac);
	    cny = sin(ac);
	    lnx = -cny;
	    lny = cnx;
	    da = cpnext->angle - cp->angle;
	    if (da < 0.0) da += 2*pi;
	    if (cp->extruded) {
	      if (da <= pi/2) rl = 2.0;
	      else rl = 1.5;
	    }
	    else {
	      rl = 1.0;
	    }
	    bases[cpnext->start].x = bases[cp->end].x + rl*lnx;
	    bases[cpnext->start].y = bases[cp->end].y + rl*lny;
	    bases[cpnext->end].x = bases[cpnext->start].x - cpnexty;
	    bases[cpnext->end].y = bases[cpnext->start].y + cpnextx;
	  }
	}
      }
      if (direction < 0) {
	if (icdown == icend) {
	  icdown = -1;
	}
	else if (icdown >= 0) {
	  if (++icdown >= lp->nconnection) {
	    icdown = 0;
	  }
	}
	direction = 1;
      }
      else {
	if (icup == icstart) icup = -1;
	else if (icup >= 0) {
	  if (--icup < 0) {
	    icup = lp->nconnection - 1;
	  }
	}
	direction = -1;
      }
      done = icup == -1 && icdown == -1;
    }
    icnext = icend + 1;
    if (icnext >= lp->nconnection) icnext = 0;
    if (icend != icstart && (! (icstart == icstart1 && icnext == icstart1))) {
      /*
       *	    Move the bases just constructed (or the radius) so
       *	    that the bisector of the end points is radius distance
       *	    away from the loop center.
       */
      cp = lp->connections[icstart];
      cpnext = lp->connections[icend];
      dx = bases[cpnext->end].x - bases[cp->start].x;
      dy = bases[cpnext->end].y - bases[cp->start].y;
      midx = bases[cp->start].x + dx/2.0;
      midy = bases[cp->start].y + dy/2.0;
      rr = sqrt(dx*dx + dy*dy);
      mx = dx / rr;
      my = dy / rr;
      vx = xc - midx;
      vy = yc - midy;
      rr = sqrt(dx*dx + dy*dy);
      vx /= rr;
      vy /= rr;
      dotmv = vx*mx + vy*my;
      nrx = dotmv*mx - vx;
      nry = dotmv*my - vy;
      rr = sqrt(nrx*nrx + nry*nry);
      nrx /= rr;
      nry /= rr;
      /*
       *	    Determine which side of the bisector the center should be.
       */
      dx = bases[cp->start].x - xc;
      dy = bases[cp->start].y - yc;
      ac = atan2(dy,dx);
      if (ac < 0.0) ac += 2*pi;
      dx = bases[cpnext->end].x - xc;
      dy = bases[cpnext->end].y - yc;
      acn = atan2(dy,dx);
      if (acn < 0.0) acn += 2*pi;
      if (acn < ac) acn += 2*pi;
      if (acn - ac > pi) sign = -1;
      else sign = 1;
      nmidx = xc + sign*radius*nrx;
      nmidy = yc + sign*radius*nry;
      if (rooted) {
	xc -= nmidx - midx;
	yc -= nmidy - midy;
      }
      else {
	for (ic=icstart; ; ++ic >= lp->nconnection ? (ic = 0) : 0) {
	  cp = lp->connections[ic];
	  i = cp->start;
	  bases[i].x += nmidx - midx;
	  bases[i].y += nmidy - midy;
	  i = cp->end;
	  bases[i].x += nmidx - midx;
	  bases[i].y += nmidy - midy;
	  if (ic == icend) break;
	}
      }
    }
    icstart = icnext;
    done_all_connections = icstart == icstart1;
  }
  for (ic=0; ic < lp->nconnection; ic++) {
    cp = lp->connections[ic];
    j = ic + 1;
    if (j >= lp->nconnection) j = 0;
    cpnext = lp->connections[j];
    dx = bases[cp->end].x - xc;
    dy = bases[cp->end].y - yc;
    rc = sqrt(dx*dx + dy*dy);
    ac = atan2(dy,dx);
    if (ac < 0.0) ac += 2*pi;
    dx = bases[cpnext->start].x - xc;
    dy = bases[cpnext->start].y - yc;
    rcn = sqrt(dx*dx + dy*dy);
    acn = atan2(dy,dx);
    if (acn < 0.0) acn += 2*pi;
    if (acn < ac) acn += 2*pi;
    dan = acn - ac;
    dcp = cpnext->angle - cp->angle;
    if (dcp <= 0.0) dcp += 2*pi;
    if (fabs(dan-dcp) > pi) {
      if (cp->extruded) {
	fprintf(stderr, "Warning from traverse_loop. Loop %d has crossed regions\n",
	       lp->number);
      }
      else if ((cpnext->start - cp->end) != 1) {
	cp->extruded = true;
	goto set_radius;	    /* Forever shamed */
      }
    }
    if (cp->extruded) {
      construct_extruded_segment(cp,cpnext);
    }
    else {
      n = cpnext->start - cp->end;
      if (n < 0) n += nbase + 1;
      angleinc = dan / n;
      for (j = 1;  j < n;  j++) {
	i = cp->end + j;
	if (i > nbase) i -= nbase + 1;
	a = ac + j*angleinc;
	rr = rc + (rcn-rc)*(a-ac)/dan;
	bases[i].x = xc + rr*cos(a);
	bases[i].y = yc + rr*sin(a);
      }
    }
  }
  for (ic=0; ic < lp->nconnection; ic++) {
    if (icroot != ic) {
      cp = lp->connections[ic];
      generate_region(cp);
      traverse_loop(cp->loop,cp);
    }
  }
  n = 0;
  sx = 0.0;
  sy = 0.0;
  for (ic = 0;  ic < lp->nconnection;  ic++) {
    j = ic + 1;
    if (j >= lp->nconnection) j = 0;
    cp = lp->connections[ic];
    cpnext = lp->connections[j];
    n += 2;
    sx += bases[cp->start].x + bases[cp->end].x;
    sy += bases[cp->start].y + bases[cp->end].y;
    if (!cp->extruded) {
      for (j = cp->end + 1;  j != cpnext->start;  j++) {
	if (j > nbase) j -= nbase + 1;
	n++;
	sx += bases[j].x;
	sy += bases[j].y;
      }
    }
  }
  lp->x = sx / n;
  lp->y = sy / n;

  /* free connections (ih) */
  for (ic = 0;  ic < lp->nconnection;  ic++)
    free(lp->connections[ic]);
  free(lp->connections);
}