  void operator()(CompletionHandler&& completion_handler,
      tcp::socket& socket, const char* message) const
  {
    // The async_write operation has a completion handler signature of:
    //
    //   void(boost::system::error_code error, std::size n)
    //
    // This differs from our operation's signature in that it is also passed
    // the number of bytes transferred as an argument of type std::size_t. We
    // will adapt our completion handler to async_write's completion handler
    // signature by using std::bind, which drops the additional argument.
    //
    // However, it is essential to the correctness of our composed operation
    // that we preserve the executor of the user-supplied completion handler.
    // The std::bind function will not do this for us, so we must do this by
    // first obtaining the completion handler's associated executor (defaulting
    // to the I/O executor - in this case the executor of the socket - if the
    // completion handler does not have its own) ...
    auto executor = boost::asio::get_associated_executor(
        completion_handler, socket.get_executor());

    // ... and then binding this executor to our adapted completion handler
    // using the boost::asio::bind_executor function.
    boost::asio::async_write(socket,
        boost::asio::buffer(message, std::strlen(message)),
        boost::asio::bind_executor(executor,
          std::bind(std::forward<CompletionHandler>(
            completion_handler), std::placeholders::_1)));
  }