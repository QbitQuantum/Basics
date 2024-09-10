  static void ping_pong(stackful_actor self)
  {
    try
    {
      aid_t host, partner;
      host = self->recv("prepare", partner);

      int count_down;
      while (true)
      {
        self->recv("ping_pong", count_down);
        if (count_down == 0)
        {
          self->send(partner, "ping_pong", count_down);
          break;
        }
        --count_down;
        self->send(partner, "ping_pong", count_down);
      }
      self->send(host);
    }
    catch (std::exception& ex)
    {
      std::cerr << ex.what() << std::endl;
    }
  }