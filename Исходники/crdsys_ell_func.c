double * llh_to_xyz( ellipsoid *el, double llh[3], double xyz[3],
                     double *dEdLn, double *dNdLt )
{
    double bsac,p,clt,slt,cln,sln,hgt;
    clt  = cos(llh[CRD_LAT]);
    slt  = sin(llh[CRD_LAT]);
    cln  = cos(llh[CRD_LON]);
    sln  = sin(llh[CRD_LON]);
	hgt = llh[CRD_HGT];
    bsac = _hypot( el->b*slt, el->a*clt );
    p    = el->a2*clt/bsac + hgt*clt;
    xyz[0] = p*cln;
    xyz[1] = p*sln;
    xyz[2] = el->b2*slt/bsac + llh[CRD_HGT]*slt;

    if( dEdLn ) *dEdLn = p;
    if( dNdLt ) *dNdLt = (el->a2 * el->b2)/(bsac*bsac*bsac) + hgt;

    return &xyz[0];
}