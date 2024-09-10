DNSServiceErrorType DNSSDPluginAPI::resolve_init(DNSServiceRef* sdref,
						 uint32_t ifnum,
						 const std::string& name,
						 const std::string& regtype,
						 const std::string& domain,
						 void* context) {
  return DNSServiceResolve(sdref,
			   0,
			   ifnum,
			   name.c_str(),
			   regtype.c_str(),
			   domain.c_str(),
			   DNSSDPluginAPI::resolve_callback,
			   context);
}