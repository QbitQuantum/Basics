int
countHits(struct bu_vlb *vlb)
{
    unsigned char *c;
    int numRays = 0;
    int rayNum;
    int hitCount = 0;

    c = bu_vlb_addr(vlb);
    numRays = BU_GLONG(c);

    c += SIZEOF_NETWORK_LONG;

    for(rayNum=0 ; rayNum<numRays ; rayNum++) {
	int numPartitions = 0;
	int partNo;

	numPartitions = BU_GLONG(c);
	c += SIZEOF_NETWORK_LONG;

	for(partNo=0 ; partNo<numPartitions ; partNo++) {
	    point_t enterPt;
	    point_t exitPt;
	    vect_t enterNorm;
	    vect_t exitNorm;
	    double inObl;
	    double outObl;
	    /* UNUSED: int regionIndex; */

	    ntohd((unsigned char *)enterPt, c, 3);
	    c += SIZEOF_NETWORK_DOUBLE * 3;

	    ntohd((unsigned char *)exitPt, c, 3);
	    c += SIZEOF_NETWORK_DOUBLE * 3;

	    ntohd((unsigned char *)enterNorm, c, 3);
	    c += SIZEOF_NETWORK_DOUBLE * 3;

	    ntohd((unsigned char *)exitNorm, c, 3);
	    c += SIZEOF_NETWORK_DOUBLE * 3;

	    ntohd((unsigned char*)&inObl, c, 1);
	    c += SIZEOF_NETWORK_DOUBLE;

	    ntohd((unsigned char*)&outObl, c, 1);
	    c += SIZEOF_NETWORK_DOUBLE;

	    /* UNUSED: regionIndex = BU_GLONG(c); */
	    c += SIZEOF_NETWORK_LONG;

	    hitCount++;
	}
    }
    return hitCount;
}