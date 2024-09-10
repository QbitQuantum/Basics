std::vector<X509_DN> Certificate_Store_Windows::all_subjects() const
   {
   std::vector<X509_DN> subject_dns;
   for(const auto store_name : cert_store_names)
      {
      Handle_Guard<HCERTSTORE> windows_cert_store = open_cert_store(store_name);
      Handle_Guard<PCCERT_CONTEXT> cert_context = nullptr;

      // Handle_Guard::assign exchanges the underlying pointer. No RAII is needed here, because the Windows API takes care of
      // freeing the previous context.
      while(cert_context.assign(CertEnumCertificatesInStore(windows_cert_store.get(), cert_context.get())))
         {
         X509_Certificate cert(cert_context->pbCertEncoded, cert_context->cbCertEncoded);
         subject_dns.push_back(cert.subject_dn());
         }
      }

   return subject_dns;
   }