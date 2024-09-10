void Pool::spawn_connection() {
    if (state_ != POOL_STATE_CLOSING && state_ != POOL_STATE_CLOSED) {
        Connection* connection =
            new Connection(loop_, config_, metrics_,
                           address_,
                           io_worker_->keyspace(),
                           io_worker_->protocol_version(),
                           this);

        LOG_INFO("Spawning new connection to host %s", address_.to_string(true).c_str());
        connection->connect();

        connections_pending_.insert(connection);
    }
}