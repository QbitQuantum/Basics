int BasicASIOTransport::setup_socket(udp::socket& socket)
{
  int tar_buff_size(settings_.queue_length);

  asio::socket_base::send_buffer_size send_buffer_option;
  asio::socket_base::receive_buffer_size receive_buffer_option;

  try
  {
    socket.get_option(send_buffer_option);
    int send_buff_size = send_buffer_option.value();

    socket.get_option(receive_buffer_option);
    int rcv_buff_size = receive_buffer_option.value();

    madara_logger_log(context_.get_logger(), logger::LOG_MAJOR,
        "BasicASIOTransport::setup:"
        " default socket buff size is send=%d, rcv=%d\n",
        send_buff_size, rcv_buff_size);

    if (send_buff_size < tar_buff_size)
    {
      madara_logger_log(context_.get_logger(), logger::LOG_MAJOR,
          "BasicASIOTransport::setup:"
          " setting send buff size to settings.queue_length (%d)\n",
          tar_buff_size);

      send_buffer_option = tar_buff_size;
      socket.set_option(send_buffer_option);

      socket.get_option(send_buffer_option);
      send_buff_size = send_buffer_option.value();

      madara_logger_log(context_.get_logger(), logger::LOG_MAJOR,
          "BasicASIOTransport::setup:"
          " current socket buff size is send=%d, rcv=%d\n",
          send_buff_size, rcv_buff_size);
    }

    if (rcv_buff_size < tar_buff_size)
    {
      madara_logger_log(context_.get_logger(), logger::LOG_MAJOR,
          "BasicASIOTransport::setup:"
          " setting rcv buff size to settings.queue_length (%d)\n",
          tar_buff_size);

      receive_buffer_option = tar_buff_size;
      socket.set_option(receive_buffer_option);

      socket.get_option(receive_buffer_option);
      rcv_buff_size = receive_buffer_option.value();

      madara_logger_log(context_.get_logger(), logger::LOG_MAJOR,
          "BasicASIOTransport::setup:"
          " current socket buff size is send=%d, rcv=%d\n",
          send_buff_size, rcv_buff_size);
    }
  }
  catch (const boost::system::system_error& e)
  {
    madara_logger_log(context_.get_logger(), logger::LOG_MAJOR,
        "BasicASIOTransport::setup:"
        " Error setting up sockets: %s\n",
        e.what());

    this->invalidate_transport();
    return -1;
  }

  return 0;
}