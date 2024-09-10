int uiDrawMatrixInvert(uiDrawMatrix *m)
{
    D2D1_MATRIX_3X2_F d;

    m2d(m, &d);
    if (D2D1InvertMatrix(&d) == FALSE)
        return 0;
    d2m(&d, m);
    return 1;
}