/** Creates and initialises an instance of an algorithm.
 *
 * The algorithm gets tracked in the list of "managed" algorithms,
 * which is shown in GUI for cancelling, etc.
 *
 * @param  algName :: The name of the algorithm required
 * @param  version :: The version of the algorithm required, if not defined most
 *recent version is used -> version =-1
 * @param  makeProxy :: If true (default), create and return AlgorithmProxy of
 *the given algorithm.
 *         DO NOT SET TO FALSE unless you are really sure of what you are doing!
 * @return A pointer to the created algorithm
 * @throw  NotFoundError Thrown if algorithm requested is not registered
 * @throw  std::runtime_error Thrown if properties string is ill-formed
*/
IAlgorithm_sptr AlgorithmManagerImpl::create(const std::string &algName,
                                             const int &version,
                                             bool makeProxy) {
  Mutex::ScopedLock _lock(this->m_managedMutex);
  IAlgorithm_sptr alg;
  try {
    Algorithm_sptr unmanagedAlg = AlgorithmFactory::Instance().create(
        algName, version); // Throws on fail:
    if (makeProxy)
      alg = IAlgorithm_sptr(new AlgorithmProxy(unmanagedAlg));
    else
      alg = unmanagedAlg;

    // If this takes us beyond the maximum size, then remove the oldest one(s)
    while (m_managed_algs.size() >=
           static_cast<std::deque<IAlgorithm_sptr>::size_type>(m_max_no_algs)) {
      std::deque<IAlgorithm_sptr>::iterator it;
      it = m_managed_algs.begin();

      // Look for the first (oldest) algo that is NOT running right now.
      while (it != m_managed_algs.end()) {
        if (!(*it)->isRunning())
          break;
        ++it;
      }

      if (it == m_managed_algs.end()) {
        // Unusual case where ALL algorithms are running
        g_log.warning()
            << "All algorithms in the AlgorithmManager are running. "
            << "Cannot pop oldest algorithm. "
            << "You should increase your 'algorithms.retained' value. "
            << m_managed_algs.size() << " in queue." << std::endl;
        break;
      } else {
        // Normal; erase that algorithm
        g_log.debug() << "Popping out oldest algorithm " << (*it)->name()
                      << std::endl;
        m_managed_algs.erase(it);
      }
    }

    // Add to list of managed ones
    m_managed_algs.push_back(alg);
    alg->initialize();

  } catch (std::runtime_error &ex) {
    g_log.error() << "AlgorithmManager:: Unable to create algorithm " << algName
                  << ' ' << ex.what() << std::endl;
    throw std::runtime_error("AlgorithmManager:: Unable to create algorithm " +
                             algName + ' ' + ex.what());
  }
  return alg;
}