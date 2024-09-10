  void registration(Thread *thread) {
    //  release calling thread semaphore
    thread->thread_ready();

    DNSServiceErrorType error;
    DNSServiceRef service;

    error = DNSServiceRegister(&service,
      0,                    // no flags
      0,                    // all network interfaces
      master_->name_.c_str(),         // name
      master_->service_type_.c_str(), // service type
      "",                   // register in default domain(s)
      NULL,                 // use default host name
      htons(master_->port_),// port number
      0,                    // length of TXT record
      NULL,                 // no TXT record
      Implementation::register_callback,  // callback function
      (void*)master_);         // context

    if (error == kDNSServiceErr_NoError) {
      pthread_cleanup_push(registration_cleanup, &service);
        register_service(service);
      pthread_cleanup_pop(0); // 0 = do not execute on pop
    } else {
      fprintf(stderr,"Could not register service %s.%s on port %u (error %d)\n", master_->name_.c_str(), master_->service_type_.c_str(), master_->port_, error);//, strerror(errno));
    }

    DNSServiceRefDeallocate(service);
  }