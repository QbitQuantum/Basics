IsotopeEnvelopeEstimator::Impl::Impl(const Config& config)
:   config_(config)
{
    initializeCache();
}