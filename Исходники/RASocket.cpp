int RASocket::process_command (const std::string& command)
{
    if (command.length() == 0)
        return 0;

    sLog->outRemote("Got command: %s", command.c_str());

    // handle quit, exit and logout commands to terminate connection
    if (command == "quit" || command == "exit" || command == "logout")
    {
        (void) send("Bye\r\n");
        return -1;
    }

    CliCommandHolder* cmd = new CliCommandHolder(this, command.c_str(), &RASocket::zprint, &RASocket::commandFinished);
    sWorld->QueueCliCommand(cmd);

    // wait for result
    ACE_Message_Block* mb;
    for (;;)
    {
        if (getq(mb) == -1)
            return -1;

        if (mb->msg_type() == ACE_Message_Block::MB_BREAK)
        {
            mb->release();
            break;
        }

        if (size_t(peer().send(mb->rd_ptr(), mb->length())) != mb->length())
        {
            mb->release();
            return -1;
        }

        mb->release();
    }

    return 0;
}