int64 hpix_ring_num(const struct healpix* hpix, double z) {
    int64 nside=hpix->nside;

    // rounds double to nearest long long int
    int64 iring = llrintl( nside*(2.-1.5*z) );

    // north cap
    if (z > M_TWOTHIRD) {
        iring = llrintl( nside* sqrt(3.*(1.-z)) );
        if (iring == 0) {
            iring = 1;
        }
    } else if (z < -M_TWOTHIRD) {
        iring = llrintl( nside* sqrt(3.*(1.+z)) );

        if (iring == 0) {
            iring = 1;
        }
        iring = 4*nside - iring;
    }

    return iring;
}