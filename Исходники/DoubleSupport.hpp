    /**
     * Determine if target is not a number
     * 
     * @param theNumber target number
     * @return true if target represents the "not a number" value
     */
    static bool
    isNaN(double    theNumber)
    {
#if defined(_MSC_VER)
        return _isnan(theNumber) != 0;
#elif defined(XALAN_POSIX2_AVAILABLE) && !defined(CYGWIN) && !defined(MINGW)
#if defined(XALAN_NO_STD_NAMESPACE)
        return isnam(theNumber) != 0;
#else
        return std::isnan(theNumber) != 0;
#endif
#else
        return s_NaN == theNumber;
#endif
    }