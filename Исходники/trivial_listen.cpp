 void on_container_start(proton::container& c) override {
     auto&& copts = proton::connection_options()
         .sasl_allow_insecure_mechs(true)
         .sasl_allowed_mechs("ANONYMOUS PLAIN")
     ;
     c.listen("0.0.0.0", copts);
 }