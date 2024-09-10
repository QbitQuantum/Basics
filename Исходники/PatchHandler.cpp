void PatchHandler::OnWriteComplete(const boost::system::error_code& error, size_t bytes_transferred)
{
    if (error)
        return;

    send_buffer_.Consume(bytes_transferred);

    if (send_buffer_.length() > 0)
    {
        StartAsyncWrite();
        return;
    }

    TransmitFile();
}