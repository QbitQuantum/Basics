void doSocketTest(EventPoll& poll)
{
    using namespace std::placeholders;

    const std::string PATH = "/tmp/ut-poll.sock";
    const size_t REQUEST_LEN = 5;
    const std::string REQUEST_GOOD = "GET 1";
    const std::string REQUEST_BAD = "GET 7";
    const std::string RESPONSE = "This is a response message";

    // Scenario 1:
    // client connects to server listening socket
    // client ---good-request---> server
    // server ---response---> client
    // client disconnects
    //
    // Scenario 2:
    // client connects to server listening socket
    // client ---bad-request----> server
    // server disconnects

    // { server setup

    auto serverCallback = [&](int /*fd*/,
                              Events events,
                              std::shared_ptr<Socket> socket,
                              CallbackGuard::Tracker) {
        LOGD("Server events: " << eventsToString(events));

        if (events & EPOLLIN) {
            std::string request(REQUEST_LEN, 'x');
            socket->read(&request.front(), request.size());
            if (request == REQUEST_GOOD) {
                poll.modifyFD(socket->getFD(), EPOLLRDHUP | EPOLLOUT);
            } else {
                // disconnect (socket is kept in callback)
                poll.removeFD(socket->getFD());
            }
        }

        if (events & EPOLLOUT) {
            socket->write(RESPONSE.data(), RESPONSE.size());
            poll.modifyFD(socket->getFD(), EPOLLRDHUP);
        }

        if (events & EPOLLRDHUP) {
            // client has disconnected
            poll.removeFD(socket->getFD());
        }
    };

    Socket listenSocket = Socket::createUNIX(PATH);
    CallbackGuard serverSocketsGuard;

    auto listenCallback = [&](int /*fd*/, Events events) {
        LOGD("Listen events: " << eventsToString(events));
        if (events & EPOLLIN) {
            // accept new server connection
            std::shared_ptr<Socket> socket = listenSocket.accept();
            poll.addFD(socket->getFD(),
                       EPOLLRDHUP | EPOLLIN,
                       std::bind(serverCallback, _1, _2, socket, serverSocketsGuard.spawn()));
        }
    };

    poll.addFD(listenSocket.getFD(), EPOLLIN, listenCallback);

    // } server setup

    // { client setup

    auto clientCallback = [&](int /*fd*/,
                              Events events,
                              Socket& socket,
                              const std::string& request,
                              ValueLatch<std::string>& response) {
        LOGD("Client events: " << eventsToString(events));

        if (events & EPOLLOUT) {
            socket.write(request.data(), request.size());
            poll.modifyFD(socket.getFD(), EPOLLRDHUP | EPOLLIN);
        }

        if (events & EPOLLIN) {
            try {
                std::string msg(RESPONSE.size(), 'x');
                socket.read(&msg.front(), msg.size());
                response.set(msg);
            } catch (const UtilsException&) {
                response.set(std::string());
            }
            poll.modifyFD(socket.getFD(), EPOLLRDHUP);
        }

        if (events & EPOLLRDHUP) {
            LOGD("Server has disconnected");
            poll.removeFD(socket.getFD()); //prevent active loop
        }
    };

    // } client setup

    // Scenario 1
    LOGD("Scerario 1");
    {
        Socket client = Socket::connectUNIX(PATH);
        ValueLatch<std::string> response;

        poll.addFD(client.getFD(),
                   EPOLLRDHUP | EPOLLOUT,
                   std::bind(clientCallback,
                             _1,
                             _2,
                             std::ref(client),
                             REQUEST_GOOD,
                             std::ref(response)));

        BOOST_CHECK(response.get(TIMEOUT) == RESPONSE);

        poll.removeFD(client.getFD());
    }

    // Scenario 2
    LOGD("Scerario 2");
    {
        Socket client = Socket::connectUNIX(PATH);
        ValueLatch<std::string> response;

        poll.addFD(client.getFD(),
                   EPOLLRDHUP | EPOLLOUT,
                   std::bind(clientCallback,
                             _1,
                             _2,
                             std::ref(client),
                             REQUEST_BAD,
                             std::ref(response)));

        BOOST_CHECK(response.get(TIMEOUT) == std::string());

        poll.removeFD(client.getFD());
    }
    LOGD("Done");

    poll.removeFD(listenSocket.getFD());

    // wait for all server sockets (ensure all EPOLLRDHUP are processed)
    BOOST_REQUIRE(serverSocketsGuard.waitForTrackers(TIMEOUT));
}