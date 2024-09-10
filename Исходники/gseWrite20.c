static void dbDelaz(float *slat, float *slon, float *elat, float *elon,
           float *delt, float *dist, float *azim, float *bazim)
{
    /* Builtin functions */
/*    double tan(), atan(), sin(), cos(), acos(), sqrt(); */

    /* Local variables */
    static double  a, b, c__, z__, celon, elatr, cslon, elonr, selon, a1,
            b1, c1, slatr, slonr, sslon, cd, ceclat, bz, cz, eclatr, seclat,
            csclat, sclatr, ssclat, aaa, cbz;

/* cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
/*  This subroutine calculates the four quantities that depend on the  c */
/*  relative locations on the globe of epicenter and station.          c */
/*  Output: delt(angular separation id degrees), dist(geodesic distancec */
/*  in kilometers), azim(epicenter-to-station azimuth, in degrees N    c */
/*  thru E), and bazim(station-to-epicenter azimuth, in degrees N thru E */
/*  Input: slat(station latitude), slon(station longitude), elat(epi-  c */
/*  center latitude), and elon(epicenter longitude).  Latitudes(which  c */
/*  are input as geographic latitudes) are to be given from 0 to 90    c */
/*  degrees, +indicating North, and - indicating South.  Longitudes    c */
/*  are to be given from 0 to 180 degrees, + indicating East and -     c */
/*  indicating West, with  0=Greenwich Meridian.                       c */
/* cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */

/*  converting input angles from degrees to radians */
/*  (suffix r always denotes radian measure) */
    slatr = *slat * (float).01745329;
    slonr = *slon * (float).01745329;
    elatr = *elat * (float).01745329;
    elonr = *elon * (float).01745329;
/*  converting geographic latitudes to geocentric latitudes */
    aaa = tan(slatr) * (float).996647;
    slatr = atan(aaa);
    aaa = tan(elatr) * (float).996647;
    elatr = atan(aaa);
/*  At this point latitudes are converted into colatitudes, which run  c
*/
/*  from 0 at North Pole to 180 at South Pole.  Also, longitudes are   c
*/
/*  re-evaluated so that they run from 0 to 360 from Greenwich Eastward */
/*  sclatr=station colatitude   eclatr=epicenter colatitude  (radians) */
    sclatr = (float)1.570796327 - slatr;
    if (slonr >= 0.) {
        goto L20;
    } else {
        goto L10;
    }
L10:
    slonr += (float)6.283185307;
L20:
    eclatr = (float)1.570796327 - elatr;
    if (elonr >= 0.) {
        goto L40;
    } else {
        goto L30;
    }
L30:
    elonr += (float)6.283185307;
L40:
    seclat = sin(eclatr);
    ceclat = cos(eclatr);
    selon = sin(elonr);
    celon = cos(elonr);
    ssclat = sin(sclatr);
    csclat = cos(sclatr);
    sslon = sin(slonr);
    cslon = cos(slonr);
/*  calculation of direction cosines of station (a1,b1,c1) and of      c
*/
/*  epicenter (a,b,c). For this calculation, x-axis is thru Greenwich  c
*/
/*  Meridian, y-axis at 90E longitude, and z-axis thru North Pole.     c
*/
    a = seclat * celon;
    b = seclat * selon;
    c__ = ceclat;
    a1 = ssclat * cslon;
    b1 = ssclat * sslon;
    c1 = csclat;
/*  Now you have all the info necessary to compute delt, dist, azim, */
/*  and bazim.  For reference:  cosine of delta=cd, cosine of azimuth=cz
*/
/*  azim. in radians=z, cosine of backazimuth=cbz, and back-azimuth */
/*  in radians=bz. */
    cd = a * a1 + b * b1 + c__ * c1;
    *delt = acos(cd) * (float)57.29577951;
    *dist = *delt * (float).01745329252 * (float)6371.;
/*  computation of cz and z.  The following formula is derivable */
/*  from Bullen orig via analytic geometry. */
    cz = (seclat * csclat - ceclat * ssclat * (celon * cslon + selon * sslon))
             / sqrt((float)1. - cd * cd);
    z__ = acos(cz);
/*  The following test determines whether z should be > orig < 180 degrees.
*/
    if (sslon * celon - cslon * selon < (float)0.) {
        z__ = (float)6.283185307 - z__;
    }
    *azim = z__ * (float)57.29577951;
/*  computation of cbz and bz.  This is accomplished by switching the */
/*  roles of station and epicenter in the previous formula. */
    cbz = (ssclat * ceclat - csclat * seclat * (cslon * celon + sslon * selon)
            ) / sqrt((float)1. - cd * cd);
    bz = acos(cbz);
/*  The following test determines whether bz should be > orig < 180 degrees.
 */
    if (selon * cslon - celon * sslon < (float)0.) {
        bz = (float)6.283185307 - bz;
    }
    *bazim = bz * (float)57.29577951;
}