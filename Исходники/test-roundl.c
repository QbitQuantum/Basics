int
main ()
{
    DECL_LONG_DOUBLE_ROUNDING

    BEGIN_LONG_DOUBLE_ROUNDING ();

    /* Zero.  */
    ASSERT (roundl (0.0L) == 0.0L);
    ASSERT (roundl (minus_zerol) == 0.0L);
    /* Positive numbers.  */
    ASSERT (roundl (0.3L) == 0.0L);
    ASSERT (roundl (0.5L) == 1.0L);
    ASSERT (roundl (0.7L) == 1.0L);
    ASSERT (roundl (1.0L) == 1.0L);
    ASSERT (roundl (1.5L) == 2.0L);
    ASSERT (roundl (2.5L) == 3.0L);
    ASSERT (roundl (1.999L) == 2.0L);
    ASSERT (roundl (2.0L) == 2.0L);
    ASSERT (roundl (65535.999L) == 65536.0L);
    ASSERT (roundl (65536.0L) == 65536.0L);
    ASSERT (roundl (65536.001L) == 65536.0L);
    ASSERT (roundl (2.341e31L) == 2.341e31L);
    /* Negative numbers.  */
    ASSERT (roundl (-0.3L) == 0.0L);
    ASSERT (roundl (-0.5L) == -1.0L);
    ASSERT (roundl (-0.7L) == -1.0L);
    ASSERT (roundl (-1.0L) == -1.0L);
    ASSERT (roundl (-1.5L) == -2.0L);
    ASSERT (roundl (-2.5L) == -3.0L);
    ASSERT (roundl (-1.999L) == -2.0L);
    ASSERT (roundl (-2.0L) == -2.0L);
    ASSERT (roundl (-65535.999L) == -65536.0L);
    ASSERT (roundl (-65536.0L) == -65536.0L);
    ASSERT (roundl (-65536.001L) == -65536.0L);
    ASSERT (roundl (-2.341e31L) == -2.341e31L);
    /* Infinite numbers.  */
    ASSERT (roundl (Infinityl ()) == Infinityl ());
    ASSERT (roundl (- Infinityl ()) == - Infinityl ());
    /* NaNs.  */
    ASSERT (isnanl (roundl (NaNl ())));

    return 0;
}