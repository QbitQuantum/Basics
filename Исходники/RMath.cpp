/**
 * \return true if v is Inf.
 */
bool RMath::isInf(double v) {
#ifdef Q_OS_MAC
    return std::fpclassify(v)==FP_INFINITE;
#elif defined Q_OS_WIN32
    return !_finite(v);
#else
    return std::fpclassify(v)==FP_INFINITE;
#endif
}