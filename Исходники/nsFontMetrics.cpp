static gfxFloat ComputeMaxAscent(const gfxFont::Metrics& aMetrics)
{
    return floor(aMetrics.maxAscent + 0.5);
}