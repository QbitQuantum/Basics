TEST(HTTPTest, Endpoints)
{
  Http http;

  // First hit '/body' (using explicit sockets and HTTP/1.0).
  Try<Socket> create = Socket::create();
  ASSERT_SOME(create);

  Socket socket = create.get();

  AWAIT_READY(socket.connect(http.process->self().address));

  std::ostringstream out;
  out << "GET /" << http.process->self().id << "/body"
      << " HTTP/1.0\r\n"
      << "Connection: Keep-Alive\r\n"
      << "\r\n";

  const string data = out.str();

  EXPECT_CALL(*http.process, body(_))
    .WillOnce(Return(http::OK()));

  AWAIT_READY(socket.send(data));

  string response = "HTTP/1.1 200 OK";

  AWAIT_EXPECT_EQ(response, socket.recv(response.size()));

  // Now hit '/pipe' (by using http::get).
  http::Pipe pipe;
  http::OK ok;
  ok.type = http::Response::PIPE;
  ok.reader = pipe.reader();

  Future<Nothing> request;
  EXPECT_CALL(*http.process, pipe(_))
    .WillOnce(DoAll(FutureSatisfy(&request),
                    Return(ok)));

  Future<http::Response> future = http::get(http.process->self(), "pipe");

  AWAIT_READY(request);

  // Write the response.
  http::Pipe::Writer writer = pipe.writer();
  EXPECT_TRUE(writer.write("Hello World\n"));
  EXPECT_TRUE(writer.close());

  AWAIT_READY(future);
  EXPECT_EQ(http::Status::OK, future->code);
  EXPECT_EQ(http::Status::string(http::Status::OK), future->status);

  EXPECT_SOME_EQ("chunked", future->headers.get("Transfer-Encoding"));
  EXPECT_EQ("Hello World\n", future->body);
}