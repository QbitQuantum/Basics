void client_work(std::shared_ptr<Socket> client)
{
    client->setRcvTimeout(/*sec*/30, /*microsec*/0);
    while (true) try
    {
        std::string line = client->recv();
        client->send("echo: " + line + "\n");
    }
    catch(const std::exception &e)
    {
        std::cerr << "exception: " << e.what() << std::endl;
        return;
    }
}