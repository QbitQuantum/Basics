void get_acceleration_by_sunl_test(void)
{
    long double utc_in_mjd = 59865.0L;
    long double coord[3], acceleration[3];

    coord[0] = -43203.606331156676L;
    coord[1] = 932.8531254505084L;
    coord[2] = 105.03042685970608L;

    get_acceleration_by_sunl(utc_in_mjd, coord, acceleration);

    assert(fabsl(fabsl(acceleration[0]) - 2.8480208700617356e-009L) < 1e-18);
    assert(fabsl(fabsl(acceleration[1]) - 1.5087331078186935e-009L) < 1e-18);
    assert(fabsl(fabsl(acceleration[2]) - 6.4204449389352687e-010L) < 1e-18);

    return;
}