inline bool rdrand(
    UIntType *rand, std::integral_constant<std::size_t, sizeof(std::uint64_t)>)
{
#if defined(VSMC_MSVC) || (defined(VSMC_INTEL) && VSMC_INTEL_VERSION < 1600)
    unsigned __int64 r;
#else
    unsigned long long r;
#endif
    int cf = _rdrand64_step(&r);
    *rand = static_cast<UIntType>(r);

    return cf != 0;
}