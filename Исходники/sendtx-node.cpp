void send_tx(const std::error_code& ec, channel_ptr node, transaction_type& tx)
{
    check_error(ec);
    std::cout << "sendtx: Sending " << hash_transaction(tx) << std::endl;
    auto handle_send =
        [node](const std::error_code& ec)
        {
            if (ec)
                log_warning() << "Send failed: " << ec.message();
            else
                std::cout << "sendtx: Sent "
                    << time(nullptr) << std::endl;
            stopped = true;
        };
    node->send(tx, handle_send);
}