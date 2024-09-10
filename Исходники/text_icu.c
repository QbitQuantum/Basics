int32_t __hs_uspoof_serialize(USpoofChecker *sc, void *data, int32_t capacity,
                              UErrorCode *status)
{
    return uspoof_serialize(sc, data, capacity, status);
}