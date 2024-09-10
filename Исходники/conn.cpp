///----------------------------------------------------------------------------
void conn::run(gce::actor<gce::stackless>& self)
{
  try
  {
    GCE_REENTER (self)
    {
      GCE_YIELD
      {
        gce::response_t res =
          gce::request(
            self, group_aid_,
            gce::atom("add_conn")
            );

        self.recv(res, sender_, msg_);
      }

      if (msg_.get_type() != gce::atom("ok"))
      {
        throw std::runtime_error("add_conn error");
      }

      GCE_YIELD 
      {
        gce::spawn(
          self,
          boost::bind(&conn::timeout::run, &tmo_, _1),
          tmo_aid_,
          gce::monitored
          );
      }

      GCE_YIELD
      {
        gce::spawn(
          self,
          boost::bind(
            &conn::recv::run, &rcv_, _1, 
            tmo_aid_, self.get_aid()
            ),
          rcv_aid_,
          gce::monitored,
          true
          );
      }

      running_ = true;
      exit_num_ = 0;
      while (running_)
      {
        msg_ = gce::message();
        sender_ = gce::aid_t();
        GCE_YIELD self.recv(sender_, msg_);
        type_ = msg_.get_type();
        if (type_ == gce::exit)
        {
          ++exit_num_;
          if (exit_num_ < 2)
          {
            gce::send(self, tmo_aid_, gce::exit);
          skt_->close();
          }
          else
          {
            running_ = false;
          }
        }
        else if (type_ == gce::atom("stop"))
        {
          gce::send(self, tmo_aid_, gce::exit);
          skt_->close();
        }
        else if (type_ == gce::atom("fwd_msg"))
        {
          GCE_YIELD
          {
            gce::message m;
            msg_ >> m;
            std::printf("fwd msg to client: %s\n", gce::atom(m.get_type()).c_str());
            ec_.clear();
            skt_->send(m, gce::adaptor(self, ec_, bytes_transferred_));
          }

          if (ec_)
          {
            throw std::runtime_error("socket send error");
          }
        }
        else
        {
          std::string errmsg("conn::run unexpected message, type: ");
          errmsg += gce::atom(type_);
          throw std::runtime_error(errmsg);
        }
      }
    }