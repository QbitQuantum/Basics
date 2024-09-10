void RequestResponse::run()
{
    const char *options[] = {"", "--log-enable", "trace+", "--log-to-stdout", "on", "--log-time", "on", "--log-level", "on"};
    Logger::configure(9, options);

    std::string url = "amqp:ssl:" + _options.getHost() + ":" + std::to_string(_options.getPort());

    Connection connection(url, "{ protocol: amqp1.0 }");
    connection.setOption("sasl_mechanisms", "EXTERNAL");
    connection.setOption("heartbeat", "30");

    Address reply(_replyAddress);
    Address request(_requestAddress);
    Address response(_responseAddress);

    Duration timeout = Duration::SECOND * _options.getTimeout();

    try
    {
        connection.open();
        Session session = connection.createSession();

        std::cout << "-I- Connection opened, session created" << std::endl;

        Sender sender = session.createSender(request);
        sender.setCapacity(_capacity);

        std::cout << "-I- Sender created " << sender.getName() << std::endl;

        Receiver receiver = session.createReceiver(response);
        receiver.setCapacity(_capacity);

        std::cout << "-I- Receiver created " << receiver.getName() << std::endl;

        Message requestMsg("<FIXML>...</FIXML>");
        requestMsg.setDurable(false);
        requestMsg.setReplyTo(reply);
        sender.send(requestMsg, true);

        std::cout << "-I- Request message sent" << std::endl;

        try
        {
            Message responseMsg = receiver.fetch(timeout);

            std::cout << "-I- Received message with content: " << responseMsg.getContent() << std::endl;

            session.acknowledge(true);

            _messageCounter++;
        }
        catch (NoMessageAvailable noMessage)
        {
            std::cout << "-I- No message received for " << timeout.getMilliseconds()/1000 << " seconds" << std::endl;
        }

        session.sync(true);

        sender.close();
        receiver.close();
        session.close();
        connection.close();
    }
    catch (const std::exception &error)
    {
        connection.close();
        std::cerr << "-E- Caught exception: " << error.what() << std::endl;
        throw error;
    }
}