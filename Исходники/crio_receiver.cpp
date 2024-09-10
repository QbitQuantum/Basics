void check_deadline(deadline_timer& deadline, udp::socket& socket) {
  if (deadline.expires_at() <= deadline_timer::traits_type::now()) {
    socket.cancel();
    deadline.expires_at(boost::posix_time::pos_infin);
  }
  deadline.async_wait(boost::bind(&check_deadline, boost::ref(deadline), boost::ref(socket)));
}