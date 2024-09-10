void filesync_service::private_impl::new_connection(shared_ptr<server> server)
{
    auto stream = server->accept();
    if (!stream) {
        return;
    }

    if (contains(sync_peers_, stream->remote_host_id()))
    {
        auto peer = sync_peers_[stream->remote_host_id()];
        end_session_with(peer);
        logger::info() << "Repeated incoming connection from " << stream->remote_host_id();
        assert(!peer->stream_);
        peer->stream_ = stream;
        connect_stream(peer->stream_);
    }
    else
    {
        logger::info() << "New incoming connection from " << stream->remote_host_id();
        auto peer = make_shared<peer_sync>(stream);
        start_session_with(peer);//inserts new peer into the table
        connect_stream(peer->stream_);
    }
}