int run_tests()
{
    int result = 0;

    /* Complex string */
    snprintf(str, 256, "y=26*2/2+log10(pi)+2.*pow(2,1*(3+7*.1)*1.1+x{0}[0])*3*4+cos(2.)");
    setup_test('f', 1, 1, src_float, 'f', 1, 1, dest_float);
    result += parse_and_eval(EXPECT_SUCCESS);
    eprintf("Expected: %g\n", 26*2/2+log10f(M_PI)+2.f
            *powf(2,1*(3+7*.1f)*1.1f+src_float[0])*3*4+cosf(2.0f));

    /* Building vectors, conditionals */
    snprintf(str, 256, "y=(x>1)?[1,2,3]:[2,4,6]");
    setup_test('f', 1, 3, src_float, 'i', 1, 3, dest_int);
    result += parse_and_eval(EXPECT_SUCCESS);
    eprintf("Expected: [%i, %i, %i]\n", src_float[0]>1?1:2, src_float[1]>1?2:4,
           src_float[2]>1?3:6);

    /* Conditionals with shortened syntax */
    snprintf(str, 256, "y=x?:123");
    setup_test('f', 1, 1, src_float, 'i', 1, 1, dest_int);
    result += parse_and_eval(EXPECT_SUCCESS);
    eprintf("Expected: %i\n", (int)src_float[0]?:123);

    /* Conditional that should be optimized */
    snprintf(str, 256, "y=1?2:123");
    setup_test('f', 1, 1, src_float, 'i', 1, 1, dest_int);
    result += parse_and_eval(EXPECT_SUCCESS);
    eprintf("Expected: 2\n");

    /* Building vectors with variables, operations inside vector-builder */
    snprintf(str, 256, "y=[x*-2+1,0]");
    setup_test('i', 1, 2, src_int, 'd', 1, 3, dest_double);
    result += parse_and_eval(EXPECT_SUCCESS);
    eprintf("Expected: [%g, %g, %g]\n", (double)src_int[0]*-2+1,
            (double)src_int[1]*-2+1, 0.0);

    /* Building vectors with variables, operations inside vector-builder */
    snprintf(str, 256, "y=[-99.4, -x*1.1+x]");
    setup_test('i', 1, 2, src_int, 'd', 1, 3, dest_double);
    result += parse_and_eval(EXPECT_SUCCESS);
    eprintf("Expected: [%g, %g, %g]\n", -99.4,
            (double)(-src_int[0]*1.1+src_int[0]),
            (double)(-src_int[1]*1.1+src_int[1]));

    /* Indexing vectors by range */
    snprintf(str, 256, "y=x[1:2]+100");
    setup_test('d', 1, 3, src_double, 'f', 1, 2, dest_float);
    result += parse_and_eval(EXPECT_SUCCESS);
    eprintf("Expected: [%g, %g]\n", (float)src_double[1]+100,
           (float)src_double[2]+100);

    /* Typical linear scaling expression with vectors */
    snprintf(str, 256, "y=x*[0.1,3.7,-.1112]+[2,1.3,9000]");
    setup_test('f', 1, 3, src_float, 'f', 1, 3, dest_float);
    result += parse_and_eval(EXPECT_SUCCESS);
    eprintf("Expected: [%g, %g, %g]\n", src_float[0]*0.1f+2.f,
            src_float[1]*3.7f+1.3f, src_float[2]*-.1112f+9000.f);

    /* Check type and vector length promotion of operation sequences */
    snprintf(str, 256, "y=1+2*3-4*x");
    setup_test('f', 1, 2, src_float, 'f', 1, 2, dest_float);
    result += parse_and_eval(EXPECT_SUCCESS);
    eprintf("Expected: [%g, %g]\n", 1.f+2.f*3.f-4.f*src_float[0],
            1.f+2.f*3.f-4.f*src_float[1]);

    /* Swizzling, more pre-computation */
    snprintf(str, 256, "y=[x[2],x[0]]*0+1+12");
    setup_test('f', 1, 3, src_float, 'f', 1, 2, dest_float);
    result += parse_and_eval(EXPECT_SUCCESS);
    eprintf("Expected: [%g, %g]\n", src_float[2]*0.f+1.f+12.f,
            src_float[0]*0.f+1.f+12.f);

    /* Logical negation */
    snprintf(str, 256, "y=!(x[1]*0)");
    setup_test('d', 1, 3, src_double, 'i', 1, 1, dest_int);
    result += parse_and_eval(EXPECT_SUCCESS);
    eprintf("Expected: %i\n", (int)!(src_double[1]*0));

    /* any() */
    snprintf(str, 256, "y=any(x-1)");
    setup_test('d', 1, 3, src_double, 'i', 1, 1, dest_int);
    result += parse_and_eval(EXPECT_SUCCESS);
    eprintf("Expected: %i\n", ((int)src_double[0]-1)?1:0
           | ((int)src_double[1]-1)?1:0
           | ((int)src_double[2]-1)?1:0);

    /* all() */
    snprintf(str, 256, "y=x[2]*all(x-1)");
    setup_test('d', 1, 3, src_double, 'i', 1, 1, dest_int);
    result += parse_and_eval(EXPECT_SUCCESS);
    int temp = ((int)src_double[0]-1)?1:0 & ((int)src_double[1]-1)?1:0
                & ((int)src_double[2]-1)?1:0;
    eprintf("Expected: %i\n", (int)src_double[2] * temp);

    /* pi and e, extra spaces */
    snprintf(str, 256, "y=x + pi -     e");
    setup_test('d', 1, 1, src_double, 'f', 1, 1, dest_float);
    result += parse_and_eval(EXPECT_SUCCESS);
    eprintf("Expected: %g\n", (float)(src_double[0]+M_PI-M_E));

    /* bad vector notation */
    snprintf(str, 256, "y=(x-2)[1]");
    setup_test('i', 1, 1, src_int, 'i', 1, 1, dest_int);
    result += parse_and_eval(EXPECT_FAILURE);
    eprintf("Expected: FAILURE\n");

    /* vector index outside bounds */
    snprintf(str, 256, "y=x[3]");
    setup_test('i', 1, 3, src_int, 'i', 1, 1, dest_int);
    result += parse_and_eval(EXPECT_FAILURE);
    eprintf("Expected: FAILURE\n");

    /* vector length mismatch */
    snprintf(str, 256, "y=x[1:2]");
    setup_test('i', 1, 3, src_int, 'i', 1, 1, dest_int);
    result += parse_and_eval(EXPECT_FAILURE);
    eprintf("Expected: FAILURE\n");

    /* unnecessary vector notation */
    snprintf(str, 256, "y=x+[1]");
    setup_test('i', 1, 1, src_int, 'i', 1, 1, dest_int);
    result += parse_and_eval(EXPECT_SUCCESS);
    eprintf("Expected: %i\n", src_int[0]+1);

    /* invalid history index */
    snprintf(str, 256, "y=x{-101}");
    setup_test('i', 1, 1, src_int, 'i', 1, 1, dest_int);
    result += parse_and_eval(EXPECT_FAILURE);
    eprintf("Expected: FAILURE\n");

    /* invalid history index */
    snprintf(str, 256, "y=x-y{-101}");
    setup_test('i', 1, 1, src_int, 'i', 1, 1, dest_int);
    result += parse_and_eval(EXPECT_FAILURE);
    eprintf("Expected: FAILURE\n");

    /* scientific notation */
    snprintf(str, 256, "y=x[1]*1.23e-20");
    setup_test('i', 1, 2, src_int, 'd', 1, 1, dest_double);
    result += parse_and_eval(EXPECT_SUCCESS);
    eprintf("Expected: %g\n", (double)src_int[1] * 1.23e-20);

    /* Vector assignment */
    snprintf(str, 256, "y[1]=x[1]");
    setup_test('d', 1, 3, src_double, 'i', 1, 3, dest_int);
    result += parse_and_eval(EXPECT_SUCCESS);
    eprintf("Expected: [NULL, %i, NULL]\n", (int)src_double[1]);

    /* Vector assignment */
    snprintf(str, 256, "y[1:2]=[x[1],10]");
    setup_test('d', 1, 3, src_double, 'i', 1, 3, dest_int);
    result += parse_and_eval(EXPECT_SUCCESS);
    eprintf("Expected: [NULL, %i, %i]\n", (int)src_double[1], 10);

    /* Output vector swizzling */
    snprintf(str, 256, "[y[0],y[2]]=x[1:2]");
    setup_test('f', 1, 3, src_float, 'd', 1, 3, dest_double);
    result += parse_and_eval(EXPECT_SUCCESS);
    eprintf("Expected: [%g, NULL, %g]\n", (double)src_float[1],
            (double)src_float[2]);

    /* Multiple expressions */
    snprintf(str, 256, "y[0]=x*100-23.5; y[2]=100-x*6.7");
    setup_test('i', 1, 1, src_int, 'f', 1, 3, dest_float);
    result += parse_and_eval(EXPECT_FAILURE);
    eprintf("Expected: FAILURE\n");

    /* Error check: separating sub-expressions with commas */
    snprintf(str, 256, "foo=1,  y=y{-1}+foo");
    setup_test('i', 1, 1, src_int, 'f', 1, 1, dest_float);
    result += parse_and_eval(EXPECT_FAILURE);
    eprintf("Expected: FAILURE\n");

    /* Initialize filters */
    snprintf(str, 256, "y=x+y{-1}; y{-1}=100");
    setup_test('i', 1, 1, src_int, 'i', 2, 1, dest_int);
    result += parse_and_eval(EXPECT_SUCCESS);
    eprintf("Expected: %i\n", src_int[0]*iterations + 100);

    /* Initialize filters + vector index */
    snprintf(str, 256, "y=x+y{-1}; y[1]{-1}=100");
    setup_test('i', 1, 2, src_int, 'i', 2, 2, dest_int);
    result += parse_and_eval(EXPECT_SUCCESS);
    eprintf("Expected: [%i, %i]\n", src_int[0]*iterations,
            src_int[1]*iterations + 100);

    /* Initialize filters + vector index */
    snprintf(str, 256, "y=x+y{-1}; y{-1}=[100,101]");
    setup_test('i', 1, 2, src_int, 'i', 2, 2, dest_int);
    result += parse_and_eval(EXPECT_SUCCESS);
    eprintf("Expected: [%i, %i]\n", src_int[0]*iterations + 100,
            src_int[1]*iterations + 101);

    /* Initialize filters */
    snprintf(str, 256, "y=x+y{-1}; y[0]{-1}=100; y[2]{-1}=200");
    setup_test('i', 1, 3, src_int, 'i', 2, 3, dest_int);
    result += parse_and_eval(EXPECT_SUCCESS);
    eprintf("Expected: [%i, %i, %i]\n", src_int[0]*iterations + 100,
            src_int[1]*iterations, src_int[2]*iterations + 200);

    /* Initialize filters */
    snprintf(str, 256, "y=x+y{-1}-y{-2}; y{-1}=[100,101]; y{-2}=[100,101]");
    setup_test('i', 1, 2, src_int, 'i', 3, 2, dest_int);
    result += parse_and_eval(EXPECT_SUCCESS);
    eprintf("Expected: [1, 2]\n");

    /* Only initialize */
    snprintf(str, 256, "y{-1}=100");
    setup_test('i', 1, 3, src_int, 'i', 1, 1, dest_int);
    result += parse_and_eval(EXPECT_FAILURE);
    eprintf("Expected: FAILURE\n");

    /* Some examples of bad syntax */
    strcpy(str, "");
    setup_test('i', 1, 1, src_int, 'f', 1, 3, dest_float);
    result += parse_and_eval(EXPECT_FAILURE);
    eprintf("Expected: FAILURE\n");
    snprintf(str, 256, " ");
    setup_test('i', 1, 1, src_int, 'f', 1, 3, dest_float);
    result += parse_and_eval(EXPECT_FAILURE);
    eprintf("Expected: FAILURE\n");
    snprintf(str, 256, "y");
    setup_test('i', 1, 1, src_int, 'f', 1, 3, dest_float);
    result += parse_and_eval(EXPECT_FAILURE);
    eprintf("Expected: FAILURE\n");
    snprintf(str, 256, "y=");
    setup_test('i', 1, 1, src_int, 'f', 1, 3, dest_float);
    result += parse_and_eval(EXPECT_FAILURE);
    eprintf("Expected: FAILURE\n");
    snprintf(str, 256, "=x");
    setup_test('i', 1, 1, src_int, 'f', 1, 3, dest_float);
    result += parse_and_eval(EXPECT_FAILURE);
    eprintf("Expected: FAILURE\n");
    snprintf(str, 256, "sin(x)");
    setup_test('i', 1, 1, src_int, 'f', 1, 3, dest_float);
    result += parse_and_eval(EXPECT_FAILURE);
    eprintf("Expected: FAILURE\n");

    /* Variable declaration */
    snprintf(str, 256, "var=3.5; y=x+var");
    setup_test('i', 1, 1, src_int, 'f', 1, 1, dest_float);
    result += parse_and_eval(EXPECT_SUCCESS);
    eprintf("Expected: %g\n", (float)src_int[0] + 3.5);

    /* Variable declaration */
    snprintf(str, 256, "ema=ema{-1}*0.9+x*0.1; y=ema*2; ema{-1}=90");
    setup_test('i', 1, 1, src_int, 'f', 1, 1, dest_float);
    result += parse_and_eval(EXPECT_SUCCESS);
    eprintf("Expected: 2\n");

    /* Use of uninitialized variable */
    snprintf(str, 256, "y=x + myvariable * 10");
    setup_test('i', 1, 1, src_int, 'f', 1, 1, dest_float);
    result += parse_and_eval(EXPECT_FAILURE);
    eprintf("Expected: FAILURE\n");

    /* Vector functions mean() and sum() */
    snprintf(str, 256, "y=mean(x)==(sum(x)/3)");
    setup_test('f', 1, 3, src_float, 'i', 1, 1, dest_int);
    result += parse_and_eval(EXPECT_SUCCESS);
    eprintf("Expected: %i\n", 1);

    /* Overloaded vector functions max() and min() */
    snprintf(str, 256, "y=max(x)-min(x)");
    setup_test('f', 1, 3, src_float, 'i', 1, 1, dest_int);
    result += parse_and_eval(EXPECT_SUCCESS);
    eprintf("Expected: %i\n",
            ((src_float[0]>src_float[1])?
             (src_float[0]>src_float[2]?(int)src_float[0]:(int)src_float[2]):
             (src_float[1]>src_float[2]?(int)src_float[1]:(int)src_float[2])) -
            ((src_float[0]<src_float[1])?
             (src_float[0]<src_float[2]?(int)src_float[0]:(int)src_float[2]):
             (src_float[1]<src_float[2]?(int)src_float[1]:(int)src_float[2])));

    /* Optimization: operations by zero */
    snprintf(str, 256, "y=0*sin(x)*200+1.1");
    setup_test('i', 1, 1, src_int, 'f', 1, 1, dest_float);
    result += parse_and_eval(EXPECT_SUCCESS);
    eprintf("Expected: 1.1\n");

    /* Optimization: operations by one */
    snprintf(str, 256, "y=x*1");
    setup_test('i', 1, 1, src_int, 'f', 1, 1, dest_float);
    result += parse_and_eval(EXPECT_SUCCESS);
    eprintf("Expected: 1\n");

    /* Error check: division by zero */
    snprintf(str, 256, "y=x/0");
    setup_test('i', 1, 1, src_int, 'f', 1, 1, dest_float);
    result += parse_and_eval(EXPECT_FAILURE);
    eprintf("Expected: FAILURE\n");

    return result;
}