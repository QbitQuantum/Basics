 ~WSClientImpl() override
 {
     ws_.close({});
     stream_.close();
     work_ = boost::none;
     thread_.join();
 }