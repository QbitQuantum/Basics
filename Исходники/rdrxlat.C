/* assume the source is an array which is n_az x n_bins in size and we need
   to process the lot
*/
void rdr_xlat::relocate(unsigned char *src, unsigned char *dest, int n_az, 
		    int src_n_bins, int dest_n_bins,
		    float rng_res, float src_start_rng, float dest_start_rng, 
		    double dest_ofs_x, double dest_ofs_y)
{
    int i, j;    /* array location for current destination point of interest */
    double t, r; /* polar co-ordinates for destination */
    double dest_x, dest_y; /* cartesian co-ordinates for destination */
    double dest_t, dest_i_f;          /* polar angle for source data */
    int dest_radl_ofs;
    int dest_i, dest_j;      /* array location for the nearest dest point */

    double src_x, src_y;   /* cartesion co-ordinates for source */
    double src_t, src_i_f;          /* polar angle for source data */
    int src_radl_ofs;
    int src_i, src_j;      /* array location for the nearest source point */

    double cost, sint;

#ifdef RINGS
    {
        extern void dump(char *);
        int i, j;
        for(j=0; j<n_bins; j++) { /*fill columns first */
            for(i=0; i< n_az; i++) {
                src[i*n_bins + j] = 'a' + (j/3)%26;
            } 
        }
        dump(src);
    }
#endif /* RINGS */
#ifdef WEDGES
{
        extern void dump(char *);
        int i, j;
        for(i=0; i< n_az; i++) /*fill rows first */{
            for(j=0; j<n_bins; j++) { 
                src[i*n_bins + j] = 'a' + (i/3)%26;
            } 
        }
        dump(src);
    }
#endif /* WEDGES */

    /* traverse destination volume and get nearest src point */
    /* rows are the polar angle, columns are the radial distance */

    for(i=0; i<n_az; i++) {  /*traverse along the row (range) first */
	t = DEG2RAD * i;
	cost = cos(t);
	sint = sin(t);
	dest_radl_ofs = i*dest_n_bins;
	for(j=0; j<dest_n_bins; j++) {
            r = dest_start_rng + (rng_res * (j + 0.5));	// add 0.5 to get centre of range bin
            dest_x = r * cost;
            dest_y = r * sint;

            src_x = dest_x - dest_ofs_x;
            src_y = dest_y - dest_ofs_y;
            src_t = atan2(src_y, src_x);
            src_i_f = src_t / DEG2RAD;
	    if (src_i_f < -0.5) src_i_f += 360.0;
	    src_i = (int)(0.5 + src_i_f);
            src_j = (int)(0.5 + ((hypot(src_x, src_y) - src_start_rng) /
		rng_res));

            if((src_j < src_n_bins)&&(src_j >= 0)) { 
                dest[dest_radl_ofs + j] = src[src_i*src_n_bins + src_j];
            }
        }
    }
    
    /* traverse src array and xlat to dest, replace dest cell if src > dest */
    for(i=0; i<n_az; i++) {  /*traverse along the row (range) first */
	t = DEG2RAD * i;
	cost = cos(t);
	sint = sin(t);
	src_radl_ofs = i*src_n_bins;
	for(j=0; j<src_n_bins; j++) {
            r = src_start_rng + (rng_res * (j + 0.5));	// add 0.5 to get centre of range bin
            src_x = r * cost;
            src_y = r * sint;

            dest_x = src_x + dest_ofs_x;
            dest_y = src_y + dest_ofs_y;
            dest_t = atan2(dest_y, dest_x);
            dest_i_f = dest_t / DEG2RAD;
	    if (dest_i_f < -0.5) dest_i_f += 360.0;
	    dest_i = (int)(0.5 + dest_i_f);
	    dest_j = (int)(0.5 + ((hypot(dest_x, dest_y) - dest_start_rng) /
		rng_res));

            if((dest_j < dest_n_bins)&&(dest_j >= 0)&&	// only overwrite smaller value
		(dest[dest_i*dest_n_bins + dest_j] < src[src_radl_ofs + j])) { 
                dest[dest_i*dest_n_bins + dest_j] = src[src_radl_ofs + j];
            }
}
    }
}