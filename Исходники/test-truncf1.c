int
main ()
{
    /* Zero.  */
    ASSERT (truncf (0.0f) == 0.0f);
    ASSERT (truncf (minus_zerof) == 0.0f);
    /* Positive numbers.  */
    ASSERT (truncf (0.3f) == 0.0f);
    ASSERT (truncf (0.7f) == 0.0f);
    ASSERT (truncf (1.0f) == 1.0f);
    ASSERT (truncf (1.5f) == 1.0f);
    ASSERT (truncf (1.999f) == 1.0f);
    ASSERT (truncf (2.0f) == 2.0f);
    ASSERT (truncf (65535.99f) == 65535.0f);
    ASSERT (truncf (65536.0f) == 65536.0f);
    ASSERT (truncf (2.341e31f) == 2.341e31f);
    /* Negative numbers.  */
    ASSERT (truncf (-0.3f) == 0.0f);
    ASSERT (truncf (-0.7f) == 0.0f);
    ASSERT (truncf (-1.0f) == -1.0f);
    ASSERT (truncf (-1.5f) == -1.0f);
    ASSERT (truncf (-1.999f) == -1.0f);
    ASSERT (truncf (-2.0f) == -2.0f);
    ASSERT (truncf (-65535.99f) == -65535.0f);
    ASSERT (truncf (-65536.0f) == -65536.0f);
    ASSERT (truncf (-2.341e31f) == -2.341e31f);
    /* Infinite numbers.  */
    ASSERT (truncf (Infinityf ()) == Infinityf ());
    ASSERT (truncf (- Infinityf ()) == - Infinityf ());
    /* NaNs.  */
    ASSERT (isnanf (truncf (NaNf ())));

    return 0;
}