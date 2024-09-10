void handle_stop(const std::error_code& ec)
{
    if (ec)
        log_error() << "Stopped: " << ec.message();
    log_info() << "Channel stopped.";
    channode->send(message::verack(), handle_send);
}