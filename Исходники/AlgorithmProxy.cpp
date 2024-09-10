/// Constructor
AlgorithmProxy::AlgorithmProxy(Algorithm_sptr alg)
    : PropertyManagerOwner(),
      m_executeAsync(new Poco::ActiveMethod<bool, Poco::Void, AlgorithmProxy>(
                         this, &AlgorithmProxy::executeAsyncImpl)),
      m_name(alg->name()), m_category(alg->category()),
      m_categorySeparator(alg->categorySeparator()), m_alias(alg->alias()),
      m_summary(alg->summary()), m_version(alg->version()), m_alg(alg),
      m_isExecuted(), m_isLoggingEnabled(true), m_loggingOffset(0),
      m_isAlgStartupLoggingEnabled(true), m_rethrow(false), m_isChild(false) {
    if (!alg) {
        throw std::logic_error("Unable to create a proxy algorithm.");
    }
    alg->initialize();
    copyPropertiesFrom(*alg);
}