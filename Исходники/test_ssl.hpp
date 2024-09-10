  static void echo_server(stackful_actor self)
  {
    context& ctx = self.get_context();
    log::logger_t& lg = ctx.get_logger();
    try
    {
      aid_t sender = self->recv("init");
      
      size_t scount = 0;
      errcode_t ec;

      tcp::resolver rsv(self);
      tcp_resolver_t::query qry("0.0.0.0", "23333");
      rsv.async_resolve(qry);
      boost::shared_ptr<tcp_resolver_t::iterator> eitr;
      self->match(tcp::as_resolve).recv(ec, eitr);
      GCE_VERIFY(!ec).except(ec);

      tcp::acceptor acpr(self);
      boost::asio::ip::tcp::endpoint ep = **eitr;

      acpr->open(ep.protocol());

      acpr->set_option(boost::asio::socket_base::reuse_address(true));
      acpr->bind(ep);

      acpr->set_option(boost::asio::socket_base::receive_buffer_size(640000));
      acpr->set_option(boost::asio::socket_base::send_buffer_size(640000));

      acpr->listen(1024);

      acpr->set_option(boost::asio::ip::tcp::no_delay(true));
      acpr->set_option(boost::asio::socket_base::keep_alive(true));
      acpr->set_option(boost::asio::socket_base::enable_connection_aborted(true));

      self->send(sender, "ready");
      
      /// ssl context
      boost::asio::ssl::context ssl_ctx(boost::asio::ssl::context::sslv23);
      ssl_ctx.set_options(
          boost::asio::ssl::context::default_workarounds
          | boost::asio::ssl::context::no_sslv2
          | boost::asio::ssl::context::single_dh_use);
      ssl_ctx.set_password_callback(boost::bind(&ssl_ut::get_password));
      ssl_ctx.use_certificate_chain_file("test_ssl_asio/server.pem");
      ssl_ctx.use_private_key_file("test_ssl_asio/server.pem", boost::asio::ssl::context::pem);
      ssl_ctx.use_tmp_dh_file("test_ssl_asio/dh512.pem");

      while (true)
      {
        boost::shared_ptr<ssl_socket_t> skt = 
          boost::make_shared<ssl_socket_t>(boost::ref(ctx.get_io_service()), boost::ref(ssl_ctx));
        acpr.async_accept(skt->lowest_layer());

        match_t type;
        errcode_t ec;
        message msg;
        self->match(tcp::as_accept, "end", type).raw(msg).recv();
        if (type == atom("end"))
        {
          break;
        }

        msg >> ec;
        if (!ec)
        {
          aid_t cln = spawn(self, boost::bind(&ssl_ut::echo_session, _arg1), monitored);
          self->send(cln, "init", skt);
          ++scount;
        }
      }

      for (size_t i=0; i<scount; ++i)
      {
        self->recv(exit);
      }
    }
    catch (std::exception& ex)
    {
      GCE_ERROR(lg) << ex.what();
    }
  }