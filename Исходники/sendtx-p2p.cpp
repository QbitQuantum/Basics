void send_tx(const std::error_code& ec, channel_ptr node,
    protocol& prot, transaction_type& tx)
{
    check_error(ec);
    std::cout << "sendtx-p2p: Sending " << hash_transaction(tx) << std::endl;
    auto handle_send =
        [](const std::error_code& ec)
        {
            if (ec)
                log_warning() << "Send failed: " << ec.message();
            else
                std::cout << "sendtx-p2p: Sent "
                    << time(nullptr) << std::endl;
        };
    node->send(tx, handle_send);
    prot.subscribe_channel(
        std::bind(send_tx, _1, _2, std::ref(prot), std::ref(tx)));
}