void transmit_file(tcp::socket& socket,
    random_access_handle& file, Handler handler)
{
  // Construct an OVERLAPPED-derived object to contain the handler.
  overlapped_ptr overlapped(socket.get_io_service(), handler);

  // Initiate the TransmitFile operation.
  BOOL ok = ::TransmitFile(socket.native(),
      file.native(), 0, 0, overlapped.get(), 0, 0);
  DWORD last_error = ::GetLastError();

  // Check if the operation completed immediately.
  if (!ok && last_error != ERROR_IO_PENDING)
  {
    // The operation completed immediately, so a completion notification needs
    // to be posted. When complete() is called, ownership of the OVERLAPPED-
    // derived object passes to the io_service.
    asio::error_code ec(last_error,
        asio::error::get_system_category());
    overlapped.complete(ec, 0);
  }
  else
  {
    // The operation was successfully initiated, so ownership of the
    // OVERLAPPED-derived object has passed to the io_service.
    overlapped.release();
  }
}