void setup_layout(){
register int i,j,k,dir;

#ifdef HAVE_QMP
 if(QMP_get_msg_passing_type()==QMP_GRID){
   printf("This layout should not be used on a grid architecture\n");
   terminate(1);
 }
#endif

    if(mynode()==0){
	printf("LAYOUT = Hypercubes, options = ");
	printf("tstretch,");
	printf("\n");
    }

    /* Figure out dimensions of rectangle */
    if( (nx*ny*nz*nt)%numnodes() == 0){
      squaresize[XUP] = nx; squaresize[YUP] = ny;
      squaresize[ZUP] = nz; squaresize[TUP] = nt;
    }
    else if ( (nx*ny*nz*(nt+1))%numnodes() == 0){
      squaresize[XUP] = nx; squaresize[YUP] = ny;
      squaresize[ZUP] = nz; squaresize[TUP] = nt+1;
    }
    nsquares[XUP] = nsquares[YUP] = nsquares[ZUP] = nsquares[TUP] = 1;

    i = 1;	/* current number of hypercubes */
    while(i<numnodes()){
	/* figure out which prime to divide by starting with largest */
	k = MAXPRIMES-1;
	while( (numnodes()/i)%prime[k] != 0 && k>0 ) --k;
	/* figure out which direction to divide */

	/* find largest even dimension of h-cubes */
	for(j=1,dir=XUP;dir<=TUP;dir++)
	    if( squaresize[dir]>j && squaresize[dir]%prime[k]==0 )
		j=squaresize[dir];

	/* if one direction with largest dimension has already been
	   divided, divide it again.  Otherwise divide first direction
	   with largest dimension. */
	for(dir=XUP;dir<=TUP;dir++)
	    if( squaresize[dir]==j && nsquares[dir]>1 )break;
	if( dir > TUP)for(dir=XUP;dir<=TUP;dir++)
	    if( squaresize[dir]==j )break;
	/* This can fail if I run out of prime factors in the dimensions */
	if(dir > TUP){
	    if(mynode()==0)printf(
	    "LAYOUT: Can't lay out this lattice, not enough factors of %d\n"
		,prime[k]);
	    terminate(1);
	}

	/* do the surgery */
	i*=prime[k]; squaresize[dir] /= prime[k]; nsquares[dir] *= prime[k];
    }

    sites_on_node =
	    squaresize[XUP]*squaresize[YUP]*squaresize[ZUP]*squaresize[TUP];
    sites_on_lastnodes = sites_on_node;

if( mynode()==0)
  printf("ON MOST NODES %d x %d x %d x %d\n",squaresize[XUP],squaresize[YUP],
                squaresize[ZUP],squaresize[TUP]);
    if( !((nx*ny*nz*nt)%numnodes() == 0) && (nx*ny*nz*(nt+1))%numnodes() == 0 ){
	/* stretched t direction by one */
	if( mynode()==0)printf("SOME NODES HAVE FEWER SITES\n");
	if( mynode() >=  nsquares[XUP]*nsquares[YUP]*nsquares[ZUP]*(nsquares[TUP]-1) ){
	    sites_on_node = squaresize[XUP]*squaresize[YUP]*squaresize[ZUP]*(squaresize[TUP]-1);
	    sites_on_lastnodes = sites_on_node;
	}
    }

    /* Need even number of sites per hypercube */
    if( mynode()==0)if( sites_on_node%2 != 0){
	printf("SORRY, CAN'T LAY OUT THIS LATTICE\n");
	terminate(0);
    }
if( mynode()==0 && sites_on_node%2 != 0)
	printf("WATCH OUT FOR EVEN/ODD SITES ON NODE BUG!!!\n");
    even_sites_on_node = odd_sites_on_node = sites_on_node/2;
}