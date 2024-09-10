//l corresponds to vector with 3 elements
void lsort(float *c, float *a, float *b, int *l)
{
    int tmp = 0;
    float arg1 = 0.0;
    float arg2 = 0.0;

    //initialise
    *l = 0;
    *(l + 1) = 1;
    *(l + 2) = 2;

    if (c < a)
    {
        tmp = *l;
        *l = *(l + 1);
        *(l + 1) = tmp;

        arg1 = *c;
        arg2 = *a;
        *c = FMAX(arg1, arg2);
        *a = FMIN(arg1, arg2);
    }
    else
        ;

    if (c < b)
    {
        tmp = *l;
        *l = *(l + 2);
        *(l + 2) = tmp;

        arg1 = *c;
        arg2 = *b;
        *c = FMAX(arg1, arg2);
        *b = FMIN(arg1, arg2);
    }
    else
        ;

    if (a < b)
    {
        tmp = *(l + 1);
        *(l + 1) = *(l + 2);
        *(l + 2) = tmp;

        arg1 = *a;
        arg2 = *b;
        *a = FMAX(arg1, arg2);
        *b = FMIN(arg1, arg2);
    }
    else
        ;
}