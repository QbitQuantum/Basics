int DeviceManagerThread::Run()
{
    ThreadCommand::PopBuffer command;

    SetThreadName("OVR::DeviceManagerThread");
    LogText("OVR::DeviceManagerThread - running (ThreadId=%p).\n", GetThreadId());
    

    while(!IsExiting())
    {
        // PopCommand will reset event on empty queue.
        if (PopCommand(&command))
        {
            command.Execute();
        }
        else
        {
            bool commands = 0;
            do
            {
                int n = poll(&PollFds[0], PollFds.GetSize(), -1);

                for (int i = 0; i < PollFds.GetSize(); i++)
                {
                    if (PollFds[i].revents & POLLERR)
                    {
                        OVR_DEBUG_LOG(("poll: error on [%d]: %d", i, PollFds[i].fd));
                    }
                    else if (PollFds[i].revents & POLLIN)
                    {
                        if (FdNotifiers[i])
                            FdNotifiers[i]->OnEvent(i, PollFds[i].fd);
                        else if (i == 0) // command
                        {
                            char dummy[128];                            
                            read(PollFds[i].fd, dummy, 128);
                            commands = 1;
                        }
                    }

                    if (PollFds[i].revents & POLLHUP)
                        PollFds[i].events = 0;

                    if (PollFds[i].revents != 0)
                    {
                        n--;
                        if (n == 0)
                            break;
                    }
                }                    
            } while (PollFds.GetSize() > 0 && !commands);
        }
    }

    LogText("OVR::DeviceManagerThread - exiting (ThreadId=%p).\n", GetThreadId());
    return 0;
}