bool SupportsSSE()
{
#if defined(USE_SSE)
    return IsProcessorFeaturePresent(PF_XMMI_INSTRUCTIONS_AVAILABLE) ? true : false;
#else
    return false;
#endif
}