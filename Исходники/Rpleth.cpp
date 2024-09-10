            /**
            * Check that we can read a rpleth from the socket and check that its valid.
            */
            void check_rpleth_card_msg(zmqpp::socket &source, const std::vector<uint8_t> card_binary)
            {
                zmqpp::message msg;
                std::string connection_identity, data;

                source.receive(msg);
                msg >> connection_identity;
                msg >> data; // data we would read from socket
                RplethPacket rpleth_packet = extract_packet(data);

                ASSERT_TRUE(rpleth_packet.isGood);
                ASSERT_EQ(8, +rpleth_packet.dataLen);
                ASSERT_EQ(8, +rpleth_packet.data.size());

                ASSERT_EQ(card_binary, rpleth_packet.data);
            }