int main(int argc, char* argv[])
{
    int port = getPort(argc, argv);
    std::cout << "connecting on port:" << port << std::endl;
    Server server;

    try {
        server.init_asio();
        server.clear_access_channels(websocketpp::log::alevel::all);
        server.set_message_handler(
                std::bind(&messageReceived, &server, std::placeholders::_1, std::placeholders::_2));
        server.listen(port);
        server.start_accept();

        // Start the ASIO io_service run loop
        server.set_reuse_addr(true);
        server.run();
    } catch (websocketpp::exception const& e) {
        std::cout << e.what() << std::endl;
    } catch (...) {
        std::cout << "other exception" << std::endl;
    }
}