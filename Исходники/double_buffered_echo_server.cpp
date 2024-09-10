awaitable<void> echo(tcp::socket s)
{
 auto token = co_await this_coro::token();

 try
 {
   char data1[1024];
   char data2[1024];

   char* p1 = data1;
   char* p2 = data2;

   // Perform initial read into first buffer.
   size_t n = co_await s.async_read_some(boost::asio::buffer(p1, 1024), token);

   for (;;)
   {
     // Swap received data to other buffer and initiate write operation.
     std::swap(p1, p2);
     auto write_result = boost::asio::async_write(s, boost::asio::buffer(p2, n), token);

     // Perform next read while write operation is in progress.
     n = co_await s.async_read_some(boost::asio::buffer(p1, 1024), token);

     // Wait for write operation to complete before proceeding.
     co_await write_result;
   }
 }
 catch (std::exception& e)
 {
   std::printf("echo Exception: %s\n", e.what());
 }
}