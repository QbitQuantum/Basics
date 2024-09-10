void accepted_connection(const std::error_code& ec, channel_ptr node,
    acceptor_ptr accept)
{
    if (ec)
    {
        log_error() << "Accept: " << ec.message();
        return;
    }
    log_info() << "Accepted connection!";
    node->subscribe_stop(node_stopped);
    // Now we need to keep it alive otherwise the connection is closed.
    node->subscribe_version(
        std::bind(version_received, _1, _2, node));
    // Keep accepting more connections.
    accept->accept(
        std::bind(accepted_connection, _1, _2, accept));
}