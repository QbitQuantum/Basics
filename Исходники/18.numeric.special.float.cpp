void test_signaling_NaN (FloatT snan, FloatT snan2, const char *tname)
{
    // NAN never compares equal to self or any other number
    rw_assert (!(snan == snan2), 0, __LINE__,
               "numeric_limits<%s>::signaling_NaN() != "
               "numeric_limits<%1$s>::signaling_NaN()",
               tname);

    const FloatT inf = std::numeric_limits<FloatT>::infinity ();

    rw_assert (!(snan == inf), 0, __LINE__,
               "numeric_limits<%s>::signaling_NaN() != "
               "numeric_limits<%1$s>::infinity()",
                tname);

    rw_assert (!(snan == -inf), 0, __LINE__,
               "numeric_limits<%s>::signaling_NaN() != "
               "-numeric_limits<%1$s>::infinity()",
               tname);

#ifdef _MSC_VER

    rw_assert (0 != _isnan (snan), 0, __LINE__,
               "_isnan (numeric_limits<%s>::signaling_NaN()) != 0, got 0",
               tname);

    const int fpc = _fpclass (snan);
    rw_assert (_FPCLASS_SNAN == fpc, 0, __LINE__,
               "_fpclass(numeric_limits<%s>::signaling_NaN()) == "
               "%d (_FPCLASS_SNAN), got %d (%s)",
               tname, _FPCLASS_SNAN, fpc, fpclass_name (fpc));

#elif defined (_RWSTD_OS_SUNOS)

    rw_assert (!finite (snan), 0, __LINE__,
               "finite(numeric_limits<%s>::signaling_NaN()) == 0, "
               "got non-zero", tname);

    const fpclass_t fpc = fpclass (snan);
    rw_assert (FP_SNAN == fpc, 0, __LINE__,
               "fpclass(numeric_limits<%s>::signaling_NaN()) == %d "
               "(FP_SNAN), got %d (%s)", tname,
               FP_SNAN, fpc, fpclass_name (fpc));
#else

#  ifdef isnan

    rw_assert (0 != isnan (snan), 0, __LINE__,
               "isnan(numeric_limits<%s>::signaling_NaN()) != 0, got 0",
               tname);

#  endif   // isnan

#  ifdef fpclassify

    const int fpc = fpclassify (snan);
    rw_assert (FP_NAN == fpc, 0, __LINE__,
               "fpclassify(numeric_limits<%s>::signaling_NaN()) == "
               "%d (FP_NAN), got %d (%s)", tname,
               FP_NAN, fpc, fpclass_name (fpc));

#  endif   // fpclassify

#endif

}