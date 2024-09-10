    void* run()
    {
        // Remove 1 item at a time and process it. Blocks if no items are
        // available to process.
        for (int i = 0;; i++)
        {
            //qDebug("thread %lu, loop %d - waiting for item...", (long unsigned int)self(), i);
            WorkItem* item = m_queue.remove();
            //qDebug("thread %lu, loop %d - got one item", (long unsigned int)self(), i);
            TCPStream* stream = item->getStream();

            // Echo messages back the client until the connection is
            // closed
            char input[10256];
            for (int i = 0; i < 10255; i++)
            {
                input[i] = '\0';
            }

            string output;
            int len;

            while ((len = stream->receive(input, sizeof(input)-1)) > 0 )
            {
                output = "OK";
                stream->send(output.c_str(), (sizeof(output.c_str())-1));
                //qDebug("thread %lu, echoed '%s' back to the client", (long unsigned int)self(), input);

                //taskPrefix - Remote Task Manager Message, HOP task
                char taskPrefix[5];
                strncpy(taskPrefix, input, 4);
                taskPrefix[4] = '\0';

                if (strcmp(taskPrefix, "RTMM") == 0)
                {
                    std::string rtmm(input);
                    qDebug("%s", rtmm.c_str());
                    TaskManager::getInstance()->addUpdateRTMM(rtmm);
                    continue;
                }
                else if (strcmp(taskPrefix, "HOP_") == 0)
                {
                    std::string hoptaskmsg(input);
                    qDebug("%s", hoptaskmsg.c_str());

                    TaskManager::getInstance()->sendScript(hoptaskmsg.substr(4));

                    continue;
                }
                else
                {
                    std::string script(input);

                    if (script.length() > 0)
                    {
                        executeScript(script);
                    }
                }
            }

            delete item;
        }

        // Should never get here
        return NULL;
    }