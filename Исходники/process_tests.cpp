// Like the 'remote' test but uses http::connect.
TEST(ProcessTest, Http1)
{
  ASSERT_TRUE(GTEST_IS_THREADSAFE);

  RemoteProcess process;
  spawn(process);

  http::URL url = http::URL(
      "http",
      process.self().address.ip,
      process.self().address.port,
      process.self().id + "/handler");

  Future<http::Connection> connect = http::connect(url);
  AWAIT_READY(connect);

  http::Connection connection = connect.get();

  Future<UPID> pid;
  Future<string> body;
  EXPECT_CALL(process, handler(_, _))
    .WillOnce(DoAll(FutureArg<0>(&pid),
                    FutureArg<1>(&body)));

  http::Request request;
  request.method = "POST";
  request.url = url;
  request.headers["User-Agent"] = "libprocess/";
  request.body = "hello world";

  // Send the libprocess request. Note that we will not
  // receive a 202 due to the use of the `User-Agent`
  // header, therefore we need to explicitly disconnect!
  Future<http::Response> response = connection.send(request);

  AWAIT_READY(body);
  ASSERT_EQ("hello world", body.get());

  AWAIT_READY(pid);
  ASSERT_EQ(UPID(), pid.get());

  EXPECT_TRUE(response.isPending());

  AWAIT_READY(connection.disconnect());

  terminate(process);
  wait(process);
}