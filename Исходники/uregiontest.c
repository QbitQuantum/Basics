static void TestKnownRegions() {
    const KnownRegion * rd;
    for (rd = knownRegions; rd->code != NULL ; rd++ ) {
        UErrorCode status = U_ZERO_ERROR;
        const URegion *r = uregion_getRegionFromCode(rd->code, &status);
        if ( U_SUCCESS(status) ) {
            int32_t n = uregion_getNumericCode(r);
            int32_t e = rd->numeric;
            if ( n != e ) {
                log_err("ERROR: Numeric code mismatch for region %s.  Expected:%d Got:%d\n", uregion_getRegionCode(r), e, n );
            }
            if (uregion_getType(r) != rd->type) {
                log_err("ERROR: Expected region %s to be of type %d. Got: %d\n", uregion_getRegionCode(r), rd->type, uregion_getType(r) );
            }
            if ( e > 0 ) {
                const URegion *ncRegion = uregion_getRegionFromNumericCode(e, &status);
                if ( !uregion_areEqual(ncRegion, r) && e != 891 ) { // 891 is special case - CS and YU both deprecated codes for region 891
                    log_err("ERROR: Creating region %s by its numeric code returned a different region. Got: %s instead.\n",
                        uregion_getRegionCode(r), uregion_getRegionCode(ncRegion) );
                }
             }
        } else {
            log_data_err("ERROR: Known region %s was not recognized.\n", rd->code);
        }
    }
}