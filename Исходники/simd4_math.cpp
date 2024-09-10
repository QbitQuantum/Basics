/*! \brief Implementation routine to compare SIMD4 vs reference functions.
 *
 * \param refFuncExpr    Description of reference function expression
 * \param simd4FuncExpr  Description of SIMD function expression
 * \param refFunc        Reference math function pointer
 * \param simd4Func      SIMD math function pointer
 *
 * The function will be tested with the range and tolerances specified in
 * the SimdBaseTest class. You should not never call this function directly,
 * but use the macro GMX_EXPECT_SIMD4_FUNC_NEAR(refFunc,tstFunc) instead.
 */
::testing::AssertionResult
Simd4MathTest::compareSimd4MathFunction(const char * refFuncExpr, const char *simd4FuncExpr,
                                        real refFunc(real x),     gmx_simd4_real_t gmx_simdcall simd4Func(gmx_simd4_real_t x))
{
    std::vector<real>            vx(GMX_SIMD4_WIDTH);
    std::vector<real>            vref(GMX_SIMD4_WIDTH);
    std::vector<real>            vtst(GMX_SIMD4_WIDTH);
    real                         dx;
    gmx_int64_t                  ulpDiff, maxUlpDiff;
    real                         maxUlpDiffPos;
    real                         refValMaxUlpDiff, simdValMaxUlpDiff;
    bool                         eq, signOk;
    int                          i, iter;
    int                          niter   = s_nPoints/GMX_SIMD4_WIDTH;
    int                          npoints = niter*GMX_SIMD4_WIDTH;
#    ifdef GMX_DOUBLE
    union {
        double r; gmx_int64_t i;
    } conv0, conv1;
#    else
    union {
        float  r; gmx_int32_t i;
    } conv0, conv1;
#    endif

    maxUlpDiff = 0;
    dx         = (range_.second-range_.first)/npoints;

    for (iter = 0; iter < niter; iter++)
    {
        for (i = 0; i < GMX_SIMD4_WIDTH; i++)
        {
            vx[i]   = range_.first+dx*(iter*GMX_SIMD4_WIDTH+i);
            vref[i] = refFunc(vx[i]);
        }
        vtst  = simd4Real2Vector(simd4Func(vector2Simd4Real(vx)));

        for (i = 0, eq = true, signOk = true; i < GMX_SIMD4_WIDTH && eq == true; i++)
        {
            eq     = eq && ( fabs(vref[i]-vtst[i]) < absTol_ );
            signOk = signOk && ( vref[i]*vtst[i] >= 0 );
        }
        if (eq == true)
        {
            // Go to next point if everything within absolute tolerance
            continue;
        }
        else if (signOk == false)
        {
            return ::testing::AssertionFailure()
                   << "Failing SIMD4 math function comparison due to sign differences." << std::endl
                   << "Reference function: " << refFuncExpr << std::endl
                   << "Simd function:      " << simd4FuncExpr << std::endl
                   << "Test range is ( " << range_.first << " , " << range_.second << " ) " << std::endl
                   << "First sign difference around x=" << std::setprecision(20) << ::testing::PrintToString(vx) << std::endl
                   << "Ref values:   " << std::setprecision(20) << ::testing::PrintToString(vref) << std::endl
                   << "SIMD4 values: " << std::setprecision(20) << ::testing::PrintToString(vtst) << std::endl;
        }
        /* We replicate the trivial ulp differences comparison here rather than
         * calling the lower-level routine for comparing them, since this enables
         * us to run through the entire test range and report the largest deviation
         * without lots of extra glue routines.
         */
        for (i = 0; i < GMX_SIMD4_WIDTH; i++)
        {
            conv0.r = vref[i];
            conv1.r = vtst[i];
            ulpDiff = llabs(conv0.i-conv1.i);
            if (ulpDiff > maxUlpDiff)
            {
                maxUlpDiff        = ulpDiff;
                maxUlpDiffPos     = vx[i];
                refValMaxUlpDiff  = vref[i];
                simdValMaxUlpDiff = vtst[i];
            }
        }
    }

    if (maxUlpDiff <= ulpTol_)
    {
        return ::testing::AssertionSuccess();
    }
    else
    {
        return ::testing::AssertionFailure()
               << "Failing SIMD4 math function ulp comparison between " << refFuncExpr << " and " << simd4FuncExpr << std::endl
               << "Requested ulp tolerance: " << ulpTol_ << std::endl
               << "Requested abs tolerance: " << absTol_ << std::endl
               << "Largest Ulp difference occurs for x=" << std::setprecision(20) << maxUlpDiffPos << std::endl
               << "Ref  values:  " << std::setprecision(20) << refValMaxUlpDiff << std::endl
               << "SIMD4 values: " << std::setprecision(20) << simdValMaxUlpDiff << std::endl
               << "Ulp diff.:   " << std::setprecision(20) << maxUlpDiff << std::endl;
    }
}