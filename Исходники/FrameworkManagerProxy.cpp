/**
 * Creates a managed version of a specified algorithm.
 * @param algName :: The name of the algorithm to execute.
 * @param version :: The version number (default=-1=highest version).
 * @return Pointer to algorithm.
 **/
API::IAlgorithm_sptr FrameworkManagerProxy::createUnmanagedAlgorithm(const std::string& algName, const int version)
{
  API::IAlgorithm_sptr alg = API::AlgorithmManager::Instance().createUnmanaged(algName, version);
  alg->initialize();
  return alg;
}