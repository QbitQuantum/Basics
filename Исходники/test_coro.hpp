  static void my_actor(stackful_actor self, aid_t base)
  {
    std::size_t loop_num = 10;
    yield_t yield = self.get_yield();
    timer_t tmr(self.get_context().get_io_service());

    for (std::size_t i=0; i<loop_num; ++i)
    {
      self->send(base, "echo");
      self->recv("echo");

      tmr.expires_from_now(boost::chrono::milliseconds(1));
      tmr.async_wait(yield);
    }
  }