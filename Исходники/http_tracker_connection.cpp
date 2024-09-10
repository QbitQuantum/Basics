void http_tracker_connection::on_connect(http_connection& c)
{
    error_code ec;
    tcp::endpoint ep = c.socket().remote_endpoint(ec);
    m_tracker_ip = ep.address();
    boost::shared_ptr<request_callback> cb = requester();
}