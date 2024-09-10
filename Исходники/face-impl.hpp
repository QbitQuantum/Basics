  const RegisteredPrefixId*
  registerPrefix(const Name& prefix,
                 const shared_ptr<InterestFilterRecord>& filter,
                 const RegisterPrefixSuccessCallback& onSuccess,
                 const RegisterPrefixFailureCallback& onFailure,
                 uint64_t flags,
                 const nfd::CommandOptions& options)
  {
    using namespace nfd;

    ControlParameters params;
    params.setName(prefix);
    params.setFlags(flags);

    auto prefixToRegister = make_shared<RegisteredPrefix>(prefix, filter, options);

    m_face.m_nfdController->start<RibRegisterCommand>(params,
                                                      bind(&Impl::afterPrefixRegistered, this,
                                                           prefixToRegister, onSuccess),
                                                      bind(onFailure, prefixToRegister->getPrefix(), _2),
                                                      options);

    return reinterpret_cast<const RegisteredPrefixId*>(prefixToRegister.get());
  }