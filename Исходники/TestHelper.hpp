            bool bus_read(zmqpp::socket &sub, Content... content)
            {
                zmqpp::message msg;

                if (!sub.receive(msg))
                    return false;
                return bus_read_extract(&msg, content...);
            }